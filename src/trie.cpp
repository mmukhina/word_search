#include "../include/trie.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

Node *head = nullptr;

void load_doc(FILE *file, int doc_num)
{
    // cout << "adding " << doc_num << endl;
    char line[100]; // Для хранения строк из файла

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // cout << line << endl;
        string text = (string)line;
        Node *ptr = nullptr;
        // Node *ptr_last = nullptr;
        if (head == nullptr)
        {
            head = new Node;
            head->letter = '\0';           
            head->in_file = "";            
            head->next = vector<Node *>();
        }
        ptr = head;

        for (int i = 0; i < text.length(); i++)
        {
            char currentChar = tolower(text[i]);
            // cout << currentChar << endl;
            if (strchr(".!,?;:'\"-()[]{}<>@#$%^&*_+=|\\/~` \t\n\r", currentChar) != nullptr)
            {
                if (ptr != head)
                {
                    string doc_num_str = to_string(doc_num);
                    // cout << (ptr->in_file.find(doc_num_str) != string::npos) << endl;
                    if (ptr->in_file.find(doc_num_str) == string::npos)
                    {
                        ptr->in_file += to_string(doc_num);
                        ptr->in_file += '/';
                    }
                    // cout << "Added word ending at: " << currentChar << endl;
                }
                ptr = head;
            }
            else
            {
                bool found_letter = false;
                for (int i = 0; i < ptr->next.size(); i++)
                {
                    if (ptr->next[i]->letter == currentChar)
                    {
                        ptr = ptr->next[i];
                        found_letter = true;
                        break;
                    }
                }

                if (!found_letter)
                {
                    Node *newNode = new Node();
                    newNode->letter = currentChar;
                    // cout << "add - " << currentChar << endl;
                    newNode->in_file = "";
                    newNode->next = vector<Node *>();

                    ptr->next.push_back(newNode);
                    // ptr_last = ptr;
                    ptr = ptr->next[ptr->next.size() - 1];
                }
            }
        }
    }
}

string find_word(string word)
{
    Node *ptr = head;
    bool found_letter = false;
    for (int i = 0; i < word.length(); i++)
    {
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

    if (ptr->in_file.length() > 0)
    {
        return ptr->in_file;
    }

    return "";
}

void del_doc_tree(Node *node, string del_index)
{
    int del_doc_num = stoi(del_index);

    if (node->in_file.length() > 0)
    {
        string new_in_file = "";
        stringstream ss(node->in_file);
        string token;
        bool changed = false;

        while (getline(ss, token, '/'))
        {
            if (!token.empty())
            {
                int current_num = stoi(token);
                if (current_num == del_doc_num)
                {
                    changed = true;
                }
                else if (current_num > del_doc_num)
                {
                    new_in_file += to_string(current_num - 1) + "/";
                    changed = true;
                }
                else
                {
                    new_in_file += token + "/";
                }
            }
        }

        if (changed)
        {
            // cout << "Before: " << node->in_file << " -> After: " << new_in_file << endl;
            node->in_file = new_in_file;
        }
    }

    for (int i = 0; i < node->next.size(); i++)
    {
        Node *child = node->next[i];
        del_doc_tree(child, del_index);
    }
}

void print_trie(Node *node, string currentWord = "")
{
    if (node->in_file.length() > 0 && currentWord != "")
    {
        cout << "Word: '" << currentWord << "'" << endl;
    }

    for (int i = 0; i < node->next.size(); i++)
    {
        Node *child = node->next[i];
        print_trie(child, currentWord + child->letter);
    }
}
