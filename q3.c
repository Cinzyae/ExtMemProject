//
// Created by 14153 on 2021/5/4.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extmem.h"
#include "q3.h"
#include "q2.h"

int buildIndex(Buffer *buf, int start, int end) {
    printf("build index for %d to %d\n", start, end);
    unsigned char *blk; /* A pointer to a block */

    unsigned char *finalblk; //final block

    for (int i = 0; i < end - start + 1; ++i) {
        finalblk = buf->data + 7 * (buf->blkSize + 1);
        *finalblk = BLOCK_UNAVAILABLE;
        buf->numFreeBlk--;
        finalblk++;
        if ((blk = readBlockFromDisk(200 + start + i, buf)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        } else {
            printf("%d ", 200 + start + i);
        }
        memcpy(finalblk + (i % 7) * 8, blk, 8);
        if (i % 7 == 6) {
            int show[7];
            int Y;
            printf("\noutput:\n");
            for (int l = 0; l < 7; l++) //一个blk存7个元组加一个地址
            {
                show[l] = getInt(finalblk + l * 8);
                Y = getInt(finalblk + l * 8 + 4);
                printf(" (%d, %d) ", show[l], Y);
            }
            printf("\n");
            writeBlockToDisk(finalblk, 300 + (start + i) / 7, buf);
            freeBuffer(buf);
        }
    }
    int show[7];
    int Y;
    printf("\noutput:\n");
    for (int l = 0; l < 7; l++) //一个blk存7个元组加一个地址
    {
        show[l] = getInt(finalblk + l * 8);
        Y = getInt(finalblk + l * 8 + 4);
        printf(" (%d, %d) ", show[l], Y);
    }
    printf("\n");
    writeBlockToDisk(finalblk, 301 + end / 7, buf);
    freeBuffer(buf);
    return 0;
};

int searchBlock(unsigned char *blk, int num) {
    int X = -1;
    for (int j = 0; j < 7; ++j) {
        X = getInt(blk + j * 8);
        if (X > num) {
            return j;
        }
    }
    return -1;
}

int handleResult(Buffer *buf, int BlockNum) {
    unsigned char *finalblk; //final block
    finalblk = buf->data + 7 * (buf->blkSize + 1);
    *finalblk = BLOCK_UNAVAILABLE;
    buf->numFreeBlk--;
    finalblk++;
    int i = 0;
    int flag = 1;
    while (flag) {
        printf("\nin block:%d\n", BlockNum);
        unsigned char *blk; /* A pointer to a block */
        if ((blk = readBlockFromDisk(BlockNum, buf)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        } else {
            int X, Y;
            for (int j = 0; j < 7; ++j) {
                X = getInt(blk + j * 8);
                Y = getInt(blk + j * 8 + 4);
                if (X == 50) {
                    printf("(%d,%d) ", X, Y);
                    memcpy(finalblk + (i % 7) * 8, blk + j * 8, 8);
                    if ((i % 7) == 6) {
                        int show[7];
                        int Y2;
                        printf("\noutput:\n");
                        for (int l = 0; l < 7; l++) //一个blk存7个元组加一个地址
                        {
                            show[l] = getInt(finalblk + l * 8);
                            Y2 = getInt(finalblk + l * 8 + 4);
                            printf(" (%d, %d) ", show[l], Y2);
                        }
                        printf("\n");
                        writeBlockToDisk(finalblk, 401 + i / 7, buf);
                        memset(finalblk - 1, 0, buf->blkSize + 1);

                        finalblk = buf->data + 7 * (buf->blkSize + 1);
                        *finalblk = BLOCK_UNAVAILABLE;
                        buf->numFreeBlk--;
                        finalblk++;
                    }
                    i++;
                } else if (X > 50) {
                    flag = 0;

                    int show[7];
                    int Y2;
                    printf("\noutput:\n");
                    for (int l = 0; l < 7; l++) //一个blk存7个元组加一个地址
                    {
                        show[l] = getInt(finalblk + l * 8);
                        Y2 = getInt(finalblk + l * 8 + 4);
                        printf(" (%d, %d) ", show[l], Y2);
                    }
                    printf("\n");
                    writeBlockToDisk(finalblk, 401 + i / 7, buf);
                    freeBuffer(buf);

                    finalblk = buf->data + 7 * (buf->blkSize + 1);
                    *finalblk = BLOCK_UNAVAILABLE;
                    buf->numFreeBlk--;
                    finalblk++;
                }
            }
        }
        BlockNum++;
    }
    return 0;
};

int searchIndex(Buffer *buf, int start, int end) {
    printf("\nnow search by index\n");
    unsigned char *blk; /* A pointer to a block */
    int Blocknum = -1;
    int i = -1;
    for (i = 301 + start / 7; i < 300 + start + (end - start + 1) / 7; ++i) {
        if ((blk = readBlockFromDisk(i, buf)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        } else {
            printf("%d ", i);
        }
        Blocknum = searchBlock(blk, 50);
        if (Blocknum > -1) {
            break;
        }
    }
    if (Blocknum < 0) {
        freeBuffer(buf);
        return -1;
    } else {
        //blk i,Block Number Blocknum.
        handleResult(buf, 7 * (i - 301) + Blocknum + 200);
        return 0;
    }
}

int q3(Buffer *buf) {
    int befor_build_IO = buf->numIO;
    int after_build_IO;
    int after_search_IO;
    buildIndex(buf, 17, 48);
    after_build_IO = buf->numIO;
    searchIndex(buf, 17, 48);
    after_search_IO = buf->numIO;
    printf("IO's is %d\n", after_search_IO - after_build_IO); /* Check the number of IO's */
    return 0;
};