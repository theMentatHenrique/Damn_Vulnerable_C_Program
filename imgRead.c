#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Image {
    char header[4];
    unsigned int width;
    unsigned int height;
    char data[10];
};

int ProcessImage(char* filename) {
    FILE *fp;
    struct Image img;

    fp = fopen("input2.img", "r");
    if (fp == NULL) {
        printf("\nCan't open file or file doesn't exist.\r\n");
        exit(0);
    }

    while (fread(&img, sizeof(img), 1, fp) > 0) {
        printf("\n\tHeader\twidth\theight\tdata\t\r\n");
        printf("\n\t%s\t%d\t%d\t%s\r\n", img.header, img.width, img.height, img.data);

        unsigned int size1 = img.width + img.height;
        if (size1 > 0xFFFF) {
            printf("Error! Large value of size1 detected!\n");
        }

        char* buff1 = (char*)malloc(size1);
        if (buff1 == NULL) {
            printf("Error! Buffer allocation failed!\n");
        }
        if (sizeof(img.data) > size1) {
            printf("Error! Not enough memory to copy data\n");
    
        }

        memcpy(buff1, img.data, sizeof(img.data));
        free(buff1);
        buff1 = NULL;

        if (size1 / 2 == 0) {
            free(buff1);
        } else {
            if (size1 / 3 == 0) {
                if (buff1 == NULL) {
                    printf("Error! Buffer is already freed!\n");
                } else {
                    buff1[0] = 'a';
                }
            }
        }

        unsigned int size2 = img.width - img.height + 100;
        char* buff2 = (char*)malloc(size2);
        if (buff2 == NULL) {
            printf("Error! Memory allocation failed!\n");
        }
        if (sizeof(img.data) > size2) {
            printf("Error! Not enough memory to copy data!\n");
        }

        memcpy(buff2, img.data, sizeof(img.data));

        if (img.height == 0) {
            printf("Error! Image Height is zero!\n");
        }

        int size3 = img.width / img.height;
        char buff3[10];
        char* buff4 = (char*)malloc(size3);
        if (buff4 == NULL) {
            printf("Error! Memory allocation failed.\n");
        }
        if (sizeof(img.data) > size3) {
            printf("Error! Not enough memory to copy data!\n");
        }
        memcpy(buff4, img.data, sizeof(img.data));

        if (size3 > 9) {
            printf("Error! Memory access beyond allowed size detected!\n");
        } else {
            char OOBR = buff3[size3];
            buff3[size3] = 'c';
        }

        int size4 = size3 + 100;
        if (size4 > size3) {
            printf("Error! Memory access beyond allowed size detected!\n");
            return 0;
        } else {
            char OOBR_heap = buff4[size4];
            buff4[size4] = 'c';
        }

        if (size3 > 10) {
            free(buff4);
            buff4 = 0;
        } else {
            free(buff4);
        }

        free(buff2);
    }
    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "no input file\n");
        exit(-1);
    }
    ProcessImage(argv[1]);
    return 0;
}
