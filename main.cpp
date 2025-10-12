#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

struct Node
{
    char letter;
    string in_file;
    vector<Node *> next;
};

Node *head = nullptr;

vector<string> doc_list;

// Получить выбор пользователя в меню
// int count - количество пунктов в меню
int get_choice(int count)
{
    int variant;     // Выбор пользователя итоговый
    char input[100]; // Для хранения ввода пользователя

    fgets(input, 99, stdin);            // Получаем ввод от пользователя
    input[strcspn(input, "\n")] = '\0'; // Удалить \n в конце строки

    printf("\033[2J\033[1;1H"); // Очистка консоли

    // Проверяем содержит ли строка только цифры и находится ли в необходимом диапазоне
    if (strspn(input, "0123456789") == strlen(input))
    {
        variant = atoi(input);
        if (variant > 0 && variant <= count)
            return variant;
        else
        {
            printf("Такой команды нет, введите цифру по списку.\n\n");
            return 0;
        }
    }
    else
    {
        printf("Такой команды нет, введите цифру по списку.\n\n");
        return 0;
    }
}

bool list_empty()
{
    if (doc_list.size() > 0)
    {
        return false;
    }

    return true;
}

void print_trie(Node *node, string currentWord = "")
{
    if (node->in_file.length() > 0 && currentWord != "")
    {
        cout << "Word: '" << currentWord << "'" << endl;
    }

    for (int i = 0; i < node->next.size(); i++)
    {
        Node *child = node->next[i];
        print_trie(child, currentWord + child->letter);
    }
}

string find_word(string word)
{
    Node *ptr = head;
    bool found_letter = false;
    for (int i = 0; i < word.length(); i++)
    {
        for (int j = 0; j < ptr->next.size(); j++)
        {
            if (ptr->next[j]->letter == word[i])
            {
                ptr = ptr->next[j];
                found_letter = true;
                break;
            }
        }
        if (!found_letter)
        {
            return "";
        }

        found_letter = false;
    }

    if (ptr->in_file.length() > 0)
    {
        return ptr->in_file;
    }

    return "";
}

void load_doc(FILE *file, int doc_num)
{
    // cout << "adding " << doc_num << endl;
    char line[100]; // Для хранения строк из файла

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // cout << line << endl;
        string text = (string)line;
        Node *ptr = nullptr;
        // Node *ptr_last = nullptr;
        if (head == nullptr)
        {
            head = new Node;
            head->letter = '\0';           // Initialize manually
            head->in_file = "";            // Initialize manually
            head->next = vector<Node *>(); // Initialize manually
        }
        ptr = head;

        for (int i = 0; i < text.length(); i++)
        {
            char currentChar = tolower(text[i]);
            // cout << currentChar << endl;
            if (strchr(".!,?;:'\"-()[]{}<>@#$%^&*_+=|\\/~` \t\n\r", currentChar) != nullptr)
            {
                if (ptr != head)
                {
                    string doc_num_str = to_string(doc_num);
                    // cout << (ptr->in_file.find(doc_num_str) != string::npos) << endl;
                    if (ptr->in_file.find(doc_num_str) == string::npos)
                    {
                        ptr->in_file += to_string(doc_num);
                        ptr->in_file += '/';
                    }
                    // cout << "Added word ending at: " << currentChar << endl;
                }
                ptr = head;
            }
            else
            {
                bool found_letter = false;
                for (int i = 0; i < ptr->next.size(); i++)
                {
                    if (ptr->next[i]->letter == currentChar)
                    {
                        ptr = ptr->next[i];
                        found_letter = true;
                        break;
                    }
                }

                if (!found_letter)
                {
                    Node *newNode = new Node();    // Create new node
                    newNode->letter = currentChar; // Set letter manually
                    // cout << "add - " << currentChar << endl;
                    newNode->in_file = "";
                    newNode->next = vector<Node *>(); // Initialize next vector manually

                    ptr->next.push_back(newNode);
                    // ptr_last = ptr;
                    ptr = ptr->next[ptr->next.size() - 1];
                }
            }
        }
    }
}

void show_all_doc()
{
    printf("Список докуметов:\n");

    if (list_empty())
    {
        printf("Список документов для поиска пуст!\n\n");
        return;
    }

    for (int i = 0; i < doc_list.size(); i++)
    {
        printf("%d: %s\n", (i + 1), doc_list[i].c_str());
    }
}

