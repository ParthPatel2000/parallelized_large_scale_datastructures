#include "genome_functions.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char const *argv[])
{
    // checking for the valid count of arguments
    if (argc == 4)
    {
        genomeProcessor *genomeObj = new genomeProcessor;
        // calling the read function based on the flag "read"
        if (strcmp("read", argv[1]) == 0)
           genomeObj->readHumanGenome(argv[2], argv[3]);

        // calling the compute function based on the flag "process"
        else if (strcmp("process", argv[1]) == 0)
           genomeObj->computeCharacters(argv[2], argv[3]);

        // handling errors
        else
            cout << "ERROR: command not recognized" << endl;
    }

    // handling errors
    else
    {
        cout << "Invalid inputs provided" << endl;
        cout << "use Flags: 'read' and 'process'." << endl;
        cout << "Usage:" << endl;
        cout << "\tread: ./executable read input_filename output_filename" << endl
             << endl;
        cout << "\tprocess: ./executable process input_filname outputfilename" << endl;
        cout << endl;
    }
    // cout << "ERROR: invalid arguments provided" << endl;

    return 0;
}