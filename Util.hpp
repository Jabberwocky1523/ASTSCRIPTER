#ifndef UTIL_H
#define UTIL_H
#include "stdio.h"
#include "stdarg.h"
#include "stdlib.h"
#define OPENANDREAD(fp, buffer, len)           \
    do                                         \
    {                                          \
        if (fp == NULL)                        \
        {                                      \
            printf("file not exists!\n");      \
            return NULL;                       \
        }                                      \
        fseek(fp, 0, SEEK_END);                \
        len = ftell(fp);                       \
        fseek(fp, 0, SEEK_SET);                \
        buffer = (unsigned char *)malloc(len); \
        fread(buffer, len, 1, fp);             \
    } while (0)
class utils
{
public:
    typedef unsigned char uchar3[3];
    inline void printError(const char *format, ...)
    {
        va_list ap;
        va_start(ap, format);
        vfprintf(stderr, format, ap);
        va_end(ap);
        exit(-1);
    }
    unsigned char convHexToDec(char ch)
    {
        if ('0' <= ch && ch <= '9')
            return ch - '0';
        else if ('a' <= ch && ch <= 'f')
            return ch - 'a' + 10;
        else if ('A' <= ch && ch <= 'F')
            return ch - 'A' + 10;
        return 0;
    }
    void readColor(uchar3 *color, const char *buf)
    {
        if (buf[0] != '#')
            printError("rgb error!");
        (*color)[0] = convHexToDec(buf[1]) << 4 | convHexToDec(buf[2]);
        (*color)[1] = convHexToDec(buf[3]) << 4 | convHexToDec(buf[4]);
        (*color)[2] = convHexToDec(buf[5]) << 4 | convHexToDec(buf[6]);
    }
    bool getFile(const char *filename, unsigned char **buf, size_t &len)
    {
        *buf = loadFileToMemory(filename, &len);
        return true;
    }
    unsigned char *loadFileToMemory(const char *path, size_t *fileSize)
    {
        FILE *file = fopen(path, "rb");
        if (!file)
        {
            printf("Failed to open file: %s\n", path);
            return NULL;
        }
        fseek(file, 0, SEEK_END);
        *fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        unsigned char *buffer = (unsigned char *)malloc(*fileSize);
        if (!buffer)
        {
            printf("Failed to allocate memory for file data\n");
            fclose(file);
            return NULL;
        }
        fread(buffer, 1, *fileSize, file);
        fclose(file);
        return buffer;
    }
};
#endif