#include <stdio.h>
#include <cstdlib>
#include <locale.h>

typedef struct {
    char *begin;
    unsigned len;
} LINE;

int comparator(const void* aptr, const void* bptr);
void qsort(LINE arr[], int left, int right);
void swap(LINE arr[], int i, int j);


/// @brief Функция принимает указатели на начало двух строк, вычисление, какая строка больше другой 
/// (в лексикографическом смысле и по длине при совпадении первых i символов)
/// @return 1 если первая строка больше второй, -1 если первая меньше второй, 0 если сторки совпадают
int comparator(const void* aptr, const void* bptr)
{
    const char* a = (const char*)aptr;
    const char* b = (const char*)bptr;
    int i=0;
    while ((int)*(a+i) != '\n' && (int)*(b+i) != '\n') // цикл выполняется, пока не достигается конец одной из строк
    {   
        if ((int)*(a+i) < (int)*(b+i)) // если буква с строке а меньше буквы в строке b то вывод 1
            return -1;
        else if ((int)*(a+i) > (int)*(b+i)) // если буква с строке а больше буквы в строке b то вывод -1
            return 1;
        else                                // если буквы совпадают
        {
            if ((*(a+i+1) != '\n') && (*(b+i+1) != '\n'))   // и обе не заканчиваются на следующем символе
                {
                    i++;
                    continue;  // цикл продолжает работать
                }
            else if (*(a+i+1) == '\n')  // если a заканчивается, то она короче по длине 
                return -1;
            else if (*(b+i+1) == '\n')  // если b заканчивается, то она короче по длине
                return 1;
            else
                return 0;  // строки совпадают
        }
    }
    return 0;
}

void qsortik(LINE arr[], int left, int right)
{
    int i, last;
    void swap(LINE arr[], int i, int j);
    if (left >= right) /* ничего не делается, если */
        return; /* в массиве менее двух элементов */ 
    swap(arr, left, (left + right)/2); /* делящий элемент */
    last = left; /* переносится в v[0] */
    for(i = left+1; i <= right; i++) /* деление на части */
        if (comparator(arr[i].begin, arr[left].begin) == -1)
            swap(arr, ++last, i);
    swap(arr, left, last); /* перезапоминаем делящий элемент */ 
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

int main (){
    setlocale(LC_ALL, "RUS");
    LINE *stroki = (LINE*) calloc(1, sizeof(LINE*));

    FILE *fp;
    char file_name[] = "onegin.txt";
    if ((fp = fopen(file_name, "rb")) == NULL)
    {
        printf("Не удалось открыть файл\n\n\n");
        return -1;
    }
    fseek(fp , 0 , SEEK_END);  // позицию в конец файла
    long lSize = ftell(fp);     
    rewind (fp);   // указатель в начало файла

    char * buffer = (char*) calloc(lSize, sizeof(char)); // выделить память для хранения содержимого файла
    if (buffer == NULL)
    {
        printf("Ошибка памяти");
        fclose(fp);
        return -1;
    }

    // printf("Выделенный размер для буфера:%d \n", _msize());
    size_t result = fread(buffer, sizeof(char), lSize, fp); 
    printf("Размер считанного файла:%lu\n", result);
    if (result != lSize)
    {
        printf("Ошибка чтения");
        fclose(fp);
        return -1;
    }
    
    char* begining = &buffer[0];
    //printf("%s \n\n", buffer);

    int numb_strok = 0;
    int lenght = 0; 
    int line_empty = 1;

    for (int i = 0; i < lSize; i++)
    {   
        //printf("%i    %c %i\n", i, buffer[i], (int)buffer[i]);

        if ((int)buffer[i] == 10 || i == lSize - 1)
        {
            //printf("последний символ строки %i\n", (int)buffer[i]);  
            if (!(line_empty))
                {
                stroki[numb_strok].begin = begining;
                stroki[numb_strok].len = lenght;
                //printf("%u\n", stroki[numb_strok].len);
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
    printf("%c %c\n", *stroki[0].begin, *stroki[1].begin);
    printf("%i\n", comparator(stroki[0].begin, stroki[1].begin));
    qsortik(stroki, 0, numb_strok-1);
    for (int i=0; i < numb_strok; i++)
    {
        for (int j=0; j < stroki[i].len; j++)
        {
            printf("%c", *(stroki[i].begin + j));
        }
        printf("\n");
    }
    fclose(fp);
    free(buffer);
    return 0;
}

