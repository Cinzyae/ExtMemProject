//
// Created by 14153 on 2021/5/3.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extmem.h"
#include "q2.h"

int SortExt(Buffer *buf, int start, int end) {
    int SortTimes = (end - start + 1) / 7;
    int SortRemain = (end - start + 1) % 7;

    unsigned char *blk; /* A pointer to a block */
    for (int i = 0; i < SortTimes; ++i) {
        /* Read the block from the hard disk */
        printf("read buf:");
        for (int j = 0; j < 7; ++j) {
            if (readBlockFromDisk(start + 7 * i + j, buf) == NULL) {
                perror("Reading Block Failed!\n");
                return -1;
            } else {
                printf("%d ", start + 7 * i + j);
            }
        }
        printf("\n");
        SortCache(buf, 7);
        freeBuffer(buf);
    }

    printf("read buf:");
    for (int j = 0; j < SortRemain; ++j) {
        if (readBlockFromDisk(start + 7 * SortTimes + j, buf) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        } else {
            printf("%d ", start + 7 * SortTimes + j);
        }
    }
    printf("\n");
    SortCache(buf, SortRemain);
    freeBuffer(buf);
    return 0;
}

int SortCache(Buffer *buf, int BlockNum) {
    printf(" sorting %d Blocks\n", BlockNum);
    for (int i = 0; i < BlockNum; ++i) {
        SortBlock(buf, i);
    }
    // TODO :merge
    // TODO :output
    return 0;
}

int SortBlock(Buffer *buf, int BlockNum) {
    printf("  sorting Block no.%d\n  ", BlockNum);
    unsigned char *blk; /* A pointer to a block */
    blk = buf->data + BlockNum * (buf->blkSize + 1) + 1;
    int X[7] = {0};
    int Y;
    for (int i = 0; i < 7; i++) //一个blk存7个元组加一个地址
    {
        X[i] = getInt(blk + i * 8);
        Y = getInt(blk + i * 8 + 4);
        printf(" (%d, %d) ", X[i], Y);
    }
    printf("\n   ->\n  ");

    // sort X[7]
    int MinX = 9999;
    for (int i = 0; i < 7; ++i) {
        MinX = i;
        for (int j = i; j < 7; ++j) {
            if (X[j] < X[MinX]) {
                MinX = j;
            }
        }
        // swap X[i] and X[MinX] with Y
        SwapN(blk + i * 8, blk + MinX * 8);
        int temp = 0;
        temp = X[i];
        X[i] = X[MinX];
        X[MinX] = temp;
    }

    for (int i = 0; i < 7; i++) //一个blk存7个元组加一个地址
    {
        X[i] = getInt(blk + i * 8);
        Y = getInt(blk + i * 8 + 4);
        printf(" (%d, %d) ", X[i], Y);
    }
    printf("\n");
    return 0;
}

int getInt(unsigned char *addr) {
    char str[5];
    for (int k = 0; k < 4; k++) {
        str[k] = *(addr + k);
    }
    return atoi(str);
}

void SwapN(unsigned char *addr1, unsigned char *addr2) {
    char temp[8];
    memcpy(temp, addr1, 8);
    memcpy(addr1, addr2, 8);
    memcpy(addr2, temp, 8);
}

int q2(Buffer *buf) {
//    SortExt(buf, 1, 7);
    SortExt(buf, 1, 16);
    SortExt(buf, 17, 48);
    return 0;
}