#include "onegin_func.h"

int main()
{
    FILE* file = fopen("hamlet.txt", "r");
    size_t fsize = file_size(file);
    char* buf = (char*)calloc(fsize, sizeof(char));
    size_t string_num = read_text(buf, file);
    fclose(file);

    file = fopen("output.txt", "w");
    string_elem* string_buf = (string_elem*)calloc(string_num, sizeof(string_elem));
    #ifndef TEST_MODE
        realise_sort(string_buf, buf, string_num, file, fsize);
    #endif
    #ifdef TEST_MODE
        test_qsort(string_buf, string_num, file);
    #endif
    free(string_buf);
    free(buf);
    fclose(file);
    
    return 0;
}