#include "onegin_func.h"

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        char* inputfile = argv[1];
        char* outputfile = argv[2];
        realise(inputfile, outputfile);
        return 0;
    }
    else
    { 
        printf("Invalid input/output files, try again\n"); 
        return -1;
    }
}