#include "tmp/tmp.h"

#include <stdlib.h>

int TMPAlloc(char** buf, int size)
{
    char* tmpbuf = nullptr;
    tmpbuf = malloc(sizeof(char)*size); 
    
    if (tmpbuf == nullptr)
    {
        return -1;
    }

    *buf = tmpbuf;
    return 0;
}