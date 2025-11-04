#ifndef DOC_H
#define DOC_H

#include <vector>
#include <string>
using namespace std;

void del_doc();
void check_doc();
void add_doc();
void show_all_doc();
bool doc_list_empty();

extern vector<string> doc_list;

#endif