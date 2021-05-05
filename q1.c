//
// Created by 14153 on 2021/5/2.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extmem.h"
#include "q1.h"

int
writeBlockToDisk4q1(unsigned char *finalblk, int *outputNum, Buffer *buf, int *finalmark,
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

int q1(Buffer *buf) {
    int before_search_IO = buf->numIO;
    int after_search_IO;
    unsigned char *blk; /* A pointer to a block */
    unsigned char *finalblk; //final block
    finalblk = buf->data + 7 * (buf->blkSize + 1);
    *finalblk = BLOCK_UNAVAILABLE;
    buf->numFreeBlk--;
    finalblk++;
    int outputNum = 50;
    int finalmark = 0;
    for (int j = 17; j < 49; ++j) {
        /* Read the block from the hard disk */
        if ((blk = readBlockFromDisk(j, buf)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }

        /* Process the data in the block */
        int X = -1;
        int Y = -1;
        char str[5];
        printf("block %d:\n", j);
        for (int i = 0; i < 7; i++) //一个blk存7个元组加一个地址
        {
            for (int k = 0; k < 4; k++) {
                str[k] = *(blk + i * 8 + k);
            }
            X = atoi(str);
            for (int k = 0; k < 4; k++) {
                str[k] = *(blk + i * 8 + 4 + k);
            }
            Y = atoi(str);

            if (X == 50) {
                printf("(%d, %d) \n", X, Y);
                writeBlockToDisk4q1(finalblk, &outputNum, buf, &finalmark, blk + i * 8);
            }
        }
        *(blk - 1) = BLOCK_AVAILABLE;
        buf->numFreeBlk++;
    }
    writeBlockToDisk(finalblk, outputNum, buf);
    after_search_IO = buf->numIO;
    printf("IO's is %d\n\n", after_search_IO - before_search_IO); /* Check the number of IO's */

    return 0;
}