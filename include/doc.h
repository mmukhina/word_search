#ifndef DOC_H
#define DOC_H

#include <vector>
#include <string>
using namespace std;

// Название файла настроек со списком документов
const string setup_path = "setup.txt";

// Функция удаления документа из списка
void del_doc();

// Функция проверки и загрузки всех документов в префиксное дерево
void check_doc();

// Функция добавления нового документа в список
void add_doc();

// Функция отображения списка всех документов
void show_all_doc();

// Функция проверки пустоты списка документов
bool doc_list_empty();

extern vector<string> doc_list;

#endif