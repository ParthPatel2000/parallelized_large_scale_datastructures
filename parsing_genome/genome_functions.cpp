#include "genome_functions.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;

/**
 * @brief Calculate the size of the genome characters by skipping genome headers in an input file.
 *
 * This function iterates through the entire content of the input file, excluding lines that start with '>',
 * and calculates the size of the genome characters.
 *
 * @param inputFilePointer Input file stream representing the genome data file.
 * @return The size of the genome characters (excluding headers) as a long long int.
 */
long long int genomeProcessor::calculateGenomeSize(ifstream &inputFilePointer)
{
    char line[MAX_LINE_LENGTH]; 

    long long int totalGenomeCount = 0;

    while (inputFilePointer.getline(line, MAX_LINE_LENGTH))
    {
        if (line[0] != '>')
        {
            totalGenomeCount += strlen(line);
        }
    }

    return totalGenomeCount;
}


/**
 * @brief Read a human genome file, perform various calculations, and write the results to an output file.
 *
 * This function reads a human genome file, processes the data to calculate statistics about the genome scaffolds,
 * and then writes these statistics to an output file.
 *
 * @param inputFilePath The path to the input genome file.
 * @param outputFilePath The path to the output file where the results will be written.
 */

void genomeProcessor::readHumanGenome(const char* inputFilePath, const char* outputFilePath)
{
    ifstream inputFilePointer;
    ofstream outputFilePointer;

    char line[MAX_LINE_LENGTH];

    inputFilePointer.open(inputFilePath, ios::binary);

    long long int size = genomeProcessor::calculateGenomeSize(inputFilePointer);
    inputFilePointer.clear();
    inputFilePointer.seekg(0, ios::beg);

    genomeString = new char[size + 1];
    genomeSize = size;
    outputFilePointer.open(outputFilePath);

    if (inputFilePointer.is_open())
    {
        long long int scaffoldsCount = 0,
                      scaffoldLength = -1,
                      index = 0,
                      minScaffoldLength = __LONG_LONG_MAX__,
                      maxScaffoldLength = -1;

        char minScaffoldName[MAX_LINE_LENGTH] = "";
        char maxScaffoldName[MAX_LINE_LENGTH] = "";
        char header[MAX_LINE_LENGTH] = "";

        while (inputFilePointer.getline(header, MAX_LINE_LENGTH))
        {
            if (header[0] == '>')
            {
                scaffoldsCount++;

                if (minScaffoldLength > scaffoldLength && scaffoldLength != -1)
                {
                    minScaffoldLength = scaffoldLength;
                    strcpy(minScaffoldName, header);
                }

                if (maxScaffoldLength < scaffoldLength)
                {
                    maxScaffoldLength = scaffoldLength;
                    strcpy(maxScaffoldName, header);
                }

                scaffoldLength = 0;
            }
            else
            {
                while (inputFilePointer.getline(line, MAX_LINE_LENGTH) && line[0] != '>')
                {
                    for (int i = 0; line[i] != '\0'; i++)
                    {
                        genomeString[index++] = line[i];
                        scaffoldLength++;
                    }
                }
            }
        }

        if (minScaffoldLength > scaffoldLength)
        {
            minScaffoldLength = scaffoldLength;
            strcpy(minScaffoldName, header);
        }

        if (maxScaffoldLength < scaffoldLength)
        {
            maxScaffoldLength = scaffoldLength;
            strcpy(maxScaffoldName, header);
        }

        if (outputFilePointer.is_open())
        {
            outputFilePointer << endl
                              << "***********************************************" << endl;
            outputFilePointer << endl
                              << "*            Reading Genome Data              *" << endl;
            outputFilePointer << endl
                              << "***********************************************" << endl;
            outputFilePointer << endl
                              << "Total Scaffolds : " << scaffoldsCount << endl;
            outputFilePointer << endl
                              << "Largest Scaffold : " << maxScaffoldName << endl
                              << "Length : " << maxScaffoldLength << endl;
            outputFilePointer << endl
                              << "Shortest Scaffold : " << minScaffoldName << endl
                              << "Length : " << minScaffoldLength << endl;
            outputFilePointer << endl
                              << "Average Scaffold : " << fixed << (genomeSize / (double)scaffoldsCount) << endl;
            outputFilePointer << endl
                              << "Total Genome Length : " << genomeSize << endl;
        }

        inputFilePointer.close();
        outputFilePointer.close();
    }
}

