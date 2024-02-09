#include "queries_bl.h"

using namespace std;

/**
 * Returns a pointer to the hash table.
 * @return Pointer to the hash table.
 */
HashNode **QUERIES_BL::getHashTable()
{
    return hash_table;
}

/**
 * @brief Constructs a new QUERIES_BL object with the given hash table size.
 *
 * @param hash_table_size The size of the hash table to be created.
 */
QUERIES_BL::QUERIES_BL(long hash_table_size, int seed_length, int match, int mismatch, int gap)
{
    this->table_size = hash_table_size;
    this->hash_table = new HashNode *[table_size];
    for (long i = 0; i < table_size; i++)
    {
        hash_table[i] = NULL;
    }
    this->seed_length = seed_length;
    this->queries = queries;
    this->match = match;
    this->mismatch = mismatch;
    this->gap = gap;
}

/**
 * @brief Destructor for QUERIES_BL class. Deletes all the nodes in the hash table.
 *
 */
QUERIES_BL::~QUERIES_BL()
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

void QUERIES_BL::loadQuerySeeds(char **queries, long long num_queries, int query_length)
{
    this->queries = queries;
    printf("Loading query seeds...\n");
    for (long long i = 0; i < num_queries; i++)
    {
        for (int j = 0; j < query_length - seed_length + 1; j++)
        {
            insert(queries[i] + j, i);
            total_seeds++;
        }
    }
    return;
}

void QUERIES_BL::loadSubjectSeeds(char *subject, long long subject_length)
{
    this->subject = subject;
    printf("Loading subject seeds...\n");
    for (long long i = 0; i < subject_length - seed_length + 1; i++)
    {
        insert(subject + i, i);
        total_seeds++;
        // cout<<"\t\r"<<i<<" / "<<subject_length - seed_length + 1<<" seeds loaded.";
    }
    return;
}

/**
 * Inserts a new key into the hash table.
 *
 * @param key The key to insert.
 */
void QUERIES_BL::insert(char *key, long long query_index)
{
    HashNode *new_node = new HashNode;
    new_node->next = NULL;
    new_node->key = new char[seed_length + 1];
    new_node->index = query_index;

    // copy the seed to the node.
    memcpy(new_node->key, key, seed_length);
    new_node->key[seed_length] = '\0';

    // find the radix hash value of the first half of the string.
    long index = hash(new_node->key);

    new_node->next = hash_table[index];
    hash_table[index] = new_node;

    // insert the new node into the hash table.
    // insertNode(index, new_node);
    return;
}

/**
 * @brief Calculates the hash value of a given key using radix hashing.
 *
 * @param key The key to be hashed.
 * @return The hash value of the key.
 */
long QUERIES_BL::hash(char *key)
{
    long hash = 0;

    long weight = 1;
    for (int i = seed_length - 1; i >= 0; i--)
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

        hash += radix_val * weight;
        weight *= RADIX;
    }

    return hash % table_size;
}

/**
 * Inserts a new node into the hash table at the specified index.
 * If there is already a node at that index, the new node is added to the front of the linked list.
 * @param index The index in the hash table where the new node should be inserted.
 * @param new_node A pointer to the new node to be inserted.
 */
void QUERIES_BL::insertNode(long index, HashNode *new_node)
{
    if (hash_table[index] == NULL)
    {
        hash_table[index] = new_node;
    }
    else
    {
        new_node->next = hash_table[index];
        hash_table[index] = new_node;
        // recordCollison();
    }
    return;
}

/**
 * @brief Searches for a given key in the hash table.
 *
 * @param key The key to search for.
 * @return The index of the key in the hash table, or -1 if the key is not found.
 */
long long QUERIES_BL::searchGeomeinQueries(char *key, int mismatch_threshold)
{
    long long match_index = -1;

    int max_score = 0;

    for (int i = 0; i < 16 - 11 + 1; i++)
    {
        long index = hash(key);
        HashNode *current = hash_table[index];
        while (current != NULL)
        {
            if (memcmp(key + i, current->key, seed_length) == 0)
            {
                int score = needleman_wunsch(key, queries[current->index], query_length, query_length);

                if (score >= max_score)
                {
                    max_score = score;
                    match_index = current->index;
                }
            }
            current = current->next;
        }
    }

    return max_score >= ((query_length - mismatch_threshold) * match) + (mismatch_threshold * gap) ? match_index : -1;
}

long long QUERIES_BL::searchQueriesinGenome(char *query, int query_length, int mismatch_threshold)
{
    this->query_length = query_length;
    long long hits = 0;
    int max_score = 0;
    long long match_index = -1;

    for (int i = 0; i < (query_length - seed_length) + 1; i++)
    {
        long index = hash(query + i);
        HashNode *current = hash_table[index];
        while (current != NULL)
        {
            if (memcmp(query + i, current->key, seed_length) == 0)
            {
                int score = needleman_wunsch(query, subject + current->index, query_length, query_length);
                if (score >= max_score)
                {
                    max_score = score;
                    match_index = current->index;
                    hits++;
                }
            }
            current = current->next;
        }
    }

    return max_score >= ((query_length - mismatch_threshold) * match) + (mismatch_threshold * gap) ? match_index : -1;
}

/**
 * @brief Prints the contents of the hash table.
 *
 */
void QUERIES_BL::printHashTable()
{
    for (int i = 0; i < table_size; i++)
    {
        HashNode *temp = hash_table[i];
        cout << i << ": ";
        while (temp != NULL)
        {
            cout << temp->key << " " << temp->index << " - ";
            temp = temp->next;
        }
        cout << endl;
    }
}

int QUERIES_BL::needleman_wunsch(char *query, char *target, int query_length, int target_length)
{
    int current_mismatched = 0;
    int score = 0;
    int **similarity_matrix = new int *[query_length + 1];
    try
    {
        for (int i = 0; i <= query_length; i++)
        {
            similarity_matrix[i] = new int[target_length + 1];
        }

        for (int row = 0; row <= query_length; row++)
        {
            similarity_matrix[row][0] = row * gap;
        }

        for (int col = 0; col <= target_length; col++)
        {
            similarity_matrix[0][col] = col * gap;
        }

        for (int i = 0; i < query_length; i++)
        {
            for (int j = 0; j < target_length; j++)
            {
                int diagonal = similarity_matrix[i][j] + (query[i] == target[j] ? match : mismatch);
                int top = similarity_matrix[i][j + 1] + gap;
                int left = similarity_matrix[i + 1][j] + gap;

                if (diagonal >= top && diagonal >= left)
                {
                    similarity_matrix[i + 1][j + 1] = diagonal;
                }
                else if (top >= diagonal && top >= left)
                {
                    similarity_matrix[i + 1][j + 1] = top;
                }
                else
                {
                    similarity_matrix[i + 1][j + 1] = left;
                }
                if (i == j and query[i] != target[j])
                {
                    current_mismatched++;
                }

                if (current_mismatched > 2)
                {
                    for (int i = 0; i <= query_length; i++)
                    {
                        delete[] similarity_matrix[i];
                    }
                    delete[] similarity_matrix;
                    return 0;
                }
            }
        }

        total_hits++;
        score = similarity_matrix[query_length][target_length];
    }
    catch (...)
    {
        cout << "Error in Needleman Wunsch" << endl;
    }

    for (int i = 0; i <= query_length; i++)
    {
        delete[] similarity_matrix[i];
    }
    delete[] similarity_matrix;

    return score;
}

long long QUERIES_BL::getTotalHits()
{
    return total_hits;
}
