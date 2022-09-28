#include <stdio.h>
#include <cstdlib>
#include <locale.h>

void swap(char* v[], int i, int j);
void qsort(char* v[], int left, int right);


/* qsort: сортирует v[left]...v[right] по возрастанию */ 
void qsort(char* v[], int left, int right)
{
    int i, last;
    void swap(char* v[], int i, int j);
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
void swap(char* v[], int i, int j)
{
    char temp;
    temp = *v[i];
    *v[i] = *v[j];
    *v[j] = temp;
}

int main()
{
    char* arr[] = {"a", "h", "l", "d", "z", "a"};
    qsort(arr, 0, 5);
    for (int i = 0; i < 8; i++)
        printf("%i\n", arr[i]);
}

