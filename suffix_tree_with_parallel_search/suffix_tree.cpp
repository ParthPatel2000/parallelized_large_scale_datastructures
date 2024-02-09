/**
 * @file suffix_tree.cpp
 * @brief Implementation of the Suffix_Tree class.
 */

#include "suffix_tree.h"

/**
 * @brief Constructor for the Suffix_Tree class.
 */
Suffix_Tree::Suffix_Tree()
{
    root = new node;
    node_count++;
}

/**
 * @brief Destructor for the Suffix_Tree class.
 */
Suffix_Tree::~Suffix_Tree()
{
    clear(root);
}

/**
 * @brief Helper function for the destructor to clear the suffix tree.
 * @param root The root node of the suffix tree.
 */
void Suffix_Tree::clear(node *root)
{
    if (root == NULL)
    {
        return;
    }
    clear(root->A);
    clear(root->C);
    clear(root->G);
    clear(root->T);
    clear(root->N);
    delete root;
    return;
}


/**
 * @brief Helper function to get the number of nodes in the suffix tree.
 * @return The number of nodes in the suffix tree.
 */
int Suffix_Tree::get_node_count()
{
    return node_count;
}


/**
 * @brief Constructor for the Suffix_Tree class that takes a subject string.
 * @param subject The subject string to build the suffix tree from.
 */
Suffix_Tree::Suffix_Tree(char *subject) : Suffix_Tree()
{
    subject_length = strlen(subject);
    this->subject = subject;
    cout << "subject length: " << subject_length << endl;
    insert(this->subject);
}

/**
 * @brief Insert a subject string into the suffix tree.
 * @param subject The subject string to insert.
 */
void Suffix_Tree::insert(char *subject)
{
    for (long i = 0; i < subject_length; i++)
    {
        tree_traverser(subject, root, i);
    }
    return;
}

/**
 * @brief Helper function to traverse the suffix tree and insert a subject string.
 * @param subject The subject string to insert.
 * @param root The root node of the suffix tree.
 * @param index The index of the subject string to start inserting from.
 */
void Suffix_Tree::tree_traverser(char *subject, node *root, int index)
{
    bool debug = 0;
    // if we reach the end of the subject, then we are done.
    if (index == subject_length || index > subject_length)
    {
        return;
    }

    if (root == NULL)
    {
        return;
    }

    // find the branch to traverse down
    node *branch = NULL;
    switch (subject[index])
    {
    case 'A':
        if (root->A != NULL)
            branch = root->A;
        break;
    case 'C':
        if (root->C != NULL)
            branch = root->C;
        break;
    case 'G':
        if (root->G != NULL)
            branch = root->G;
        break;
    case 'T':
        if (root->T != NULL)
            branch = root->T;
        break;
    default:
        if (root->N != NULL)
            branch = root->N;
        break;
    }

    // if the branch doesn't exist, then we need to create it.
    if (branch == NULL)
    {
        if (debug)
        {
            cout << "creating branch" << endl;
        }
        node_count++;
        node *new_node = new node;
        new_node->start = index;
        new_node->end = subject_length - 1;
        switch (subject[index])
        {
        case 'A':
            root->A = new_node;
            break;
        case 'C':
            root->C = new_node;
            break;
        case 'G':
            root->G = new_node;
            break;
        case 'T':
            root->T = new_node;
            break;
        default:
            root->N = new_node;
            break;
        }
    }
    // if the branch does exist, then we need to match the subject to the branch.
    else
    {
        // start matching the subject to the branch
        int i = branch->start;
        while (subject[index] == subject[i] && i <= branch->end && index < subject_length)
        {
            index++;
            i++;
        }
        // if the whole branch matches the subject, and this branch doesn't need to be splitted,
        // then we need to traverse down the branch.
        if (i > branch->end)
        {
            if (debug)
            {
                cout << "traversing down branch" << endl;
            }
            tree_traverser(subject, branch, index);
        }
        // if we don't reach the end of the subject in the branch, then we need to split the branch.
        else
        {
            if (debug)
            {
                cout << "splitting branch with " << branch->start << " and " << branch->end << endl;
            }
            // splitting the branch into parent and child
            node_count++;
            // creating the child
            node *split = new node;
            split->start = i;
            split->end = branch->end;
            // pushing the children of the branch to the child
            split->A = branch->A;
            split->C = branch->C;
            split->G = branch->G;
            split->T = branch->T;
            split->N = branch->N;
            // updating the parent branch
            branch->A = NULL;
            branch->C = NULL;
            branch->G = NULL;
            branch->T = NULL;
            branch->N = NULL;
            branch->end = i - 1;

            // creating the new branch
            node_count++;
            node *new_branch = new node;
            new_branch->start = index;
            new_branch->end = subject_length - 1;

            // splitting the branch
            switch (subject[i])
            {
            case 'A':
                branch->A = split;
                break;
            case 'C':
                branch->C = split;
                break;
            case 'G':
                branch->G = split;
                break;
            case 'T':
                branch->T = split;
                break;
            default:
                branch->N = split;
                break;
            }

            // inserting the new branch
            switch (subject[index])
            {
            case 'A':
                branch->A = new_branch;
                break;
            case 'C':
                branch->C = new_branch;
                break;
            case 'G':
                branch->G = new_branch;
                break;
            case 'T':
                branch->T = new_branch;
                break;
            default:
                branch->N = new_branch;
                break;
            }
        }
    }
    return;
}

