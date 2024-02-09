#include <iostream>
#include <fstream>
#include <ctime>
#include <pthread.h>
#include <thread>
#include <string.h>
#include "genome_functions.h"
#include "queries_ht.h"

int total_found = 0;
pthread_mutex_t mutex;

struct thread_data
{
    int thread_id;
    char *genome_data;
    long long start_index;
    long long end_index;
    QUERY_HT *hash_table;
};

void *thread_routine(void *arg)
{
    int found = 0;
    thread_data *data = (thread_data *)arg;
    for (long long i = data->start_index; i < data->end_index; i++)
    {
        char *subsequence = new char[17];
        strncpy(subsequence, &data->genome_data[i], 16);
        if (data->hash_table->search(subsequence) != -1)
        {
            found++;
        }
        delete[] subsequence;
    }
    pthread_mutex_lock(&mutex);
    total_found += found;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char **argv)
{

    char *genome_file_path;
    char *query_file_path;
    unsigned int hash_table_size;
    clock_t startTime, endTime;
    char *justhash;

    if (argc != 5)
    {
        cout << "Usage: ./executable <genome_file_path> <query_file_path>  <(integer)hash_table_size> <hash/search>" << endl;
        return 0;
    }

    genome_file_path = argv[1];
    query_file_path = argv[2];
    hash_table_size = atoi(argv[3]);
    justhash = argv[4];

    // opening the files
    ifstream genome_file_ptr(genome_file_path);
    ifstream query_file_ptr(query_file_path);

    // creating the objects and reading the genome data into an array
    genomeFunctions *genome_reader = new genomeFunctions;
    genome_reader->readGenomeData(genome_file_ptr);

    char *genome_data = genome_reader->getGenomeData();
    long long genome_size = genome_reader->getSize();

    startTime = clock();

    QUERY_HT *hash_table = new QUERY_HT(hash_table_size);
    hash_table->readQueries(query_file_ptr);

    endTime = clock();
    cout << "Time taken to create hash table: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    if (strcmp(justhash, "hash"))
    {

        // searching the queries
        thread thread;
        int thread_count = thread.hardware_concurrency();

        cout << "searching queries:\n"
             << endl;

        // finding the first 15 queries sequentially

        int print_15 = 15;
        int i = 0;
        while (print_15)
        {
            char *subsequence = new char[17];
            strncpy(subsequence, &genome_data[i], 16);
            subsequence[16] = '\0';
            long index = hash_table->search(subsequence);
            if (index != -1)
            {
                cout << "subsequence "<< i <<" :" << subsequence << " found." << endl;
                delete[] subsequence;
                i++;
                print_15--;
            }
        }

        // Threads implementation
        pthread_mutex_init(&mutex, NULL);

        startTime = clock();
        pthread_t *threads = new pthread_t[thread_count];
        for (int i = 0; i < thread_count; i++)
        {

            if (i != thread_count - 1)
            {
                thread_data *data = new thread_data;
                data->thread_id = i;
                data->genome_data = genome_data;
                data->start_index = i * (genome_size - 15) / thread_count;
                data->end_index = (i + 1) * (genome_size - 15) / thread_count;
                data->hash_table = hash_table;
                pthread_create(&threads[i], NULL, thread_routine, (void *)data);
            }
            else
            {
                thread_data *data = new thread_data;
                data->thread_id = i;
                data->genome_data = genome_data;
                data->start_index = i * (genome_size - 15) / thread_count;
                data->end_index = (i + 1) * (genome_size - 15) / thread_count + (genome_size - 15) % thread_count;
                data->hash_table = hash_table;
                pthread_create(&threads[i], NULL, thread_routine, (void *)data);
            }
        }
        cout << "\nthreads created: " << thread_count << endl;

        for (int i = 0; i < thread_count; i++)
        {
            pthread_join(threads[i], NULL);
        }
        endTime = clock();
        pthread_mutex_destroy(&mutex);
        cout << "total fragments found: " << total_found << endl;
        cout << "\nTime taken to search " << genome_size - 15 << " fragments: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    }
    delete genome_reader;
    delete hash_table;
    cout << "Program ended" << endl;

    return 0;
}