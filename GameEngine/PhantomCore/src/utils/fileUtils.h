#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include <stdio.h>

char *readFile(const char *filename)
{
    FILE *file = fopen(filename, "rt");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
    {
        printf("opne file failed");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = (char *)malloc(file_size);
    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char)c;
    }
    fclose(file);
    code[n] = '\0';
    return code;
}
#endif