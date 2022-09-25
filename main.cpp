#include <stdio.h>
#include <cstdlib>

typedef struct {
    char *begin;
    unsigned len;
} line;

int main (){
    FILE *fp;
    char file_name[] = "onegin.txt";
    fp = fopen(file_name, "r");
    if ((fp = fopen(file_name, "r")) == NULL)
    {
        printf("Не удалось открыть файл\n\n\n");
        return -1;
    }
    fseek(fp , 0 , SEEK_END);  // устанавливаем позицию в конец файла
    long lSize = ftell(fp);     
    rewind (fp);   // устанавливаем указатель в начало файла

    char * buffer = (char*) malloc(sizeof(char) * lSize); // выделить память для хранения содержимого файла
    if (buffer == NULL)
    {
        printf("Ошибка памяти");
        return -1;
    }

    size_t result = fread(buffer, 1, lSize, fp); 
    if (result != lSize)
    {
        printf("Ошибка чтения");
        return -1;
    }
    
    line arr[] = {};
    // while

    fclose(fp);
    free(buffer);
    return 0;
}

