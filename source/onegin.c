#include "onegin_func.h"

int main()
{
    FILE* file = fopen("hamlet.txt", "r");
    long fsize = file_size(file);
    char buf[fsize];
    int string_num = read_text(buf, file);
    fclose(file);

    file = fopen("output.txt", "w");
    string_elem* string_buf = (string_elem*)calloc(string_num, sizeof(string_elem));
    realise_sort(string_buf, buf, string_num, file, fsize);
    #ifdef DEBUG_MODE
        test_qsort(string_buf, string_num, file);
    #endif
    fclose(file);
    
    return 0;
}