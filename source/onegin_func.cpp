#include "onegin_func.h"

int max(int a, int b)
{
    return a - b > 0 ? a : b;
}

int min(int a, int b)
{
    return a - b > 0 ? b : a;
}

void swap(void * a, void * b, size_t length)
{
    assert(a);
    assert(b);

    unsigned char* p = (unsigned char*)a;
    unsigned char* q = (unsigned char*)b;
    unsigned char tmp;
    for (size_t i = 0; i != length; ++i)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

size_t file_size(FILE* file)
{
    assert(file);

    fseek(file, 0, SEEK_END);
    size_t size = (size_t)ftell(file); 
    fseek(file, 0, SEEK_SET);

    return size; 
}

void print_buf (char* buf, FILE* file, size_t num)
{
    assert(buf);
    assert(file);
    
    for(size_t i = 0; i < num; i++)
    {
        if(buf[i] == '\0')
        {
            fprintf(file, "\n");
        }
        else fprintf(file, "%c", buf[i]);
    }
}

size_t read_text(char* buf, FILE* file, size_t num)
{
    assert(buf);
    assert(file);
    
    size_t string_num = 0;
    size_t i = 0;
    while(fread(buf+i, sizeof(char), 1, file) != 0)
    {
        if(buf[i] == '\n')
        { 
            string_num++;
            buf[i] = '\0';
        }
        else if(buf[i] == '\0')
        {
            string_num++;
            break;
        }
        else if(i == num-2)
        {
            buf[i+1] = '\0';
            string_num++;
        }
        i++;
    }
    return string_num;
}

void print_text(string_elem* string_buf, size_t string_num, FILE* file)
{
    assert(string_buf);
    assert(file);

    for(size_t i = 0; i < string_num; i++)
        fprintf(file, "%s\n", (string_buf+i)->string); 
}

void fill_string_buf(string_elem* string_buf, char* buf, size_t string_num)
{
    assert(string_buf);
    assert(buf);

    size_t j = 0;
    size_t i = 0;
    size_t length = 0;

    while(i <= string_num) 
    {
        if(buf[j] == '\n' || buf[j] == '\0' || i == 0)
        { 
            if (i != 0 && i != string_num)
            {
                (string_buf+i-1)->len = j-length;
                (string_buf+i)->string = buf + j + 1; 
                length = j;
                i++;
            }
            else if(i == 0)
            {
                (string_buf+i)->string = buf + j + 1; 
                length = j;
                i++;
            }
            else if(i == string_num)
            {
                (string_buf+i-1)->len = j-length;
                i++;
            }
        }
        j++;
    }
}

void my_qsort(void *buf, size_t number, size_t size, int (*my_compare) (const void *, const void *))
{
    if(number <= 1)
        return;
    
    void* point = (char*)buf + size * (number - 1);
    bool flag = true;

    for(size_t i = 0; i < number - 1; i ++)
    {
        void* actual = (char*)buf + size * i;
        if(flag == true && my_compare(point, actual) < 0)
        {
            swap(point, actual, size);
            point = actual;
            flag = false;
        }
        else if(flag == false && my_compare(point, actual) > 0)
        {
            while(point != actual)
            {
                swap((char*)actual - size, actual, size);
                actual = (char*)actual - size;
            }
            point = (char*)point + size;
        }
    }

    size_t new_number1 = (size_t)((char*)point - (char*)buf)/size;
    size_t new_number2 = number - new_number1 - 1;
    my_qsort (buf, new_number1, size, my_compare);
    my_qsort ((char*)point + size, new_number2, size, my_compare);
}

int my_compare_right(const void* a, const void* b)
{
    assert(a);
    assert(b);
 
    const string_elem* arg1 = (const string_elem*) a;
    const string_elem* arg2 = (const string_elem*) b;
    
    size_t i = 0;
    size_t j = 0;
    int lower_arg1 = 0;
    int lower_arg2 = 0;
    while((arg1->string)[i] != '\0' && (arg2->string)[j] != '\0')
    {
        if(isalpha((arg1->string)[i]) != 0)
        {   
            if(isalpha((arg2->string)[j]) != 0)
            {
                lower_arg1 = tolower((arg1->string)[i]);
                lower_arg2 = tolower((arg2->string)[j]);
                if(lower_arg1 != lower_arg2)
                            return (lower_arg1 - lower_arg2);
                else
                {
                    i++;
                    j++;
                }
            }
            else j++;
        }
        else i++;
    }
    return (int)(arg1->len - arg2->len);
}

int my_compare_left(const void* a, const void* b)
{
    assert(a);
    assert(b);
    
    const string_elem* arg1 = (const string_elem*) a;
    const string_elem* arg2 = (const string_elem*) b;
    
    size_t i = arg1->len-1;
    size_t j = arg2->len-1;
    int lower_arg1 = 0;
    int lower_arg2 = 0;

    while( i > 0 && j > 0)
    {
        if(isalpha((arg1->string)[i]) != 0)
        {   
            if(isalpha((arg2->string)[j]) != 0)
            {
                lower_arg1 = tolower((arg1->string)[i]);
                lower_arg2 = tolower((arg2->string)[j]);
                if(lower_arg1 != lower_arg2)
                            return (lower_arg1 - lower_arg2);
                else
                {
                    i--;
                    j--;
                }
            }
            else j--;
        }
        else i--;
    }
    return (int)(arg1->len - arg2->len);
}

void test_qsort(string_elem* string_buf, size_t string_num, FILE* file)
{
    fprintf(file, "_______________________________________________DEBUG_TEST_______________________________________________\n");
    qsort(string_buf, string_num, sizeof(string_elem), my_compare_right);
    print_text(string_buf, string_num, file);
    qsort(string_buf, string_num, sizeof(string_elem), my_compare_left);
    print_text(string_buf, string_num, file);
}

void realise_sort(string_elem* string_buf, char* buf, size_t string_num, FILE* file, size_t fsize)
{
    fill_string_buf(string_buf, buf, string_num);
    my_qsort(string_buf, string_num, sizeof(string_elem), my_compare_right);
    fprintf(file, "_________________________________RIGHT_SORT_____________________________________________\n");
    print_text(string_buf, string_num, file);
    my_qsort(string_buf, string_num, sizeof(string_elem), my_compare_left); 
    fprintf(file, "______________________________________________BACK_SORT_________________________________________________\n");  
    print_text(string_buf, string_num, file);
    fprintf(file, "______________________________________ORIGINAL_TEXT______________________________________________\n");
    print_buf(buf, file, fsize);
}

void realise(char* inputfile, char* outputfile)
{
    FILE* file = fopen(inputfile, "r");
    size_t fsize = file_size(file)+1;
    char* buf = (char*)calloc(fsize, sizeof(char));
    size_t string_num = read_text(buf, file, fsize);
    fclose(file);

    file = fopen(outputfile, "w");
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
}

