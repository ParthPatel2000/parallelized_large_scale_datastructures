#include "queries_reader.h"

QUERIES_READER::QUERIES_READER(char *query_file_path, int query_length)
{
    this->query_count = 0;
    this->query_length = query_length;
    this->readQueries(query_file_path);
}

QUERIES_READER::~QUERIES_READER()
{
    for (int i = 0; i < query_count; i++)
    {
        delete[] queries[i];
    }
    delete[] queries;
}

void QUERIES_READER::readQueries(char *query_file_path)
{
    ifstream query_file_ptr(query_file_path);
    if (!query_file_ptr.is_open())
    {
        cout << "Error opening file " << query_file_path << endl;
        exit(1);
    }

    long long total_genome_queries = 0;
    char *line = new char [this->query_length + 4];
    while (query_file_ptr.getline(line, this->query_length + 4))
    {
        if (line[0] == '>')
        {
            total_genome_queries++;
        }
    }
    this->queries = new char *[total_genome_queries];

    query_file_ptr.clear();
    query_file_ptr.seekg(0, ios::beg);

    cout << "Reading queries from file " << query_file_path << endl;

    long long index = 0;
    while (query_file_ptr.getline(line, this->query_length + 4))
    {
        if (line[0] != '>')
        {
            this->queries[index] = new char[this->query_length + 1];
            for (int i = 0; i < this->query_length; i++)
            {
                this->queries[index][i] = line[i];
            }
            this->queries[index][this->query_length] = '\0';
            index++;
        }
    }
    this->query_count = index;
    cout << "Total queries read: " << index << endl;
    return;
}

char **QUERIES_READER::getQueries()
{
    return this->queries;
}

long long QUERIES_READER::getQueryCount()
{
    return this->query_count;
}

int QUERIES_READER::getQueryLength()
{
    return this->query_length;
}