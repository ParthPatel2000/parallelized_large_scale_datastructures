#ifndef QUERIES_HT_H
#define QUERIES_HT_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define KEY_SIZE 16
#define RADIX 5
#define QUERY_SIZE 16

using namespace std;

struct HashNode
{
    long key_collisions;
    char key[KEY_SIZE + 1];
    HashNode *next;
};

struct human
{
    string name;
    int age;
    int weight;
    char sex;
};

human ronak = new human;


class QUERY_HT
{
private:
    HashNode **hash_table;
    long table_size = 0;
    int key_length = 0;
    long collision_count = 0;
    long max_collisions = 0;
    long most_common_key = -1;
    long total_queries = 0;
    long last_key_index = -1;
    int debug = 0;

    void insertNode(long index, HashNode *new_node);
    void recordCollison();
public:
    QUERY_HT(long hash_table_size);
    void readQueries(ifstream &query_file_ptr);
    void insert(char *key);
    long hash(char *key);
    long search(char *key);
    long getCollisionCount();
    HashNode **getHashTable();
    void printHashTable();
    ~QUERY_HT();
};

#endif