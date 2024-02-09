#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

class Suffix_Tree
{
private:
    struct Node
    {
        int start; // start index of the suffix
        int end;   // end index of the suffix
        struct Node *A;
        struct Node *C;
        struct Node *G;
        struct Node *T;
        struct Node *N;
        
        Node()
        {
            start = -1;
            end = -1;
            A = NULL;
            C = NULL;
            G = NULL;
            T = NULL;
            N = NULL;
        }
    };
    typedef struct Node node;
    char *subject = NULL;
    int subject_length = 0;
    node *root = NULL;
    int node_count = 0;
    void clear(node *root);
    void tree_traverser(char *subject, node *root, int index);
    void print_tree_helper(node *root);
    void search_helper(char *query, node *root, int index, bool &found);

public:
    Suffix_Tree();
    ~Suffix_Tree();
    Suffix_Tree(char *subject);
    bool search(char *query);
    void insert(char *subject);
    void print_tree();
    int get_node_count();
};

#endif // SUFFIX_TREE_H