#include <stdio.h>
#include <cstdlib>
#include <locale.h>

int comparator(const void* aptr, const void* bptr);

typedef struct {
    char *begin;
    unsigned len;
} LINE;

int comparator(const void* aptr, const void* bptr)
{
    const char* a = (const char*)aptr;
    const char* b = (const char*)bptr;
    int i=0;
    int a_eq_b = 1;
    while (*(a+i) != '\0')
    {
        if ((int)*a < (int)*b)
        {
            return -1;
        }
        else if ((int)*a > (int)*b)
            return 1;
        else if ((int)*a == (int)*b)
            continue;
    }
    //int i=(int)a;
    //while (*((int)a + i*sizeof()) != '\0')

    /*if ((not isalpha(*a)) || (not isalpha(*b)))
        return 0;*/
    printf("%i\n", a[5]);
    printf("%i\n", (int)*b);   
    return 0;

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
    fseek(fp , 0 , SEEK_END);  // устанавливаем позицию в конец файла
    long lSize = ftell(fp);     
    rewind (fp);   // устанавливаем указатель в начало файла

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
    fclose(fp);
    free(buffer);
    return 0;
}