void genomeProcessor::computeCharacters(const char* inputFilePath, const char* outputFilePath)
{
    time_t startTime, endTime;
    time(&startTime);

    ifstream inputFilePointer(inputFilePath);
    ofstream outputFilePointer(outputFilePath);

    char line[MAX_LINE_LENGTH];

    long long int aCount = 0,
                  cCount = 0,
                  gCount = 0,
                  tCount = 0,
                  othersCount = 0,
                  genomeSize = 0;

    if (inputFilePointer.is_open())
    {
        while (inputFilePointer.getline(line, MAX_LINE_LENGTH))
        {
            if (line[0] != '>') // Skip genome headers
            {
                for (long long int i = 0; line[i] != '\0'; i++)
                {
                    char currentChar = line[i];
                    switch (currentChar)
                    {
                    case 'A':
                        aCount++;
                        break;
                    case 'C':
                        cCount++;
                        break;
                    case 'G':
                        gCount++;
                        break;
                    case 'T':
                        tCount++;
                        break;
                    default:
                        othersCount++;
                        break;
                    }
                }

                genomeSize += strlen(line); // Calculate genome size
            }
        }
    }

    time(&endTime);

    cout << "aCount:" << aCount << endl;
    cout << "cCount:" << cCount << endl;
    cout << "gCount:" << gCount << endl;
    cout << "tCount:" << tCount << endl;
    cout << "othersCount:" << othersCount << endl;
    cout << "Runtime in seconds:" << (endTime - startTime) << endl;

    if (outputFilePointer.is_open())
    {
        outputFilePointer << endl
                          << "***********************************************" << endl;
        outputFilePointer << endl
                          << "*            Genome Computation               *" << endl;
        outputFilePointer << endl
                          << "***********************************************" << endl;
        outputFilePointer << endl
                          << "Total characters in the genome : " << genomeSize << endl;
        outputFilePointer << endl
                          << "Runtime in seconds : " << (endTime - startTime) << endl;
        outputFilePointer << endl
                          << "count of GC : " << (gCount + cCount) << endl;
        outputFilePointer << endl
                          << "percent of GC : " << fixed << ((gCount + cCount) / (double)genomeSize) * 100 << "%" << endl;
        outputFilePointer << endl
                          << "count of A : " << aCount << endl;
        outputFilePointer << endl
                          << "percent of A : " << fixed << (aCount / (double)genomeSize) * 100 << "%" << endl;
        outputFilePointer << endl
                          << "count of C : " << cCount << endl;
        outputFilePointer << endl
                          << "percent of C : " << fixed << (cCount / (double)genomeSize) * 100 << "%" << endl;
        outputFilePointer << endl
                          << "count of G : " << gCount << endl;
        outputFilePointer << endl
                          << "percent of G : " << fixed << (gCount / (double)genomeSize) * 100 << "%" << endl;
        outputFilePointer << endl
                          << "count of T : " << tCount << endl;
        outputFilePointer << endl
                          << "percent of T : " << fixed << (tCount / (double)genomeSize) * 100 << "%" << endl;
        outputFilePointer << endl
                          << "Other characters : " << othersCount << endl;
        outputFilePointer << endl
                          << "percent : " << fixed << (othersCount / (double)genomeSize) * 100 << "%" << endl;
    }

    inputFilePointer.close();
    outputFilePointer.close();

    cout << "Execution Complete" << endl;
}
