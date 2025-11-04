#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include "../include/doc.h"
#include "../include/trie.h"
#include "../include/menu.h"
using namespace std;

void load_setup()
{
    printf("\n***** Программа для поиска информации среди указанного множества документов *****\n\n");
    
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

    load_setup();

    check_doc();

    main_menu();

    return 0;
}
