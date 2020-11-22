#include <stdio.h>
#include <string.h>
#include <locale.h>

const char* fname = "test3.txt";
const char* result="result.txt";
const int BUF_SIZE = 256;
int strsize(char* str);
void printFile(const char* fname);

int main()
{
    setlocale(LC_ALL, "rus");
    FILE* in;
    FILE* out;
    if ((in = fopen(fname, "r")) == NULL) {
        printf("Ошибка открытия файла \"%s\"",fname);
        return 1;
    }
    out = fopen(result, "w");
    char buf[BUF_SIZE];
    int len_max = 0;
    int len;
    long int cur;
    while (fgets(buf,BUF_SIZE,in)!=NULL) {     
        len = strsize(buf);
        if (len > len_max) {
            len_max = len;
        }
    }
    if (len_max == 0) {
        printf("Исходный файл \"%s\" пуст\n",fname);
        return 0;
    }
    fseek(in, 0, SEEK_SET);
    char str[BUF_SIZE/2];
    int new_len = len_max / 2;
    int str_len = 0;
    char new_str[BUF_SIZE / 2];
    char c;
    int len_now = 0;
    while ((fgets(str,BUF_SIZE/2,in))!=NULL) {
        char* ptr;
        int count;
        if ((ptr = strrchr(str, '\n')) != NULL) {
            *ptr = ' ';
        }
        for (int i = 0; str[i]; i++) {
            c = str[i];
            if (c != '\t') {
                count = 1;
            }
            else {
                c = ' ';
                count = 3;
            }
            for (int j = 0; j < count; j++) {
                if (len_now < new_len) {
                    fputc(c, out);
                    len_now++;
                }
                else {

                    fputc('\n', out);
                    fputc(c, out);
                    len_now = 1;

                }
            }
            
        }
    }
    fclose(in);
    fclose(out);
    printFile(result);
    return 0;
}

int strsize(char* str) {
    int len = 0;
    char* ptr;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\t') {
            len += 3;
        }
        else
            len++;
    }
    if ((ptr = strrchr(str, '\n')) != NULL) {
        len--;
    }
    return len;
}

void printFile(const char* file) {
    FILE* in;
    if ((in = fopen(file, "r")) == NULL) {
        printf("Ошибка открытия файла \"%s\"", file);
        return;
    }
    char buf[BUFSIZ];
    printf("Содержимое файла \"%s\":\n", file);
    for (int i = 0; i < 20; i++) {
        printf("~");
    }
    printf("\n");
    while (fgets(buf, BUF_SIZE, in) != NULL) {
        char* ptr;
        if ((ptr=strrchr(buf, '\n')) != NULL) {
            *ptr = '\0';
        }
        puts(buf);
    }
    for (int i = 0; i < 20; i++) {
        printf("~");
    }
    printf("\n");
}