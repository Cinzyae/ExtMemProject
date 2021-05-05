//
// Created by 14153 on 2021/5/5.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extmem.h"
#include "q5.h"
#include "q4.h"
#include "q2.h"

int q5(Buffer *buf) {
    int count = 0;
    unsigned char *dataR = NULL;
    unsigned char *dataS = NULL;
    unsigned char *finalblk; //final block
    finalblk = buf->data + 7 * (buf->blkSize + 1);
    *finalblk = BLOCK_UNAVAILABLE;
    buf->numFreeBlk--;
    finalblk++;
    int outputNum = 600;
    int finalmark = 0;
    int Cmark[2] = {201, 217};
    int mark[2] = {0};
    for (int i = 40; i < 61;) {
        Cmark[1] = 217;
        mark[1] = 0;
        free(dataR);
        dataR = getdata(buf, i, 216, &Cmark[0], &mark[0]);
        if (dataR == NULL) {
            printf("there is no %d\n", i);
            ++i;
            Cmark[0] = 201;
            mark[0] = 0;
            continue;
        } else {
            do {
                free(dataS);
                dataS = getdata(buf, i, 248, &Cmark[1], &mark[1]);
                if (dataS != NULL) {
                    //output
                    printf("intersect times:%d\n", count);
                    if (getInt(dataR + 4) == getInt(dataS + 4)) {
                        count++;
                        printf("(%d,%d) (%d,%d)\n",
                               getInt(dataR), getInt(dataR + 4),
                               getInt(dataS), getInt(dataS + 4));
                        writeBlockToDisk4q4(finalblk, &outputNum, buf, &finalmark, dataS);
                    }
                }
            } while (dataS != NULL);
        }
        printf("find %d end\n", i);
    }
    writeBlockToDisk(finalblk, outputNum, buf);
    printf("\nlink times:%d", count);
    return 0;
};