#include "../include/trie.h"
using namespace std;


// Указатель на корень префиксного дерева
Node *head = nullptr;

// Функция загрузки документа в префиксное дерево
void load_doc(FILE *file, int doc_num)
{
    char line[100]; // Для хранения строк из файла

    // Чтение файла построчно
    while (fgets(line, sizeof(line), file) != NULL)
    {
        string text = (string)line;
        Node *ptr = nullptr;    // Указатель для навигации по дереву

        // Инициализация корня дерева при первом вызове
        if (head == nullptr)
        {
            head = new Node;
            head->letter = '\0';
            head->in_file = "";
            head->next = vector<Node *>();
        }
        ptr = head;

        // Обработка каждого символа в строке
        for (int i = 0; i < text.length(); i++)
        {
            // Приведение символа к нижнему регистру
            char currentChar = tolower(text[i]);

            // Проверка на разделитель
            if (strchr(".!,?;:'\"-()[]{}<>@#$%^&*_+=|\\/~` \t\n\r", currentChar) != nullptr)
            {
                // Если не в корне, значит найдено слово
                if (ptr != head)
                {
                    string doc_num_str = to_string(doc_num);
                    // Поиск информации о текущем документе в узле
                    unsigned long doc_pos = ptr->in_file.find(doc_num_str + "_");

                    // Если документ это слово еще не встречалось в документе, добавляем его
                    if (doc_pos == string::npos)
                    {
                        ptr->in_file += to_string(doc_num);
                        ptr->in_file += "_";
                        ptr->in_file += to_string(i);
                        ptr->in_file += ",/";
                    }
                    // Иначе добавляем только позицию этого слова
                    else
                    {
                        unsigned long underscore_pos = ptr->in_file.find("_", doc_pos);
                        unsigned long slash_pos = ptr->in_file.find("/", doc_pos);

                        if (underscore_pos != string::npos && slash_pos != string::npos)
                        {
                            string new_position = to_string(i) + ",";
                            ptr->in_file.insert(slash_pos, new_position);
                        }
                    }
                }
                // Возвращаемся к корню для начала нового слова
                ptr = head;
            }
            // Слово не найдено, шагаем по дереву и добавляем новые буквы
            else
            {
                bool found_letter = false;

                // Поиск буквы среди узлов
                for (int i = 0; i < ptr->next.size(); i++)
                {
                    if (ptr->next[i]->letter == currentChar)
                    {
                        ptr = ptr->next[i];
                        found_letter = true;
                        break;
                    }
                }

                // Если не найдена добавляем новый узел
                if (!found_letter)
                {
                    Node *newNode = new Node();
                    newNode->letter = currentChar;
                    newNode->in_file = "";
                    newNode->next = vector<Node *>();

                    ptr->next.push_back(newNode);
                    ptr = ptr->next[ptr->next.size() - 1];
                }
            }
        }
    }
}

// Функция поиска слова в префиксном дереве
string find_word(string word)
{
    Node *ptr = head;           // Начинаем с корня дерева
    bool found_letter = false;  // Флаг найденного слова

     // Проходим по каждому символу искомого слова
    for (int i = 0; i < word.length(); i++)
    {
        // Поиск текущего символа среди узлов
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

    // Если достигнут узел с информацией о документах, возвращаем ее
    if (ptr->in_file.length() > 0)
    {
        return ptr->in_file;
    }

    return "";
}

// Рекурсивная функция удаления информации о документе из дерева
void del_doc_tree(Node *node, string del_index)
{
    int del_doc_num = stoi(del_index);

    // Обработка информации о документах в текущем узле
    if (node->in_file.length() > 0)
    {
        string new_in_file = ""; // Новая строка с обновленной информацией
        stringstream ss(node->in_file); // Поток для разбора строки
        string token; // Токен для хранения фрагментов информации
        bool changed = false; // Флаг изменения информации

        // Разбор строки по разделителю '/'
        while (getline(ss, token, '/'))
        {
            if (!token.empty())
            {
                // Извлечение номера документа из токена
                int current_num = stoi(token);

                // Если это удаляемый документ - пропускаем
                if (current_num == del_doc_num)
                {
                    changed = true;
                }
                // Если номер больше удаляемого - уменьшаем на 1
                else if (current_num > del_doc_num)
                {
                    new_in_file += to_string(current_num - 1) + "/";
                    changed = true;
                }
                // Если номер меньше - оставляем без изменений
                else
                {
                    new_in_file += token + "/";
                }
            }
        }
        // Если были изменения, обновляем информацию в узле
        if (changed)
        {
            node->in_file = new_in_file;
        }
    }

    // Рекурсивный обход всех узлов
    for (int i = 0; i < node->next.size(); i++)
    {
        Node *child = node->next[i];
        del_doc_tree(child, del_index);
    }
}

// Рекурсивная функция вывода содержимого префиксного дерева (для отладки)
void print_trie(Node *node, string currentWord = "")
{
    if (node->in_file.length() > 0 && currentWord != "")
    {
        printf("Word: %s\n", currentWord.c_str());
    }

    for (int i = 0; i < node->next.size(); i++)
    {
        Node *child = node->next[i];
        print_trie(child, currentWord + child->letter);
    }
}
