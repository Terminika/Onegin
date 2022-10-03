#include <stdio.h>
#include <cstdlib>
#include <locale.h>
#include <cctype> // для функции isalpha


typedef enum {
    ZERO = 0,   //0
    ONE = 1,    //1
    TWO = 2,    //2
    INF = 3,    //3
    WRONG = 4   //   more comm
} compare;

typedef struct {
    char *begin;
    unsigned len;
} LINE;


void swap(char v[], int i, int j);
void qsort(char v[], int left, int right);
int comparator(const void* aptr, const void* bptr);


/* qsort: сортирует v[left]...v[right] по возрастанию */ 
void qsort(char v[], int left, int right)
{
    int i, last;
    void swap(char v[], int i, int j);
    if (left >= right) /* ничего не делается, если */
        return; /* в массиве менее двух элементов */ 
    swap(v, left, (left + right)/2); /* делящий элемент */
    last = left; /* переносится в v[0] */
    for(i = left+1; i <= right; i++) /* деление на части */
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last); /* перезапоминаем делящий элемент */ 
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: поменять местами v[i] и v[j] */
void swap(char v[], int i, int j)
{
    char temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int main()
{
    /*char arr[] = {'af', 'bcd', 'bcf', 'defg', 'def', 'ab'};
    qsort(arr, 0, 5);
    for (int i = 0; i < 8; i++)
        printf("%c\n", arr[i]);*/
    
    const char* s1 = "a";
    const char* s2 = "b";
    comparator(&s1, &s2);
    return 0;
}
