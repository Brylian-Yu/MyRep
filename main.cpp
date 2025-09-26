/*
 * Copyright (c) 2025 SerComm Corporation. All Rights Reserved.
 *
 * SerComm Corporation reserves the right to make changes to this document
 * without notice. SerComm Corporation makes no warranty, representation or
 * guarantee regarding the suitability of its products for any particular
 * purpose.
 *
 * SerComm Corporation assumes no liability arising out of the application or
 * use of any product or circuit. 
 *
 * SerComm Corporation specifically disclaims any and all liability, including
 * without limitation consequential or incidental damages; neither does it convey
 * any license under its patent rights, nor the rights of others.
 */


#include "tmp/tmp.h"
#include <stdio.h>
#include <string.h>

/*
 * @brief The main entry point for the application.
 * @return 0 on successful execution.
 */
int main()
{

    char* buffer = nullptr;
    int ret = 0;

    ret = TMPAlloc(&buffer, 1024);

    if (ret != 0)
    {
        printf("TMPAlloc failed\n");
        return -1;
    }

    memset(buffer, 0, 1024);

    snprintf(buffer, 1024, "Hello World\n");

    printf("%s", buffer);

    return 0;
}
