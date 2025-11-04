#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
using namespace std;

struct Node
{
    char letter;
    string in_file;
    vector<Node *> next;
};

void load_doc(FILE *file, int doc_num);
string find_word(string word);
void del_doc_tree(Node *node, string del_index);
void print_trie(Node *node, string currentWord);

extern Node *head;

#endif