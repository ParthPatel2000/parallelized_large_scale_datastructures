#include "queries_nw.h"

QUERIES_NW::QUERIES_NW()
{
    this->queries = NULL;
    this->query_length = 0;
    this->query_count = 0;
    this->genome_string = NULL;
    this->genome_length = 0;
}

QUERIES_NW::QUERIES_NW(int match, int mismatch, int gap) : QUERIES_NW()
{
    this->match = match;
    this->mismatch = mismatch;
    this->gap = gap;
}

QUERIES_NW::~QUERIES_NW()
{
    for (int i = 0; i < query_count; i++)
    {
        delete[] queries[i];
    }
    delete[] queries;
}

void QUERIES_NW::setQueries(char **queries, int query_length, int query_count)
{
    this->queries = queries;
    this->query_length = query_length;
    this->query_count = query_count;
}

void QUERIES_NW::setGenome(char *genome, long long genome_length)
{
    this->genome_string = genome;
    this->genome_length = genome_length;
}

int max_of_three(int a, int b, int c)
{
    return max(max(a, b), c);
}

int QUERIES_NW::needleman_wunsch(char *query, char *target, int query_length, int target_length)
{
    // cout << "in nw" << endl;
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

long long QUERIES_NW::search(char *fragment, int mismatch_threshold)
{

    int max_score = 0;
    long long best_match_index = 0;
    int num_threads = omp_get_num_procs();
    int *max_scores = new int[num_threads];
    long long *best_score_indexes = new long long[num_threads];
    int run_flag = 1;

    // initializing the max scores and best score ids
    for (int i = 0; i < num_threads; i++)
    {
        max_scores[i] = 0;
        best_score_indexes[i] = 0;
    }

#pragma omp parallel for num_threads(num_threads)
    for (long long query_index = 0; query_index < query_count; query_index++)
    {
        int thread_id = omp_get_thread_num();

        int score = needleman_wunsch(queries[query_index], fragment, query_length, query_length);
        if (score > max_scores[thread_id])
        {
            max_scores[thread_id] = score;
            best_score_indexes[thread_id] = query_index;
        }
    }

    // comparing all the scores from each thread
    for (int i = 0; i < num_threads; i++)
    {
        if (max_score < max_scores[i])
        {
            max_score = max_scores[i];
            best_match_index = best_score_indexes[i];
        }
    }

    // cout << "Total Hits: " << total_hits << endl;

    delete[] max_scores;
    delete[] best_score_indexes;

    if (max_score < ((query_length - mismatch_threshold) * match) + (mismatch_threshold * mismatch))
    {
        return -1;
    }

    return best_match_index;
}

long long QUERIES_NW::getTotalHits()
{
    return total_hits;
}