//
// Created by 14153 on 2021/5/5.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extmem.h"
#include "q4.h"
#include "q2.h"

int
writeBlockToDisk4q4(unsigned char *finalblk, int *outputNum, Buffer *buf, int *finalmark,
                    unsigned char *data) {
    memcpy(finalblk + *finalmark * 8, data, 8);
    (*finalmark)++;
    if (*finalmark == 7) {
        *finalmark = 0;
        writeBlockToDisk(finalblk, *outputNum, buf);
        memset(finalblk, 0, buf->blkSize);
        (*outputNum)++;
    }
    return 0;
};

unsigned char *getdata(Buffer *buf, int num, int end, int *Cmark, int *mark) {
    printf("find %d, from Block %d, dataNum %d to Block %d\n", num, *Cmark, *mark, end);
    unsigned char *blk; /* A pointer to a block */
    unsigned char *reblk; /* A pointer to a block */
    reblk = malloc(8);
    int X = -1;
    for (int i = *Cmark; i < end + 1; ++i) {
        if ((blk = readBlockFromDisk(i, buf)) == NULL) {
            perror("Reading Block Failed!\n");
            return NULL;
        } else {
            printf("search Block %d\n", i);
            for (int j = *mark; j < 7; ++j) {
                X = getInt(blk + j * 8);
                if (X == num) {
                    printf("find %d!\n", num);
                    memcpy(reblk, blk + j * 8, 8);
                    if (j == 6) {
                        (*Cmark)++;
                        *mark = 0;
                    } else {
                        (*mark) = j + 1;
                    }

                    *(blk - 1) = BLOCK_AVAILABLE;
                    buf->numFreeBlk++;

                    return reblk;
                }
            }
            (*Cmark)++;
            *mark = 0;

            *(blk - 1) = BLOCK_AVAILABLE;
            buf->numFreeBlk++;
        }
    }
    return NULL;
};

int q4(Buffer *buf) {
    unsigned char *dataR = NULL;
    unsigned char *dataS = NULL;
    unsigned char *finalblk; //final block
    finalblk = buf->data + 7 * (buf->blkSize + 1);
    *finalblk = BLOCK_UNAVAILABLE;
    buf->numFreeBlk--;
    finalblk++;
    int outputNum = 500;
    int finalmark = 0;
    for (int i = 40; i < 61; ++i) {
        int Cmark[2] = {201, 217};
        int mark[2] = {0};
        free(dataR);
        dataR = getdata(buf, i, 216, &Cmark[0], &mark[0]);
        if (dataR == NULL) {
            printf("there is no %d\n", i);
            continue;
        } else {
            do {
                free(dataS);
                dataS = getdata(buf, i, 248, &Cmark[1], &mark[1]);
                if (dataS != NULL) {
                    //output
                    printf("(%d,%d) (%d,%d)\n",
                           getInt(dataR), getInt(dataR + 4),
                           getInt(dataS), getInt(dataS + 4));
                    writeBlockToDisk4q4(finalblk, &outputNum, buf, &finalmark, dataR);
                    writeBlockToDisk4q4(finalblk, &outputNum, buf, &finalmark, dataS);
                }
            } while (dataS != NULL);
        }
        printf("find %d end\n", i);
    }
    return 0;
};