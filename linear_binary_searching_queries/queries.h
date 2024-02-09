#ifndef QUERIES_H
#define QUERIES_H

#define READ_LENGTH 33

using namespace std;

class Queries_AR
{
private:
    char *genome_data;

    char **genome_queries;

    long long genome_size;

    long long total_genome_queries;

    int genome_query_length;

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
    void merge(char **genome_queries, long long start, long long mid, long long end);

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
    void mergeSort(char **genome_queries, long long start, long long end);

    /**
     * Perform a linear search for a query sequence within genome_queries.
     *
     * This function performs a linear search for a given query sequence within the genome_queries array.
     *
     * @param sequence - The query sequence to search for.
     * @return true if the sequence is found, false if it's not found in the genome_queries array.
     */
    // bool linearSearch(char *sequence);
    long long linearSearch(char *sequence);


    /**
     * Perform a binary search for a query sequence within genome_queries.
     *
     * This function performs a binary search for a given query sequence within the genome_queries array.
     *
     * @param sequence - The query sequence to search for.
     * @return true if the sequence is found, false if it's not found in the genome_queries array.
     */
    // bool binarySearch(char *sequence);
    long long binarySearch(char *sequence);


public:
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
    Queries_AR();

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
    Queries_AR(ifstream &fileptr, char *genome, long long size);

    /**
     * Read genome queries from an input file.
     *
     * This function reads genome queries from the provided input file stream and stores them in the genome_queries array.
     *
     * @param fileptr - An input file stream from which genome queries are read.
     * @return true if the queries are successfully read, false if there was an issue with the file or queries.
     */
    bool readQueries(ifstream &fileptr);

    /**
     * Search for query sequences within the genome data using linear or binary search.
     *
     * This function performs a search for query sequences within the genome data using either
     * linear or binary search based on the `do_linear_search` parameter. It then prints the results.
     *
     * @param do_linear_search - A boolean indicating whether to use linear search (true) or binary search (false).
     * @param subject_fragments_count - The number of subject fragments to search within.
     */
    void searchQueries(bool do_linear_search, long long subject_fragments_count);

    /**
     * Sort the genome queries using the merge sort algorithm.
     *
     * This function provides a high-level interface for sorting the genome_queries array using
     * the merge sort algorithm. It calls the mergeSort function to perform the actual sorting.
     */
    void sortQueries();

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
    int customStrcmp(const char *str1, const char *str2);

    /**
     * Destructor for the Queries_AR class.
     *
     * This destructor is responsible for cleaning up dynamically allocated memory used for genome_queries.
     * It deallocates memory for each individual genome query and the array of pointers to genome queries.
     */
    ~Queries_AR();
};

#endif