void add_doc()
{
    printf("*** Добавить документ в список ***\n");
    printf("Для выхода введите <\n\n");
    printf("Введите название файла формата txt: ");
    char input[100];
    fgets(input, 99, stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("\033[2J\033[1;1H"); // Очистка консоли

    if (strcmp(input, "<") == 0)
    {
        return;
    }

    FILE *check = fopen(input, "r");
    if (check == NULL)
    {
        printf("Файл %s не существует!\n\n", input);
        return;
    }
    fclose(check);

    FILE *file = fopen(input, "r");
    doc_list.push_back(input);
    load_doc(file, doc_list.size() - 1);
    fclose(file);

    FILE *setting = fopen("setup.txt", "a");
    fprintf(setting, "%s\n", input);
    fclose(setting);

    printf("Файл %s успешно добавлен в список\n\n", input);
}

void del_doc_tree(Node *node, string del_index)
{
    int del_doc_num = stoi(del_index);

    if (node->in_file.length() > 0)
    {
        string new_in_file = "";
        stringstream ss(node->in_file);
        string token;
        bool changed = false;

        while (getline(ss, token, '/'))
        {
            if (!token.empty())
            {
                int current_num = stoi(token);
                if (current_num == del_doc_num)
                {
                    changed = true;
                }
                else if (current_num > del_doc_num)
                {
                    new_in_file += to_string(current_num - 1) + "/";
                    changed = true;
                }
                else
                {
                    new_in_file += token + "/";
                }
            }
        }

        if (changed)
        {
            // cout << "Before: " << node->in_file << " -> After: " << new_in_file << endl;
            node->in_file = new_in_file;
        }
    }

    for (int i = 0; i < node->next.size(); i++)
    {
        Node *child = node->next[i];
        del_doc_tree(child, del_index);
    }
}

void del_doc()
{
    int num_list = doc_list.size();

    bool incorrect_input = true;

    while (incorrect_input)
    {
        printf("*** Удалить документ из списка ***\n");
        printf("Для выхода введите <\n\n");

        if (list_empty())
        {
            printf("Список документов для поиска пуст!\n\n");
        }
        else
        {
            show_all_doc();
            printf("\n");
            printf("Введите номер документа:\n");
        }

        printf("> ");

        char input[100];
        fgets(input, 99, stdin);
        input[strcspn(input, "\n")] = '\0';

        printf("\033[2J\033[1;1H"); // Очистка консоли

        if (strcmp(input, "<") == 0)
        {
            return;
        }

        if (strspn(input, "0123456789") == strlen(input))
        {
            int variant = atoi(input);
            if (variant > 0 && variant <= num_list)
            {
                int del_index = variant - 1;
                printf("Успешно удален файл %s из списка!\n\n", doc_list[del_index].c_str());
                doc_list.erase(doc_list.begin() + del_index);

                del_doc_tree(head, to_string(del_index));

                FILE *setup = fopen("setup.txt", "w");

                for (int i = 0; i < doc_list.size(); i++)
                {
                    fprintf(setup, "%s\n", doc_list[i].c_str());
                }
                fclose(setup);
                incorrect_input = false;
            }

            else
            {
                printf("Такой команды нет, введите цифру по списку.\n\n");
            }
        }
        else
        {
            printf("Такой команды нет, введите цифру по списку.\n\n");
        }
    }
}

void check_doc()
{
    for (int i = 0; i < doc_list.size(); i++)
    {
        FILE *file = fopen(doc_list[i].c_str(), "r");

        if (file == NULL)
        {
            printf("Ошибка при открытии файла %s.", doc_list[i].c_str());
            break;
        }

        load_doc(file, i);

        fclose(file);
    }

    if (list_empty())
    {
        printf("Список документов для поиска пуст!\n\n");
    }
    else
    {
        printf("Все файлы успешно загружены!\n\n");
    }

    // cout << "printing all words" << endl;
    // print_trie(head);
}

void find_word_prep()
{
    bool incorrect_input = true;

    while (incorrect_input)
    {
        printf("*** Поиск по слову ***\n");
        printf("Для выхода введите <\n\n");

        if (list_empty())
        {
            printf("Список документов для поиска пуст!\n\n");
        } else {
            printf("Введите слово для поиска:\n");
        }

        printf("> ");

        char input[100];
        fgets(input, 99, stdin);
        input[strcspn(input, "\n")] = '\0';
        printf("\033[2J\033[1;1H"); // Очистка консоли

        if (strcmp(input, "<") == 0)
        {
            return;
        }

        if (list_empty()) continue;

        string res = find_word((string)input);
        string doc_num;

        if (res.length() > 0)
        {
            printf("%s найденно!\n\n", input);
            for (int i = 0; i < res.length(); i++)
            {
                if (res[i] == '/')
                {
                    int doc_num_int = stoi(doc_num);
                    doc_num = "";
                    printf("%d: %s\n", doc_num_int + 1, doc_list[doc_num_int].c_str());
                }
                else
                {
                    doc_num += res[i];
                }
            }

            printf("\n");
        }
        else
        {
            printf("%s не найденно!\n\n", input);
        }
    }
}

void load_setup()
{
    FILE *file = fopen("setup.txt", "r");

    if (file == NULL)
    {
        FILE *file_new = fopen("setup.txt", "w");
        fclose(file_new);
    }
    else
    {
        char line[100]; // Для хранения строк из файла

        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strcspn(line, "\n")] = '\0';
            if (strlen(line) > 0)
            {
                doc_list.push_back(line);
            }
        }
        fclose(file);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    printf("\n***** Программа для поиска информации среди указанного множества документов *****\n\n");

    load_setup();

    check_doc();

    int choice = 0;                // Выбор пользователя
    const int main_menu_total = 5; // Количество пунктов в меню

    // Основной цикл программы
    while (choice != main_menu_total)
    {
        printf("Меню:\n");
        printf("1. Посмотреть список документов\n");
        printf("2. Добавить документ в список\n");
        printf("3. Удалить документ из списка\n");
        printf("4. Поиск по слову\n");
        printf("5. Выход\n");
        printf("> ");

        // Получить выбор из меню
        choice = get_choice(main_menu_total);

        // Пропустить если был неправильный выбор
        if (choice == 0)
            continue;

        switch (choice)
        {
        case 1:
            show_all_doc();
            printf("\n");
            break;
        case 2:
            add_doc();
            break;
        case 3:
            del_doc();
            break;
        case 4:
            find_word_prep();
            break;
        }
    }

    return 0;
}
