#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include "queries.h"
#include "genome_functions.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cerr << "Usage: " << argv[0] << " <genome_file> <queries_file> <sorted/unsorted> < (integer)fragment_count/ ALL>" << endl;
        return 1;
    }

    const char *genomeInputFilePath = argv[1];
    const char *queriesInputFilePath = argv[2];
    const char *command = argv[3];
    const char *fragmentArg = argv[4];

    ifstream genomeDataFile(genomeInputFilePath);
    ifstream queryDataFile(queriesInputFilePath);

    clock_t startTime, endTime;

    genomeProcessor genomeProcessingInstance;
    genomeProcessingInstance.readGenomeData(genomeDataFile);

    char *genomeData = genomeProcessingInstance.getGenomeData();
    long long size = genomeProcessingInstance.getSize();

    Queries_AR queriesInstance(queryDataFile, genomeData, size);
    queriesInstance.readQueries(queryDataFile);

    long long fragmentCount = 0;

    if (queriesInstance.customStrcmp(fragmentArg, "ALL") == 0)
    {
        // The number of total substrings of length 32.
        fragmentCount = size - 32 + 1;
    }
    else
    {
        fragmentCount = stoll(fragmentArg);
    }

    cout << "fragment_count: " << fragmentCount << endl;

    if (queriesInstance.customStrcmp(command, "unsorted") == 0)
    {
        startTime = clock();
        queriesInstance.searchQueries(true, fragmentCount);
        endTime = clock();
    }
    else
    {
        cout << command << endl;
        queriesInstance.sortQueries();
        startTime = clock();
        queriesInstance.searchQueries(false, fragmentCount);
        endTime = clock();
    }

    cout << "Runtime: " << fixed << setprecision(5) << (double(endTime - startTime)) / CLOCKS_PER_SEC <<" secs."<< endl;

    queryDataFile.close();

    return 0;
}
