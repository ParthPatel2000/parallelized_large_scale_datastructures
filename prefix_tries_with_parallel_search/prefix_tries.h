#ifndef PREFIX_TRIES_H
#define PREFIX_TRIES_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Prefix_Trie
{
private:
    struct Node
    {
        struct Node *A;
        struct Node *C;
        struct Node *G;
        struct Node *T;
        struct Node *N;
        Node()
        {
            A = NULL;
            C = NULL;
            G = NULL;
            T = NULL;
            N = NULL;
        }
    };
    int node_count = 0;
    typedef struct Node node;
    node *root = NULL;
    void insert_helper(node *root, int index, char *sequence);
    void print_helper(node *root);
    void full_fuzzy_search_helper(node *root, int index, char *sequence, int &matches, bool &found, int mismatch = 0);
    void clear(node *root);
    void copy_node(node *src, node *dest);
    void increment_node_count();

public:
    Prefix_Trie();
    ~Prefix_Trie();
    Prefix_Trie(char **queries, int query_count);
    Prefix_Trie(const Prefix_Trie &other);
    int get_node_count();
    node *get_root();
    void insert(char *sequence);
    int search(char *sequence, int mismatch_tolerance);
    void remove(char *sequence);
    void print();
};

#endif