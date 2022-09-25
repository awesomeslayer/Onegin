#ifndef once

#define once
#define true 1
#define false 0
//#define TEST_MODE 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

typedef struct String_elem{
    char* string;
    size_t len;
} string_elem;

int max(int a, int b);

int min(int a, int b);

void swap(void * a, void * b, size_t length);

size_t file_size(FILE* file);

void print_buf (char* buf, FILE* file, size_t num);

size_t read_text(char* buf, FILE* file);

void print_text(string_elem* string_buf, size_t string_num, FILE* file);

void fill_string_buf(string_elem* string_buf, char* buf, size_t string_num);

void my_qsort(void *buf, size_t number, size_t size, int (*my_compare) (const void *, const void *));

int my_compare_right(const void* a, const void* b);

int my_compare_left(const void* a, const void* b);

void realise_sort(string_elem* string_buf, char* buf, size_t string_num, FILE* file, size_t fsize);

void test_qsort(string_elem* string_buf, size_t string_num, FILE* file);

void realise(char* inputfile, char* outputfile);

#endif