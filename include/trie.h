#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

// Структура узла
struct Node
{
    char letter;
    string in_file;
    vector<Node *> next;
};

// Функция загрузки документа в префиксное дерево
void load_doc(FILE *file, int doc_num);

// Функция поиска слова в префиксном дереве
string find_word(string word);

// Рекурсивная функция удаления информации о документе из дерева
void del_doc_tree(Node *node, string del_index);

// Рекурсивная функция вывода содержимого префиксного дерева (для отладки)
void print_trie(Node *node, string currentWord);

extern Node *head;

#endif