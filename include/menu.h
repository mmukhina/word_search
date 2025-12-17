#ifndef MENU_H
#define MENU_H

#include <string>
using namespace std;

// Функция получения выбора пользователя из меню
int get_choice(int count);

// Главное меню программы
void main_menu();

// Функция подготовки перед поиском слова
void find_word_prep();

// Функция вывода окрестность найденного слова
void print_occur(string word_pos, string filename);

#endif