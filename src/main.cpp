#include <sstream>
#include "../include/doc.h"
#include "../include/trie.h"
#include "../include/menu.h"
using namespace std;

// Функция загрузки начальной конфигурации программы
void load_setup()
{
    printf("\n***** Программа для поиска информации среди указанного множества документов *****\n\n");
    
    FILE *file = fopen(setup_path.c_str(), "r");

    // Проверка существует ли список документов на поиск
    if (file == NULL)
    {
        FILE *file_new = fopen(setup_path.c_str(), "w");
        fclose(file_new);
    }
    else
    {
        char line[100]; // Для хранения строк из файла

        // Чтение файла настроек построчно
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strcspn(line, "\n")] = '\0';
            if (strlen(line) > 0)
            {
                // Добавление пути к документу в общий список
                doc_list.push_back(line);
            }
        }
        fclose(file);
    }
}

int main()
{
    // Установка локали для поддержки русских символов в консоли
    setlocale(LC_ALL, "Russian");

    // Загрузка списка документов из файла настроек
    load_setup();

    // Проверка и загрузка документов в префиксное дерево
    check_doc();

    // Основное меню программы
    main_menu();

    return 0;
}
