#ifndef QUERIES_NW_H
#define QUERIES_NW_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include "queries_reader.h"

using namespace std;

class QUERIES_NW
{
private:
    char **queries = NULL;
    char *genome_string = NULL;
    long long genome_length = 0;
    int query_length = 0;
    int query_count = 0;
    long long total_hits = 0;

public:
    int match = 2;
    int mismatch = -1;
    int gap = -1;

    QUERIES_NW();
    QUERIES_NW(int match, int mismatch, int gap);
    ~QUERIES_NW();

    long long getTotalHits();

    void setQueries(char **queries, int query_length, int query_count);
    void setGenome(char *genome, long long genome_length);
    int needleman_wunsch(char *query, char *genome, int query_length, int genome_length);
    long long search(char *fragment, int mismatch_threshold);
    char **getQueries();
};

#endif // QUERIES_NW_H
