#include "common.h"
#include <stdlib.h>
#include <stdio.h>

char* input(void) {
    char *str = (char*)malloc(BUFSIZ);
    if (str == NULL) {
        return NULL;
    }
    if (fgets(str, BUFSIZ, stdin) == NULL) {
        free(str);
        return NULL;
    }
    str[strcspn(str, "\n")] = '\0';
    return str;
}

