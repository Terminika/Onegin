#ifndef FUNC_H
#define FUNC_H


typedef struct {
    char *begin;
    unsigned len;
} LINE;

void read_file_size(FILE *fp, long *lSize);
void read_buffer(char* buffer, long lSize, FILE* fp);
int read_lines(LINE* stroki, char* buffer, long lSize);

void swap(LINE arr[], int i, int j);
void qsortik(LINE arr[], int left, int right);
int comparator(const void* aptr, const void* bptr);
void result_2_console(int numb_strok, LINE* stroki);
void result_2_file(int numb_strok, LINE* stroki);


#endif
