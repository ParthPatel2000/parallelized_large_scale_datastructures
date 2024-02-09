#include "prefix_tries.h"

Prefix_Trie::Prefix_Trie()
{
    root = new Node;
}

Prefix_Trie::~Prefix_Trie()
{
    clear(root);
}

void Prefix_Trie::clear(Node *root)
{
    if (root == NULL)
        return;
    clear(root->A);
    clear(root->C);
    clear(root->G);
    clear(root->T);
    clear(root->N);
    delete root;
}

Prefix_Trie::Prefix_Trie(char **queries, int query_count) : Prefix_Trie()
{
    for (int i = 0; i < query_count; i++)
    {
        insert(queries[i]);
    }
}

void Prefix_Trie::increment_node_count()
{
    node_count++;
}

int Prefix_Trie::get_node_count()
{
    return node_count;
}

void Prefix_Trie::copy_node(Node *src, Node *dest)
{
    if (src->A != NULL)
    {
        dest->A = new Node;
        copy_node(src->A, dest->A);
    }
    if (src->C != NULL)
    {
        dest->C = new Node;
        copy_node(src->C, dest->C);
    }
    if (src->G != NULL)
    {
        dest->G = new Node;
        copy_node(src->G, dest->G);
    }
    if (src->T != NULL)
    {
        dest->T = new Node;
        copy_node(src->T, dest->T);
    }
    if (src->N != NULL)
    {
        dest->N = new Node;
        copy_node(src->N, dest->N);
    }
    return;
}

// copy constructor
Prefix_Trie::Prefix_Trie(const Prefix_Trie &other)
{
    node_count = other.node_count;
    if (other.root == NULL)
    {
        root = NULL;
    }
    else
    {
        root = new Node;
        copy_node(other.root, root);
    }
}

Prefix_Trie::node *Prefix_Trie::get_root()
{
    return root;
}

void Prefix_Trie::insert(char *sequence)
{
    insert_helper(root, 0, sequence);
}

void Prefix_Trie::insert_helper(Node *root, int index, char *sequence)
{
    if (sequence[index] == '\0')
        return;

    switch (sequence[index])
    {
    case 'A':
        if (root->A == NULL)
        {
            root->A = new Node;
            increment_node_count();
        }
        insert_helper(root->A, index + 1, sequence);
        break;

    case 'C':
        if (root->C == NULL)
        {
            root->C = new Node;
            increment_node_count();
        }
        insert_helper(root->C, index + 1, sequence);
        break;

    case 'G':
        if (root->G == NULL)
        {
            root->G = new Node;
            increment_node_count();
        }
        insert_helper(root->G, index + 1, sequence);
        break;

    case 'T':
        if (root->T == NULL)
        {
            root->T = new Node;
            increment_node_count();
        }
        insert_helper(root->T, index + 1, sequence);
        break;

    default:
        if (root->N == NULL)
        {
            root->N = new Node;
            increment_node_count();
        }
        insert_helper(root->N, index + 1, sequence);
        break;
    }

    return;
}

int Prefix_Trie::search(char *sequence, int mismatch_tolerance)
{
    int matches = 0;
    bool found = false;
    full_fuzzy_search_helper(root, 0, sequence, matches, found, mismatch_tolerance);
    return matches;
}

void Prefix_Trie::full_fuzzy_search_helper(node *root, int index, char *sequence, int &matches, bool &found, int mismatch)
{
    if(found || root ==NULL)
        return;


    if (sequence[index] == '\0' && !found)
    {
        matches++;
        found = true;
        return;
    }

    Node *ptrs[5] = {root->A, root->C, root->G, root->T, root->N};
    int skip = 0;

    switch (sequence[index])
    {
    case 'A':
        skip = 0;
        break;

    case 'C':
        skip = 1;
        break;

    case 'G':
        skip = 2;
        break;

    case 'T':
        skip = 3;
        break;

    default:
        skip = 4;
        break;
    }

    full_fuzzy_search_helper(ptrs[skip], index + 1, sequence, matches, found, mismatch);
    for (int i = 0; i < 5 && mismatch != 0; i++)
    {
        if (i == skip)
            continue;
        full_fuzzy_search_helper(ptrs[i], index + 1, sequence, matches, found, mismatch - 1);
    }

    return;
}

void Prefix_Trie::print()
{
    print_helper(Prefix_Trie::root);
    return;
}

void Prefix_Trie::print_helper(Node *root)
{
    if (root == NULL)
        return;
    print_helper(root->A);
    print_helper(root->C);
    print_helper(root->G);
    print_helper(root->T);
    print_helper(root->N);
    cout << (root->A ? "A" : "")
         << (root->C ? "C" : "")
         << (root->G ? "G" : "")
         << (root->T ? "T" : "")
         << (root->N ? "N" : "") << endl;
    return;
}