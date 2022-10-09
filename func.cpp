#include <stdio.h>
#include <cstdlib>
#include <locale.h>
#include <cctype> // для функции isalpha
#include "func.h"


void read_file_size(FILE *fp, long *lSize)
{
    fseek(fp , 0 , SEEK_END);  
    *lSize = ftell(fp);
	rewind (fp);   
}

void read_buffer(char* buffer, long lSize, FILE* fp)
{
	size_t result = fread(buffer, sizeof(char), lSize, fp);     
    printf("size of the read file:%lu\n", result);    
    if (result != lSize)
    {
        printf("Read error");
        fclose(fp);
        return;
    }
}

int read_lines(LINE* stroki, char* buffer, long lSize)
{
	int lenght = 0; 
    int line_empty = 1;	
    int numb_strok = 0;
    char* begining = &buffer[0];
	int i;
    for (i = 0; i < lSize; i++)
    {   
        if ((int)buffer[i] == 10 || i == lSize - 1)
        {
            if (!(line_empty))
                {
                stroki[numb_strok].begin = begining;
                stroki[numb_strok].len = lenght;
                numb_strok++;
                }
            lenght = 0;
            line_empty = 1;
            if (i < lSize - 1)
                begining = &buffer[i+1];
        }
        else
            {
            lenght++;
            if ((int)buffer[i] > 32 && line_empty == 1)
                line_empty = 0;
            }
    }
    return numb_strok;
}

int comparator(const void* aptr, const void* bptr)
{
    const char* a = (const char*)aptr;
    const char* b = (const char*)bptr;
    int i=0;
    int j = 0;
    while ((int)*(a+i) != '\n' && (int)*(b+j) != '\n') // the loop is executed until the end of one of the lines is reached
    {   
        if (!isalpha(*(a+i)))
        {
            i++;
            continue;
        }
        else if (!isalpha(*(b+j)))
        {
            j++;
            continue;
        }
        if ((int)*(a+i) < (int)*(b+j)) // if the letter in line a is smaller than the letter in line b then the output is 1
            return -1;
        else if ((int)*(a+i) > (int)*(b+j)) // if the letter in line a is greater than the letter in line b, then the output is -1
            return 1;
        else                                // if the letters match
        {
            if ((*(a+i+1) != '\n') && (*(b+j+1) != '\n'))   // and both don't end on the next character
                {
                    i++;
                    j++;
                    continue;  // the loop continues to run
                }
            else if (*(a+i+1) == '\n')  // if a ends, then it is shorter in length
                return -1;
            else if (*(b+j+1) == '\n')  // if b ends, then it is shorter in length
                return 1;
            else
                return 0;  // the lines match
        }
    }
    return 0;
}

void qsortik(LINE arr[], int left, int right)
{
    int i, last;
    void swap(LINE arr[], int i, int j);
    if (left >= right) /* nothing is done if */
        return; /* there are less than two elements in the array */ 
    swap(arr, left, (left + right)/2); /* dividing element */
    last = left; /* transferred to v[0] */
    for(i = left+1; i <= right; i++) /* division into parts*/
        if (comparator(arr[i].begin, arr[left].begin) == -1)
            swap(arr, ++last, i);
    swap(arr, left, last); /* we recall the dividing element */ 
    qsortik(arr, left, last-1);
    qsortik(arr, last+1, right);
}

void swap(LINE arr[], int i, int j)
{
    LINE temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void result_2_console(int numb_strok, LINE* stroki)
{
    int i, j;
    for (i=0; i < numb_strok; i++)
    {
        for (j=0; j < stroki[i].len; j++)
        {
            printf("%c", *(stroki[i].begin + j));
        }
        printf("\n");
    }
}

void result_2_file(int numb_strok, LINE* stroki)
{
	FILE* ptrFile = fopen ("output.txt" , "w");    
    int i, j;    
    for (i=0; i < numb_strok; i++)
    {    	
    	unsigned len = stroki[i].len;
    	char tmp_str[len+1];    	
        for (j=0; j < len; j++)
        {        	
            tmp_str[j] = *(stroki[i].begin + j);            
        }
        tmp_str[len]=' ';
        fwrite(tmp_str, 1 , sizeof(tmp_str), ptrFile ); 
    }
    fclose (ptrFile);
}
