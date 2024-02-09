#ifndef QUERIES_READER_H_
#define QUERIES_READER_H_
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

class QUERIES_READER
{
    private:
        char** queries;
        long long query_count;
        int query_length;
    public:
        QUERIES_READER(char* query_file_path, int query_length);
        ~QUERIES_READER();
        void readQueries(char* query_file_path);
        char** getQueries();
        long long getQueryCount();
        int getQueryLength();
};

#endif