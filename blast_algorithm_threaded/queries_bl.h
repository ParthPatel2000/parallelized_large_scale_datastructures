#ifndef QUERIES_BL_H
#define QUERIES_BL_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define RADIX 5

struct HashNode
{
    long key_collisions;
    char *key;
    long long index;
    HashNode *next;
};

class QUERIES_BL
{

private:
    HashNode **hash_table;
    char **queries = NULL;
    char *subject = NULL;
    long table_size = 60000000;
    int query_length = 16;
    int seed_length = 0;
    int match = 2;
    int mismatch = -1;
    int gap = -1;
    long long total_hits = 0;

    long total_seeds = 0;

    void insertNode(long index, HashNode *new_node);
    void recordCollison();
    int count_numbers(int num);

public:
    long long getTotalHits();
    QUERIES_BL(long hash_table_size, int seed_length, int match = 2, int mismatch = -1, int gap = -1);
    void loadQuerySeeds(char **queries, long long num_queries, int query_length);
    void loadSubjectSeeds(char *subject, long long subject_length);
    long long searchGeomeinQueries(char *key, int mismatch_threshold);
    long long searchQueriesinGenome(char *query, int query_length, int mismatch_threshold);
    void insert(char *key, long long index);
    void printHashTable();
    long hash(char *key);
    int needleman_wunsch(char *query, char *target, int query_length, int target_length);
    HashNode **getHashTable();

    ~QUERIES_BL();
};

#endif
