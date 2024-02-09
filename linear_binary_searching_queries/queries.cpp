#include <stdio.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "queries.h"

using namespace std;

/**
 * Constructor for the Queries_AR class.
 *
 * This constructor initializes the member variables of the Queries_AR class to their default values.
 * - total_genome_queries: The total number of genome queries is set to 0.
 * - genome_query_length: The default genome query length is set to 32.
 * - genome_size: The genome size is initialized to 0; it will be updated with actual values later.
 * - genome_data: The genome data pointer is set to NULL, serving as a placeholder for genome data.
 * - genome_queries: The genome queries pointer is also set to NULL and will hold an array of genome queries.
 */
Queries_AR::Queries_AR()
{
    total_genome_queries = 0;
    genome_query_length = 32;
    genome_size = 0;
    genome_data = NULL;
    genome_queries = NULL;
}

/**
 * Constructor for the Queries_AR class that takes parameters.
 *
 * This constructor is used to initialize the member variables of the Queries_AR class
 * based on the provided input parameters, and it builds genome queries from an input file.
 *
 * @param fileptr - An input file stream used to read genome query data.
 * @param genome - A pointer to the genome data.
 * @param size - The size of the genome data.
 */
Queries_AR::Queries_AR(ifstream &fileptr, char *genome, long long size) : Queries_AR()
{
    // Initialize genome_size with the provided size.
    genome_size = size;

    // Set the genome_data pointer to point to the provided genome data.
    genome_data = genome;

    // Check if the file stream is open and proceed if it is.
    if (fileptr.is_open())
    {
        char line[READ_LENGTH];
        long long int line_count = 0;

        // Iterate through the lines in the file to count genome queries (indicated by lines starting with '>').
        while (fileptr.getline(line, READ_LENGTH))
        {
            if (line[0] == '>')
            {
                line_count++;
            }
        }

        // Set the total_genome_queries to the counted number of queries.
        total_genome_queries = line_count;

        // Allocate memory for genome_queries to hold an array of pointers for genome queries.
        genome_queries = new char *[total_genome_queries];
    }

    // Print the size of the genome queries for debugging or information.
    // cout << "The size: " << total_genome_queries << endl;
}

/**
 * Read genome queries from an input file.
 *
 * This function reads genome queries from the provided input file stream and stores them in the genome_queries array.
 *
 * @param fileptr - An input file stream from which genome queries are read.
 * @return true if the queries are successfully read, false if there was an issue with the file or queries.
 */
bool Queries_AR::readQueries(ifstream &fileptr)
{
    if (fileptr.is_open())
    {
        // Clear any error flags and set the file pointer to the beginning.
        fileptr.clear();
        fileptr.seekg(0, ios::beg);

        cout << "Reading queries..." << endl;

        char line[READ_LENGTH];

        long long index = 0;

        // Loop through the lines in the file.
        while (fileptr.getline(line, READ_LENGTH))
        {
            if (line[0] != '>')
            {
                // Allocate memory for the current genome query.
                genome_queries[index] = new char[genome_query_length + 1];

                // Copy the characters of the query line to the allocated memory.
                for (int j = 0; j < genome_query_length; j++)
                {
                    genome_queries[index][j] = line[j];
                }

                // Null-terminate the string to create a valid C-string.
                genome_queries[index][genome_query_length] = '\0';

                index++;

                // If the desired number of queries is reached, exit the loop.
                if (index >= total_genome_queries)
                {
                    break;
                }
            }
        }

        // Print the total number of genome queries for debugging or information.
        cout << "Total genome queries: " << total_genome_queries << endl;

        // Return true to indicate that the queries were successfully read.
        return true;
    }

    // Return false if the file is not open or there's an issue with reading queries.
    return false;
}

/**
 * Search for query sequences within the genome data using linear or binary search.
 *
 * This function performs a search for query sequences within the genome data using either
 * linear or binary search based on the `do_linear_search` parameter. It then prints the results.
 *
 * @param do_linear_search - A boolean indicating whether to use linear search (true) or binary search (false).
 * @param subject_fragments_count - The number of subject fragments to search within.
 */
void Queries_AR::searchQueries(bool do_linear_search, long long subject_fragments_count)
{
    char *query_sequence = new char[genome_query_length + 1]; // Allocate memory for the query sequence
    int match_count = 0;                                      // Keep track of the number of matches found

    // Loop through the subject fragments
    for (long long i = 0; i < subject_fragments_count + genome_query_length; i++)
    {
        // Extract a query sequence from the genome data
        for (int j = 0; j < genome_query_length; j++)
        {
            query_sequence[j] = genome_data[i + j];
        }
        query_sequence[genome_query_length] = '\0'; // Null-terminate the query sequence

        // bool match;
        long long match;
        if (do_linear_search)
        {
            match = linearSearch(query_sequence);
        }
        else
        {
            match = binarySearch(query_sequence);
        }

        // If a match is found and we haven't found 10 matches yet, print the result
        if (match!=-1 && match_count < 10)
        {
            cout << "\nFor query number: " << match << endl;
            cout << "Match found:" << query_sequence << " at index: " << i << " in the genome sequence." << endl;
            match_count++;
        }
    }

    // Clean up memory allocated for the query sequence
    delete[] query_sequence;
}

/**
 * Sort the genome queries using the merge sort algorithm.
 *
 * This function provides a high-level interface for sorting the genome_queries array using
 * the merge sort algorithm. It calls the mergeSort function to perform the actual sorting.
 */
void Queries_AR::sortQueries()
{
    // Call the mergeSort function to sort the genome_queries array.
    mergeSort(genome_queries, 0, total_genome_queries - 1);
}

