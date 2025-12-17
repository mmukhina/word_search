#include "../include/doc.h"
#include "../include/trie.h"
using namespace std;

// Вектор для хранения пути к файлам
vector<string> doc_list;

// Функция удаления документа из списка
void del_doc()
{
    int num_list = doc_list.size();
    bool incorrect_input = true;

    // Пока пользователь не выйдет из режима ввода
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
            show_all_doc();     // Отобразить список документов
            printf("\n");
            printf("Введите номер документа:\n");
        }

        printf("> ");

        // Ввод пользователя
        char input[100];
        fgets(input, 99, stdin);
        input[strcspn(input, "\n")] = '\0';

        printf("\033[2J\033[1;1H"); // Очистка консоли

        // Выйти из режима если введено <
        if (strcmp(input, "<") == 0)
        {
            return;
        }

        // Проверка, что введены только цифры
        if (strspn(input, "0123456789") == strlen(input))
        {
            int variant = atoi(input);
            
            // Проверка что номер находится в допустимом диапазоне
            if (variant > 0 && variant <= num_list)
            {
                int del_index = variant - 1;
                printf("Успешно удален файл %s из списка!\n\n", doc_list[del_index].c_str());
                
                // Удаление документа из вектора
                doc_list.erase(doc_list.begin() + del_index);

                // Удаление информации о документе из префиксного дерева
                del_doc_tree(head, to_string(del_index));

                // Обновление файла настроек с новым списком документов
                FILE *setup = fopen(setup_path.c_str(), "w");

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

// Функция проверки и загрузки всех документов в префиксное дерево
void check_doc()
{
    // Итерация по всем документам в списке
    for (int i = 0; i < doc_list.size(); i++)
    {
        FILE *file = fopen(doc_list[i].c_str(), "r");

        if (file == NULL)
        {
            printf("Ошибка при открытии файла %s.", doc_list[i].c_str());
            break;
        }

        // Загрузка документа в префиксное дерево
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
}

// Функция добавления нового документа в список
void add_doc()
{
    printf("*** Добавить документ в список ***\n");
    printf("Для выхода введите <\n\n");
    printf("Введите название файла формата txt: ");
    char input[100];
    fgets(input, 99, stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("\033[2J\033[1;1H"); // Очистка консоли

    // Если введено < выйти из режима
    if (strcmp(input, "<") == 0)
    {
        return;
    }

    // Проверка существования файла
    FILE *check = fopen(input, "r");
    if (check == NULL)
    {
        printf("Файл %s не существует!\n\n", input);
        return;
    }
    fclose(check);

    // Загрузка файла в префиксное дерево
    FILE *file = fopen(input, "r");
    doc_list.push_back(input);
    load_doc(file, doc_list.size() - 1);
    fclose(file);

    // Добавление путь файла в файл настроек
    FILE *setting = fopen(setup_path.c_str(), "a");
    fprintf(setting, "%s\n", input);
    fclose(setting);

    printf("Файл %s успешно добавлен в список\n\n", input);
}

// Функция отображения списка всех документов
void show_all_doc()
{
    printf("Список докуметов:\n");

    // Проверка наличия документов
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

// Функция проверки пустоты списка документов
bool doc_list_empty()
{
    if (doc_list.size() > 0)
    {
        return false;
    }

    return true;
}
