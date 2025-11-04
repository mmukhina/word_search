#include "../include/menu.h"
#include "../include/doc.h"
#include "../include/trie.h"
#include <fstream>
using namespace std;

int choice = 0;                // Выбор пользователя
const int main_menu_total = 5; // Количество пунктов в меню

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

void find_word_prep()
{
    bool incorrect_input = true;

    while (incorrect_input)
    {
        printf("*** Поиск по слову ***\n");
        printf("Для выхода введите <\n\n");

        if (doc_list_empty())
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

        if (doc_list_empty()) continue;

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

void main_menu()
{
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
}