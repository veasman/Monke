#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>

char* get_file_contents(const char* filepath) {
    char* buf = 0;
    long len;

    FILE* f = fopen(filepath, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        len = ftell(f);
        fseek(f, 0, SEEK_SET);

        buf = calloc(len, len);

        if (buf)
            fread(buf, 1, len, f);

        fclose(f);

        return buf;
    }

    printf("Error reading file %s\n", filepath);
    exit(2);
}

