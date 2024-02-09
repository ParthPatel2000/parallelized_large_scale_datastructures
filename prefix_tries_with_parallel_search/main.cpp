#include <iostream>
#include <fstream>
#include <ctime>
// #include <pthread.h>
#include <thread>
#include <chrono>
#include <string.h>
#include <omp.h>
#include "genome_functions.h"
#include "prefix_tries.h"

char **create_fragments(char *genome, long fragment_count, int fragment_length);
char **create_fragments_error(char *genome, long fragment_count, int fragment_length, int error_rate);

int main(int argc, char **argv)
{
    char *genome_file_path = NULL;
    int genome_size = 50000;
    long fragment_count = 0;
    int query_length = 36;
    string search_type;
    char *genome = NULL;
    char **fragments = NULL;
    int matches = 0;
    int mismatch_tolerance = 1;
    int error_rate = 5;

    if (argc < 4)
    {
        cout << "Invalid number of arguments" << endl;
        cout << "Usage: ./main --genome <genome_file_path> --fragments <fragment_count> --search <search_type>" << endl;
        cout << "Search types: basic, mutate" << endl;
        cout << "Example: ./main --genome genome.txt --fragments 5000 --search basic" << endl;
        cout << "Optional arguments: --mismatch <mismatch_tolerance> --error <error_rate>" << endl;
        cout << "Example: ./main --genome genome.txt --fragments 5000 --mismatch 1 --search mutate --error 5" << endl;
        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "--search")
        {
            string type = argv[i + 1];
            if (type == "basic")
            {
                search_type = argv[i + 1];
            }
            else if (type == "mutate")
            {
                search_type = argv[i + 1];
            }
            else
            {
                cout << "Invalid search type" << endl;
                return 0;
            }
        }
        if (arg == "--genome")
        {
            genome_file_path = argv[i + 1];
        }
        if (arg == "--fragments")
        {
            fragment_count = atol(argv[i + 1]);
        }
        if (arg == "--mismatch")
        {
            mismatch_tolerance = atoi(argv[i + 1]);
        }
        if (arg == "--error")
        {
            error_rate = atoi(argv[i + 1]);
        }
    }

    if (genome_file_path == NULL || search_type == "" || fragment_count == 0)
    {
        cout << "Invalid arguments" << endl;
        cout << "Usage: ./main --genome <genome_file_path> --fragments <fragment_count> --search <search_type>" << endl;
        cout << "Search types: basic, mutate" << endl;
        cout << "Example: ./main --genome genome.txt --fragments 5000 --search basic" << endl;
        cout << "Optional arguments: --mismatch <mismatch_tolerance> --error <error_rate>" << endl;
        cout << "Example: ./main --genome genome.txt --fragments 5000 --mismatch 1 --search mutate --error 5" << endl;
        return 0;
    }
    cout << "------------------------------------------------------------------" << endl;

    // Loading the genome into the memory
    genomeFunctions *genomeFunctionsObject = new genomeFunctions();
    genomeFunctionsObject->readGenomeData(genome_file_path);
    genome = genomeFunctionsObject->getrandomfragment(genome_size);

    // Part A
    // 5k fragments
    cout << "Search Type: " << search_type << endl;
    cout << "Mismatch tolerance: " << mismatch_tolerance << endl;

    if (search_type == "basic")
    {
        fragments = create_fragments(genome, fragment_count, query_length);
        cout << "\nNumber of fragments: " << fragment_count << endl;
        Prefix_Trie *prefix_tries = new Prefix_Trie(fragments, fragment_count);
        cout << "Number of nodes: " << prefix_tries->get_node_count() << endl;
        for (int i = 0; i < genome_size - query_length + 1; i++)
        {
            char *temp = new char[query_length + 1];
            memcpy(temp, genome + i, query_length);
            temp[query_length] = '\0';
            matches += prefix_tries->search(temp, mismatch_tolerance);
            delete temp;
        }
        cout << "Number of matches: " << matches << endl;

        delete prefix_tries;
        delete[] fragments;
        delete genomeFunctionsObject;
    }
    // Part B 5% Base Error rate
    else
    {
        cout << "Error rate: " << error_rate << "%" << endl
             << endl;

        fragments = create_fragments_error(genome, fragment_count, query_length, error_rate);
        cout << "Number of fragments: " << fragment_count << endl;
        Prefix_Trie *prefix_tries = new Prefix_Trie(fragments, fragment_count);
        cout << "Number of nodes: " << prefix_tries->get_node_count() << endl;
        for (int i = 0; i < genome_size - query_length + 1; i++)
        {
            char *temp = new char[query_length + 1];
            memcpy(temp, genome + i, query_length);
            temp[query_length] = '\0';
            matches += prefix_tries->search(temp, mismatch_tolerance);
            delete temp;
        }
        cout << "Number of matches: " << matches << endl;

        delete prefix_tries;
        delete[] fragments;
        delete genomeFunctionsObject;
    }
    cout << "------------------------------------------------------------------" << endl;

    // // Testing
    // // testing the prefix trie
    // fragments = new char *[6];
    // fragments[0] = "ACGTA";
    // fragments[1] = "ACTGT";
    // fragments[2] = "ACTGG";
    // fragments[3] = "ACTTA";
    // fragments[4] = "ACTGC";
    // fragments[5] = "ACAAA";
    // Prefix_Trie *prefix_tries = new Prefix_Trie(fragments, 6);
    // prefix_tries->print();
    // cout << prefix_tries->get_node_count() << endl;
    // cout << "ACAAA" << (prefix_tries->search("ACAAA\0", 1) ? " Found" : " Not found") << endl;
    // cout << "ACTTA" << (prefix_tries->search("ACTTA\0", 1) ? " Found" : " Not found") << endl;
    // cout << "ACTGA" << (prefix_tries->search("ACTGA\0", 1) ? " Found" : " Not found") << endl;
    // matches = prefix_tries->search("", 1);

    // char subject[] = "";
    // for (int i = 0; i < 6; i++)
    // {
    //     char *temp = new char[6];
    //     memcpy(temp, subject + i, 5);
    //     temp[5] = '\0';
    //     // matches+=prefix_tries->search(temp, 1);
    //     cout<<temp<<(prefix_tries->search(temp, 1)?" Found":" Not found")<<endl;
    // }
    // cout << "Number of matches: " << matches << endl;

    // // Testing the mutator function
    // genome = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    // fragments = create_fragments_error(genome, 100, 36, 10);
    // for (int i = 0; i < 100; i++)
    // {
    //     cout << fragments[i] << endl;
    // }

    // // Testing the genome functions
    // genomeFunctions *genomeFunctionsObject = new genomeFunctions();
    // genomeFunctionsObject->readGenomeData(genome_file_path);
    // genome = genomeFunctionsObject->getGenomeData();
    // genome[50000] = '\0';
    // fragments = new char *[5000];
    // for (int i = 0; i < 5000; i++)
    // {
    //     fragments[i] = new char[37];
    //     memcpy(fragments[i], genome + i, 36);
    //     fragments[i][36] = '\0';
    // }
    // Prefix_Trie *prefix_tries = new Prefix_Trie(fragments, 5000);
    // cout << prefix_tries->get_node_count() << endl;
    // for (int i = 0; i < 50000 - 36 + 1; i++)
    // {
    //     char *temp = new char[37];
    //     memcpy(temp, genome + i, 36);
    //     temp[36] = '\0';
    //     matches += prefix_tries->search(temp, 1);
    //     delete temp;
    // }
    // cout << "Number of matches: " << matches << endl;

    // // Testing ends

    return 0;
}

