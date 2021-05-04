//
// Created by 14153 on 2021/5/2.
//

#include <stdlib.h>
#include <stdio.h>
#include "extmem.h"
#include "q1.h"

int q1(Buffer *buf) {
    int before_search_IO = buf->numIO;
    int after_search_IO;
    unsigned char *blk; /* A pointer to a block */
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
            }
        }
        if (j % 8 == 0) {
            freeBuffer(buf);
        }
    }
    after_search_IO = buf->numIO;
    printf("IO's is %d\n\n", after_search_IO -before_search_IO ); /* Check the number of IO's */

    return 0;
}