#include "queries_ht.h"

using namespace std;

/**
 * Returns a pointer to the hash table.
 * @return Pointer to the hash table.
 */
HashNode **QUERY_HT::getHashTable()
{
    return hash_table;
}

/**
 * @brief Records a collision in the hash table.
 *
 */
void QUERY_HT::recordCollison()
{
    collision_count++;
}

/**
 * Returns the number of collisions that occurred during hash table operations.
 *
 * @return The number of collisions.
 */
long QUERY_HT::getCollisionCount()
{
    return collision_count;
}

/**
 * @brief Constructs a new QUERY_HT object with the given hash table size.
 *
 * @param hash_table_size The size of the hash table to be created.
 */
QUERY_HT::QUERY_HT(long hash_table_size)
{
    table_size = hash_table_size;
    hash_table = new HashNode *[table_size];
    for (long i = 0; i < table_size; i++)
    {
        hash_table[i] = NULL;
    }

    key_length = 16;
}

/**
 * @brief Reads queries from a file and inserts them into a hash table.
 *
 * @param query_file_ptr Input file stream containing queries.
 */
void QUERY_HT::readQueries(ifstream &query_file_ptr)
{
    char *query = new char[QUERY_SIZE + 1];
    while (query_file_ptr.getline(query, QUERY_SIZE + 4))
    {
        if (query[0] != '>')
        {
            query[QUERY_SIZE] = '\0';
            total_queries++;
            insert(query);
        }
    }
    cout << "created hash table" << endl;
    cout << "total queries: " << total_queries << endl;
    cout << "total collisions: " << collision_count << endl;
    delete[] query;
    return;
}

/**
 * Inserts a new key into the hash table.
 *
 * @param key The key to insert.
 */
void QUERY_HT::insert(char *key)
{
    HashNode *new_node = new HashNode;
    new_node->next = NULL;

    // copy the last half of the string into the new node.
    strcpy(new_node->key, key);

    // find the radix hash value of the first half of the string.
    long index = hash(key);

    // insert the new node into the hash table.
    insertNode(index, new_node);
    return;
}

/**
 * @brief Calculates the hash value of a given key using radix hashing.
 *
 * @param key The key to be hashed.
 * @return The hash value of the key.
 */
long QUERY_HT::hash(char *key)
{
    long hash = 0;

    int weight = 0;
    for (int i = key_length - 1; i >= 0; i--)
    {
        int radix_val = 0;
        // this switch statement assigns a radix value to each character in the string.
        switch (key[i])
        {
        case 'A':
            radix_val = 0;
            break;
        case 'C':
            radix_val = 1;
            break;
        case 'G':
            radix_val = 2;
            break;
        case 'T':
            radix_val = 3;
            break;
        default:
            radix_val = 4;
            break;
        }
        // this creates a hash value that takes into account the position of the character in the string.

        hash += (radix_val)*pow(RADIX, weight);
        weight++;
    }

    return hash % table_size;
}

/**
 * Inserts a new node into the hash table at the specified index.
 * If there is already a node at that index, the new node is added to the front of the linked list.
 * @param index The index in the hash table where the new node should be inserted.
 * @param new_node A pointer to the new node to be inserted.
 */
void QUERY_HT::insertNode(long index, HashNode *new_node)
{
    if (hash_table[index] == NULL)
    {
        hash_table[index] = new_node;
    }
    else
    {
        new_node->next = hash_table[index];
        hash_table[index] = new_node;
        recordCollison();
    }
    return;
}

/**
 * @brief Searches for a given key in the hash table.
 *
 * @param key The key to search for.
 * @return The index of the key in the hash table, or -1 if the key is not found.
 */
long QUERY_HT::search(char *key)
{
    long index = hash(key);

    HashNode *current = hash_table[index];
    while (current != NULL)
    {

        if (strcmp(current->key, key) == 0)
        {
            return index;
        }

        current = current->next;
    }
    return -1;
}

/**
 * @brief Destructor for QUERY_HT class. Deletes all the nodes in the hash table.
 *
 */
QUERY_HT::~QUERY_HT()
{
    for (int i = 0; i < table_size; i++)
    {
        HashNode *current = hash_table[i];
        while (current != NULL)
        {
            HashNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] hash_table;
}


/**
 * @brief Prints the contents of the hash table.
 *
 */
void QUERY_HT::printHashTable()
{
    for (int i = 0; i < table_size; i++)
    {
        HashNode *temp = hash_table[i];
        cout << i << ": ";
        while (temp != NULL)
        {
            cout << temp->key << " - ";
            temp = temp->next;
        }
        cout << endl;
    }
}