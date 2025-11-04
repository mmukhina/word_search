#include "../include/doc.h"
#include "../include/trie.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

vector<string> doc_list;

void del_doc()
{
    int num_list = doc_list.size();

    bool incorrect_input = true;

    while (incorrect_input)
    {
        printf("*** Удалить документ из списка ***\n");
        printf("Для выхода введите <\n\n");

        if (doc_list_empty())
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

    if (doc_list_empty())
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

void show_all_doc()
{
    printf("Список докуметов:\n");

    if (doc_list_empty())
    {
        printf("Список документов для поиска пуст!\n\n");
        return;
    }

    for (int i = 0; i < doc_list.size(); i++)
    {
        printf("%d: %s\n", (i + 1), doc_list[i].c_str());
    }
}

bool doc_list_empty()
{
    if (doc_list.size() > 0)
    {
        return false;
    }

    return true;
}
