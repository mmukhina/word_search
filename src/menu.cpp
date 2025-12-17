#include "../include/menu.h"
#include "../include/doc.h"
#include "../include/trie.h"
using namespace std;

int choice = 0;                // Выбор пользователя
const int main_menu_total = 5; // Количество пунктов в меню

// Функция получения выбора пользователя из меню
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

// Функция вывода окрестность найденного слова
void print_occur(string word_pos, string filename)
{
    // Открыть файл в режиме чтения
    FILE *file = fopen(filename.c_str(), "r");
    if (file == NULL)
    {
        printf("Ошибка: Невозможно открыть файл %s\n", filename.c_str());
        return;
    }

    // Для каждой записи находим 5 слов до и после
    string pos = "";
    for (int i = 0; i <= word_pos.length(); i++)
    {
        if (i == word_pos.length() || word_pos[i] == ',')
        {
            if (pos.empty())
                continue;

            // Перемещаем указатель на исходное слово
            long current_pos = stoi(pos);
            fseek(file, current_pos, SEEK_SET);

            int word_count = 0; // Подсчет слов
            char ch;

            // Двигаемся назад на 5 слов
            while (current_pos > 0 && word_count <= 5)
            {
                // Перемещаем указатель назад
                current_pos--;
                fseek(file, current_pos, SEEK_SET);

                // Получаем символ куда сейчас указывает указатель
                ch = fgetc(file);

                // Если найден пробел, значит найдено потенциальное слово
                if (ch == ' ' || ch == '\n' || ch == '\t')
                {
                    // Если за пробело стоит символ, тогда считаем его словом
                    fseek(file, current_pos - 1, SEEK_SET);
                    int prev_ch = fgetc(file);
                    if (!(prev_ch == ' ' || prev_ch == '\n' || prev_ch == '\t' || prev_ch == EOF))
                    {
                        word_count++;
                    }
                }
            }

            fseek(file, current_pos, SEEK_SET);
            string result = "";
            int total_words = 0;
            bool word = false;

            // Читаем все символы пока не найдем необходимое коичеств слов
            while ((ch = fgetc(file)) != EOF && total_words < word_count + 6)
            {
                if (ch == ' ' || ch == '\n' || ch == '\t')
                {
                    if (!word){
                       total_words++; 
                       word = true;
                    }
                    
                    result += ' ';
                } else {
                    result += ch;
                    word = false;
                }
                
            }
            // Очищаем пробелы в начале
            result.erase(0, result.find_first_not_of(" \t\n\r"));
            printf("-%s\n", result.c_str());
            pos = "";
        }
        else
        {
            pos += word_pos[i];
        }
    }
    fclose(file);
}

// Функция подготовки перед поиском слова
void find_word_prep()
{
    bool incorrect_input = true;

    // Продолжать цикл пока пользователь не выйдет из цикла
    while (incorrect_input)
    {
        printf("*** Поиск по слову ***\n");
        printf("Для выхода введите <\n\n");

        if (doc_list_empty())
        {
            printf("Список документов для поиска пуст!\n\n");
        }
        else
        {
            printf("Введите слово для поиска:\n");
        }

        printf("> ");

        // Получаем ввод от пользователя
        char input[100];
        fgets(input, 99, stdin);
        input[strcspn(input, "\n")] = '\0';
        printf("\033[2J\033[1;1H"); // Очистка консоли

        // Если пользователь ввел < выйти из режима
        if (strcmp(input, "<") == 0)
        {
            return;
        }

        // Проверка на пустой документ
        if (doc_list_empty())
            continue;

        // Выполнить поиск слова
        string res = find_word((string)input);

        string doc_num;             // Номер документа
        string word_pos;            // Позиция слова в документе
        bool doc_num_part = true;   // Флаг для распознования ключа

        // Расшифровка записи о местоположения слова в файле
        if (res.length() > 0)
        {
            printf("%s найденно!\n\n", input);
            for (int i = 0; i < res.length(); i++)
            {
                if (res[i] == '/')
                {
                    int doc_num_int = stoi(doc_num);
                    doc_num = "";
                    // Отобразить пользователю в каком файле надкно слово
                    printf("%d: %s\n", doc_num_int + 1, doc_list[doc_num_int].c_str());
                    // Отобразить все вхождения этого слова в файле
                    print_occur(word_pos, doc_list[doc_num_int]);
                    printf("\n");
                    doc_num_part = true;
                    word_pos = "";
                }
                else if (res[i] == '_')
                {
                    doc_num_part = false;   // Найден разделитель между номером файла и позицией
                }
                else if (doc_num_part)
                {
                    doc_num += res[i];      // Значение относиться к ключу
                }
                else
                {
                    word_pos += res[i];     // Значение относиться к позиции
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

// Главное меню программы
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
            show_all_doc();     // Показать список документов
            printf("\n");
            break;
        case 2:
            add_doc();          // Добавить документ в список поиска
            break;
        case 3:
            del_doc();          // Удалить документ из списка 
            break;
        case 4:
            find_word_prep();   // Начать подготовку перед поиском
            break;
        }
    }
}