char **create_fragments_error(char *genome, long fragment_count, int fragment_length, int error_rate)
{
    srand(time(NULL));
    char **fragments = new char *[fragment_count];
    char nucleotides[5] = {'A', 'C', 'G', 'T', 'N'};
    for (long i = 0; i < fragment_count; i++)
    {
        fragments[i] = new char[fragment_length + 1];
        // pick a random index in the genome
        long index = rand() % (strlen(genome) - fragment_length+1);

        // generating a fragment mutating at error rate
        for (int j = 0; j < fragment_length; j++)
        {
            // only mutate 1 time in 1/error_rate times
            // so for 5% error rate, mutate 1 time in 20 times
            int mutate = rand() % 100 / error_rate;
            if (mutate == 0)
            {
                // guess a random nucleotide
                int nucleotide = rand() % 5;
                // make sure it's not the same as the original
                while (genome[index + j] == nucleotides[nucleotide])
                {
                    nucleotide = rand() % 5;
                }

                // add the new nucleotide to the fragment
                switch (nucleotide)
                {
                case 0:
                    fragments[i][j] = nucleotides[1];
                    break;
                case 1:
                    fragments[i][j] = nucleotides[2];
                    break;
                case 2:
                    fragments[i][j] = nucleotides[3];
                    break;
                case 3:
                    fragments[i][j] = nucleotides[4];
                    break;
                case 4:
                    fragments[i][j] = nucleotides[0];
                    break;
                default:
                    break;
                }
            }
            else
            {
                fragments[i][j] = genome[index + j];
            }
        }
        fragments[i][fragment_length] = '\0';
    }
    return fragments;
}

char **create_fragments(char *genome, long fragment_count, int fragment_length)
{
    char **fragments = new char *[fragment_count];
    srand(time(NULL));
    for (long i = 0; i < fragment_count; i++)
    {
        fragments[i] = new char[fragment_length + 1];
        long index = rand() % (strlen(genome) - fragment_length+1);
        memcpy(fragments[i], genome + index, fragment_length);
        fragments[i][fragment_length] = '\0';
    }
    return fragments;
}