/**
 * Custom comparison function for comparing two strings.
 *
 * This function compares two C-style strings character by character and returns:
 * - A positive integer if str1 is lexicographically greater than str2.
 * - A negative integer if str1 is lexicographically less than str2.
 * - Zero if str1 is equal to str2.
 *
 * @param str1 - The first C-style string to compare.
 * @param str2 - The second C-style string to compare.
 * @return An integer indicating the result of the comparison.
 */
int Queries_AR::customStrcmp(const char *str1, const char *str2)
{
    // Iterate through both strings character by character until a difference is found.
    while (*str1 && (*str1 == *str2))
    {
        ++str1;
        ++str2;
    }

    // Return the difference between the current characters (as integers).
    return static_cast<int>(*str1) - static_cast<int>(*str2);
}

/**
 * Destructor for the Queries_AR class.
 *
 * This destructor is responsible for cleaning up dynamically allocated memory used for genome_queries.
 * It deallocates memory for each individual genome query and the array of pointers to genome queries.
 */
Queries_AR::~Queries_AR()
{
    // Loop through all genome queries and deallocate their memory.
    for (long long i = 0; i < total_genome_queries; i++)
    {
        delete[] genome_queries[i];
    }

    // Deallocate memory for the array of pointers to genome queries.
    delete[] genome_queries;
}

/**
 * Merge two subarrays of genome_queries into a single sorted array.
 *
 * This function takes two subarrays of genome_queries, namely the left_array and right_array,
 * and merges them into a single sorted array within the genome_queries array.
 *
 * @param genome_queries - The array of genome queries being sorted and merged.
 * @param start - The starting index of the range to be merged.
 * @param mid - The middle index of the range to be merged.
 * @param end - The ending index of the range to be merged.
 */
void Queries_AR::merge(char **genome_queries, long long start, long long mid, long long end)
{
    long long left_array_size = mid - start + 1, right_array_size = end - mid;

    char **left_array = new char *[left_array_size],
         **right_array = new char *[right_array_size];

    // Copy data from genome_queries into left_array and right_array.
    for (long long i = 0; i < left_array_size; i++)
    {
        left_array[i] = genome_queries[start + i];
    }

    for (long long j = 0; j < right_array_size; j++)
    {
        right_array[j] = genome_queries[mid + 1 + j];
    }

    long long i = 0, j = 0, k = start;

    // Merge the subarrays back into genome_queries in sorted order.
    while (i < left_array_size && j < right_array_size)
    {
        if (customStrcmp(left_array[i], right_array[j]) < 0)
        {
            genome_queries[k++] = left_array[i++];
        }
        else
        {
            genome_queries[k++] = right_array[j++];
        }
    }

    // Copy any remaining elements from left_array and right_array to genome_queries.
    while (i < left_array_size)
    {
        genome_queries[k++] = left_array[i++];
    }

    while (j < right_array_size)
    {
        genome_queries[k++] = right_array[j++];
    }
}

/**
 * Sort the genome_queries array using the merge sort algorithm.
 *
 * This function implements the merge sort algorithm to sort the genome_queries array
 * in ascending order. It divides the array into smaller subarrays, recursively sorts them,
 * and then merges them back into a single sorted array.
 *
 * @param genome_queries - The array of genome queries to be sorted.
 * @param start - The starting index of the range to be sorted.
 * @param end - The ending index of the range to be sorted.
 */
void Queries_AR::mergeSort(char **genome_queries, long long start, long long end)
{
    // Base case: If the subarray contains one or zero elements, it's already sorted.
    if (start >= end)
    {
        return;
    }

    // Calculate the middle index of the subarray.
    long long mid = start + (end - start) / 2;

    // Recursively sort the left and right halves of the subarray.
    mergeSort(genome_queries, start, mid);
    mergeSort(genome_queries, mid + 1, end);

    // Merge the sorted halves back into a single sorted array.
    merge(genome_queries, start, mid, end);
}

/**
 * Perform a linear search for a query sequence within genome_queries.
 *
 * This function performs a linear search for a given query sequence within the genome_queries array.
 *
 * @param sequence - The query sequence to search for.
 * @return true if the sequence is found, false if it's not found in the genome_queries array.
 */
long long Queries_AR::linearSearch(char *sequence)
{
    // Iterate through all genome queries and compare each one to the given sequence.
    for (long long i = 0; i < total_genome_queries; i++)
    {
        // If a match is found, return true.
        if (customStrcmp(sequence, genome_queries[i]) == 0)
        {
            //return the index of the match
            return i;
        }
    }

    // If no match is found after iterating through all queries, return -1.
    return -1;
}

/**
 * Perform a binary search for a query sequence within genome_queries.
 *
 * This function performs a binary search for a given query sequence within the genome_queries array.
 *
 * @param sequence - The query sequence to search for.
 * @return true if the sequence is found, false if it's not found in the genome_queries array.
 */
long long Queries_AR::binarySearch(char *sequence)
{
    long long start = 0, end = total_genome_queries - 1, mid, match;

    while (start <= end)
    {
        mid = start + (end - start) / 2;

        match = customStrcmp(genome_queries[mid], sequence);

        if (match == 0)
        {
            // If a match is found, return true.
            return mid;
        }
        else if (match > 0)
        {
            // If the sequence is alphabetically before the middle element, adjust the search range accordingly.
            end = mid - 1;
        }
        else
        {
            // If the sequence is alphabetically after the middle element, adjust the search range accordingly.
            start = mid + 1;
        }
    }

    // If no match is found after the binary search, return -1.
    return -1;
}
