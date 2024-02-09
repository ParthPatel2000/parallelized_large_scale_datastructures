#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <iomanip>
#include "genome_functions.h"

using namespace std;

/**
 * Set the genome size to a specified value.
 *
 * @param size The size of the genome to be assigned to the private variable "genome_size."
 */
void genomeFunctions::setSize(long long int size)
{
    genome_size = size;
}

/**
 * Get the size of the genome.
 *
 * @return The size of the genome stored in the private variable "genome_size."
 */
long long int genomeFunctions::getSize()
{
    return genome_size;
}

/**
 * Get a reference to the character array containing genome data.
 *
 * @return A reference to the character array holding the genome data.
 */
char *genomeFunctions::getGenomeData()
{
    return genome_data;
}

/**
 * Calculate the size of the genome characters by iterating through the entire file content,
 * skipping the genome headers.
 *
 * @param input_file_pointer Reference to the input file stream.
 * @return The size of the genome characters.
 */
long long int genomeFunctions::countGenomeLength(char * input_file_name)
{
    ifstream input_file_pointer(input_file_name);
    char line[MAX_LINE_LENGTH];

    long long int total_genome_count = 0;

    while (input_file_pointer.getline(line, MAX_LINE_LENGTH))
    {
        if (line[0] != '>')
        {
            for (int i = 0; line[i] != '\0'; i++)
            {
                total_genome_count++;
            }
        }
    }

    return total_genome_count;
}

/**
 * Read the human genome file and perform the following tasks:
 * 1. Count the number of scaffolds.
 * 2. Determine the largest and shortest scaffold with names and lengths.
 * 3. Calculate the average scaffold length.
 *
 * @param input_file_pointer Reference to the input file stream.
 */
void genomeFunctions::readGenomeData(char* input_file_name)
{
    ifstream input_file_pointer(input_file_name);
    try
    {
        if (input_file_pointer.is_open())
        {
            long long int index = 0;

            char line[MAX_LINE_LENGTH]; // Define a maximum line length or use dynamic allocation

            long long int size = genomeFunctions::countGenomeLength(input_file_name);
            input_file_pointer.clear();
            input_file_pointer.seekg(0, ios::beg);

            genome_data = new char[size + 1];
            genomeFunctions::setSize(size);

            while (input_file_pointer.getline(line, MAX_LINE_LENGTH))
            {
                if (line[0] != '>')
                {
                    for (int i = 0; line[i] != '\0'; i++)
                    {
                        genome_data[index++] = line[i];
                    }
                }
            }

            cout << "Genome Length: " << genome_size << endl;

            input_file_pointer.close();
        }
    }
    catch (...)
    {
        cout << "ERROR in readGenomeData function" << endl;
    }
}

/**
 * Compute the number of A, G, C, T characters in the human genome and perform the following tasks:
 * 1. Count the total number of characters in the genome.
 * 2. Calculate the runtime in seconds.
 * 3. Determine the percent of GC content.
 *
 * @param input_file_pointer Reference to the input file stream.
 */
void genomeFunctions::computeCharacters(char *input_file_name)
{
    ifstream input_file_pointer(input_file_name);
    try
    {
        if (input_file_pointer.is_open())
        {
            input_file_pointer.clear();
            input_file_pointer.seekg(0, ios::beg);

            time_t start_time, end_time;
            time(&start_time);

            char line[MAX_LINE_LENGTH]; // Define a maximum line length or use dynamic allocation

            long long int a_count = 0, c_count = 0, g_count = 0,
                          t_count = 0, others_count = 0, genome_size = 0;

            while (input_file_pointer.getline(line, MAX_LINE_LENGTH))
            {
                if (line[0] != '>')
                {
                    for (int i = 0; line[i] != '\0'; i++)
                    {
                        char currentChar = line[i];
                        if (currentChar == 'A')
                            a_count++;
                        else if (currentChar == 'C')
                            c_count++;
                        else if (currentChar == 'G')
                            g_count++;
                        else if (currentChar == 'T')
                            t_count++;
                        else
                            others_count++;
                    }
                    genome_size += strlen(line);
                }
            }

            time(&end_time);

            cout << endl
                << "***********************************************" << endl;
            cout << endl
                << "*            Genome Computation               *" << endl;
            cout << endl
                << "***********************************************" << endl;
            cout << endl
                << "Total characters in the genome" << right << ":" << genome_size << endl;
            cout << endl
                << "Runtime in seconds" << right << ":" << (end_time - start_time) << endl;
            cout << endl
                << "count of GC" << right << ":" << (g_count + c_count) << endl;
            cout << endl
                << "percent of GC" << right << ":" << fixed << ((g_count + c_count) / (double)genome_size) * 100 << "%" << endl;
            cout << endl
                << "count of A" << right << ":" << a_count << endl;
            cout << endl
                << "percent of A" << right << ":" << fixed << (a_count / (double)genome_size) * 100 << "%" << endl;
            cout << endl
                << "count of C" << right << ":" << c_count << endl;
            cout << endl
                << "percent of C" << right << ":" << fixed << (c_count / (double)genome_size) * 100 << "%" << endl;
            cout << endl
                << "count of G" << right << ":" << g_count << endl;
            cout << endl
                << "percent of G" << right << ":" << fixed << (g_count / (double)genome_size) * 100 << "%" << endl;
            cout << endl
                << "count of T" << right << ":" << t_count << endl;
            cout << endl
                << "percent of T" << right << ":" << fixed << (t_count / (double)genome_size) * 100 << "%" << endl;
            cout << endl
                << "Other characters" << right << ":" << others_count << endl;
            cout << endl
                << "percent" << right << ":" << fixed << (others_count / (double)genome_size) * 100 << "%" << endl;

            input_file_pointer.close();
        }
    }
    catch (...)
    {
        cout << "ERROR in computeCharacters function" << endl;
    }
}

/**
 * Destructor for the genomeFunctions class.
 * Deallocates memory used for genome data.
 */
genomeFunctions::~genomeFunctions()
{
    delete[] genome_data;
}