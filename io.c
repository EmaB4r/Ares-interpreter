#include "io.h"
#include <stdlib.h>

char * get_file_text_from_path(char* path){
    FILE *f=fopen(path, "r");
    char * buffer = 0;
    long length;
    if (f){
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
        {
        fread (buffer, 1, length, f);
        }
    fclose (f);
    }
    return buffer;
}