/**
 * @brief Search for a query string in the suffix tree.
 * @param query The query string to search for.
 * @return True if the query string is found in the suffix tree, false otherwise.
 */
bool Suffix_Tree::search(char *query)
{
    bool found = 0;
    search_helper(query, root, 0, found);
    return found;
}

/**
 * @brief Helper function to search for a query string in the suffix tree.
 * @param query The query string to search for.
 * @param root The root node of the suffix tree.
 * @param index The index of the query string to start searching from.
 * @param found A boolean flag to indicate if the query string is found.
 */
void Suffix_Tree::search_helper(char *query, node *root, int index, bool &found)
{
    bool debug = 0;
    // if we reach the end of the subject, then we are done.
    if (index == subject_length || index > subject_length)
    {
        if (debug)
        {
            cout << "Out of bounds" << endl;
        }
        return;
    }

    if (root == NULL)
    {
        return;
    }

    // find the branch to traverse down
    if (debug)
    {
        cout << "Looking for branch " << query[index] << endl;
    }
    node *branch = NULL;
    switch (query[index])
    {
    case 'A':
        if (root->A != NULL)
        {
            if (debug)
                cout << "Branch A" << endl;
            branch = root->A;
        }
        break;
    case 'C':
        if (root->C != NULL)
        {
            if (debug)
                cout << "Branch C" << endl;
            branch = root->C;
        }
        break;
    case 'G':
        if (root->G != NULL)
        {
            if (debug)
                cout << "Branch G" << endl;
            branch = root->G;
        }
        break;
    case 'T':
        if (root->T != NULL)
        {
            if (debug)
                cout << "Branch T" << endl;
            branch = root->T;
        }
        break;
    default:
        if (root->N != NULL)
        {
            if (debug)
                cout << "Branch N" << endl;
            branch = root->N;
        }
        break;
    }

    // if the branch doesn't exist, then we can stop the search.
    if (branch == NULL)
    {
        if (debug)
            cout << "branch doesn't exist" << endl;
        found = false;
        return;
    }
    // if the branch does exist, then we need to match the query to the branch.
    else
    {
        int i = branch->start;
        while (subject[i] == query[index] && i <= branch->end && index < subject_length)
        {
            if (debug)
                cout << "subject[i]: " << subject[i] << " query[index]: " << query[index] << endl;
            index++;
            i++;
        }
        if (debug)
            cout << "index: " << index << " strlen(query): " << strlen(query) << endl;

        if (index == strlen(query))
        {
            if (debug)
                cout << "found" << endl;
            found = true;
            return;
        }
        else if (i > branch->end)
        {
            if (debug)
                cout << "traversing down branch" << endl;
            search_helper(query, branch, index, found);
        }
    }
    return;
}

/**
 * @brief Print the suffix tree.
 */
void Suffix_Tree::print_tree()
{
    print_tree_helper(root);
}

/**
 * @brief Helper function to print the suffix tree.
 * @param root The root node of the suffix tree.
 */
void Suffix_Tree::print_tree_helper(node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << "start: " << root->start << " end: " << root->end << endl;
    print_tree_helper(root->A);
    print_tree_helper(root->C);
    print_tree_helper(root->G);
    print_tree_helper(root->T);
    print_tree_helper(root->N);
    return;
}
