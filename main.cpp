#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "func.h"

int main (){
    setlocale(LC_ALL, "RUS");
    LINE *stroki = (LINE*) calloc(1, sizeof(LINE*));
    FILE *fp;
    long lSize;
    char file_name[] = "onegin.txt";
    if ((fp = fopen(file_name, "rb")) == NULL)
    {
        printf("File open error\n\n\n");
        return 0;
    }
    read_file_size(fp, &lSize);   

	        
    char * buffer = (char*) calloc(lSize, sizeof(char)); 
    if (buffer == NULL)
    {
        printf("Memory error");
        fclose(fp);
        return -1;
    }	
    printf("Allocated memory for the buffer:%lu \n", sizeof(buffer));
    
    read_buffer(buffer, lSize, fp);    
    int numb_strok = read_lines(stroki, buffer, lSize);      
    qsortik(stroki, 0, numb_strok-1);
    
    result_2_console(numb_strok, stroki);
    result_2_file(numb_strok, stroki);
    
    fclose(fp);
    free(buffer);
    return 0;
}