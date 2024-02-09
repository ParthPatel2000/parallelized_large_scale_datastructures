#include <iostream>
#include <fstream>
#include <ctime>
#include <pthread.h>
#include <thread>
#include <chrono>
#include <string.h>
#include <omp.h>
#include "genome_functions.h"
#include "queries_reader.h"
#include "queries_nw.h"
#include "queries_bl.h"

int total_found = 0;

char *randomStringGen(long long size);
void part1(long long genome_string_len, char *genome);
void part2(long long genome_string_len, char *genome);

genomeFunctions *genome_reader = NULL;
QUERIES_NW *queries_nw = NULL;
QUERIES_BL *queries_bl = NULL;
QUERIES_READER *queries_reader = NULL;

int main(int argc, char **argv)
{

    char *genome_file_path = NULL;
    char *query_file_path = NULL;
    long long search_count = 0;
    int match = 2;
    int mismatch = -1;
    int gap = -1;
    int hash_table_size = 10e7;
    int seed_length = 11;
    char *method = NULL;
    char *search_type = NULL;
    char *genome = NULL;

    if (argc != 6)
    {
        cout << "Usage: ./executable <genome_file_path> <query_file_path> <NW/(BLAST)> <random/(normal)> <number of searches>" << endl
             << "OPTIONAL ARGS: <Match (2)> <Mismatch (-1)> <Gap (-1)>" << endl;
        cout << "values in (*) are default values." << endl;
        cout << "All args are case sensitive" << endl;
        cout << "Example: ./executable genome.txt queries.txt NW random 1000" << endl;
        cout << "Example: ./executable genome.txt queries.txt BLAST normal 1000 2 -1 -1" << endl;

        return 0;
    }

    genome_file_path = argv[1];
    query_file_path = argv[2];
    method = argv[3];
    search_type = argv[4];
    search_count = atoll(argv[5]);
    genome_reader = new genomeFunctions;

    if (argc == 9)
    {
        match = atoi(argv[6]);
        mismatch = atoi(argv[7]);
        gap = atoi(argv[8]);
    }

    if (strcmp(search_type, "random") == 0)
    {
        cout << "Random search" << endl;
        genome = randomStringGen(search_count);
    }
    else
    {
        cout << "Normal search" << endl;
        // creating the objects and reading the genome data into an array
        genome_reader->readGenomeData(genome_file_path);
        srand(time(NULL));
        long long index = rand() % (genome_reader->getSize() - search_count + 1);
        genome = genome_reader->getGenomeData() + index;
        genome[search_count] = '\0';
    }

    // creating the object and reading the queries into a 2D array
    queries_reader = new QUERIES_READER(query_file_path, 16);

    // Calling the methods based on the arguments
    if (strcmp(method, "NW") == 0)
    {
        // creating needleman Wunsch object
        queries_nw = new QUERIES_NW(match, mismatch, gap);
        queries_nw->setGenome(genome, search_count);
        queries_nw->setQueries(queries_reader->getQueries(), queries_reader->getQueryLength(), queries_reader->getQueryCount());
        part1(search_count, genome);
    }
    else
    {
        // creating the BLAST object
        queries_bl = new QUERIES_BL(hash_table_size, seed_length, match, mismatch, gap);
        part2(search_count, genome);
    }
    delete queries_bl;
    delete queries_nw;
    delete genome_reader;

    return 0;
}

char *randomStringGen(long long size)
{
    char elements[] = {'A', 'C', 'G', 'T'};
    char *random_string = new char[size + 1];
    srand(time(NULL));
    for (long long i = 0; i < size; i++)
    {
        random_string[i] = elements[rand() % 4];
    }
    random_string[size] = '\0';
    return random_string;
}

void part1(long long genome_string_len, char *genome)
{
    clock_t start, end;

    start = clock();
    for (int i = 0; i < genome_string_len - queries_reader->getQueryLength() + 1; i++)
    {
        long long match_index = -1;
        match_index = queries_nw->search(genome + i, 2);
        // cout << "Match index: " << match_index << endl;
    }
    end = clock();
    cout << "From :" << genome_string_len - queries_reader->getQueryLength() + 1 << " Fragment , Hits in Queries: " << queries_nw->getTotalHits() << endl;
    cout << "Time taken to find " << genome_string_len - queries_reader->getQueryLength() + 1 << " query: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
    return;
}

void part2(long long genome_string_len, char *genome)
{

    clock_t start, end;

    start = clock();
    queries_bl->loadQuerySeeds(queries_reader->getQueries(), queries_reader->getQueryCount(), queries_reader->getQueryLength());
    end = clock();

    cout << "Time taken to load " << queries_reader->getQueryCount() << " queries " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    start = clock();
#pragma omp parallel for num_threads(omp_get_num_procs())
    for (long long i = 0; i < genome_string_len - 15; i++)
    {
        queries_bl->searchGeomeinQueries(genome + i, 2);
    }
    end = clock();

    cout << endl
         << "From :" << genome_string_len - queries_reader->getQueryLength() + 1 << " Fragments , Hits in Queries: " << queries_bl->getTotalHits() << endl;
    cout << "Time taken to find " << genome_string_len - queries_reader->getQueryLength() + 1 << " Fragments in Queries: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return;
}