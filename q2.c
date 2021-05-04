//
// Created by 14153 on 2021/5/3.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extmem.h"
#include "q2.h"

#define MAXINT 9999

int SortExt(Buffer *buf, int start, int end) {
    int SortTimes = (end - start + 1) / 7;
    int SortRemain = (end - start + 1) % 7;

    for (int i = 0; i < SortTimes; ++i) {
        /* Read the block from the hard disk */
        printf("\nread buf:");
        for (int j = 0; j < 7; ++j) {
            if (readBlockFromDisk(start + 7 * i + j, buf) == NULL) {
                perror("Reading Block Failed!\n");
                return -1;
            } else {
                printf("%d ", start + 7 * i + j);
            }
        }
        printf("\n");
        SortCache(buf, 7, start + 7 * i, start + 7 * i + 6);
        freeBuffer(buf);
    }

    printf("\nread buf:");
    for (int j = 0; j < SortRemain; ++j) {
        if (readBlockFromDisk(start + 7 * SortTimes + j, buf) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        } else {
            printf("%d ", start + 7 * SortTimes + j);
        }
    }
    printf("\n");
    SortCache(buf, SortRemain, start + 7 * SortTimes, start + 7 * SortTimes + SortRemain - 1);
    freeBuffer(buf);

    // TODO :outer sort
    return 0;
}

int SortCache(Buffer *buf, int BlockNum, int start, int end) {
    printf(" sorting %d Blocks from %d to %d\n", BlockNum, start, end);
    for (int i = 0; i < BlockNum; ++i) {
        SortBlock(buf, i);
    }
    // merge
    int X[7] = {0};
    int mark[7] = {0};
    printf(" merging:\n ");
    for (int i = 0; i < BlockNum; i++) //一个blk存7个元组加一个地址
    {
        X[i] = getInt(buf->data + i * (buf->blkSize + 1) + 1 + 8 * mark[i]);
        printf(" %d", X[i]);
    }

    unsigned char *blk; /* A pointer to a block */
    blk = buf->data + 7 * (buf->blkSize + 1);
    *blk = BLOCK_UNAVAILABLE;
    buf->numFreeBlk--;
    blk++;

    int MinX;
    // blk is a pointer to the 8th block of cache.
    for (int i = 0; i < 7 * BlockNum; ++i) {
        // write block
        MinX = 0;
        // find the min x from blocks with the number of BlockNum.
        for (int j = 0; j < BlockNum; ++j) {
            if (X[j] < X[MinX]) {
                MinX = j;
            }
        }
        // modify blk.
        printf("\n%d %d %d %d %d %d %d", X[0], X[1], X[2], X[3], X[4], X[5], X[6]);
        printf("\ntotal %d,block %d,number %d:%d", i, MinX, mark[MinX], X[MinX]);
        if (X[MinX] == MAXINT) {
            break;
        } else {
            printf("\ncopy %d from %d\n",
                   getInt(blk + (i % 7) * 8),
                   getInt(buf->data + MinX * (buf->blkSize + 1) + 1 + 8 * mark[MinX]));
            memcpy(blk + (i % 7) * 8, buf->data + MinX * (buf->blkSize + 1) + 1 + 8 * mark[MinX], 8);
            mark[MinX]++;
            if (mark[MinX] > 6) {
                mark[MinX] = 6;
                X[MinX] = MAXINT;
            } else {
                X[MinX] = getInt(buf->data + MinX * (buf->blkSize + 1) + 1 + 8 * mark[MinX]);
            }
        }
        if (i % 7 == 6) {
            int show[7];
            int Y;
            printf("output:\n");
            for (int l = 0; l < 7; l++) //一个blk存7个元组加一个地址
            {
                show[l] = getInt(blk + l * 8);
                Y = getInt(blk + l * 8 + 4);
                printf(" (%d, %d) ", show[l], Y);
            }
            printf("\n");
            writeBlockToDisk(blk, 100 + start + i / 7, buf);
        }
    }
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
        //printf(" (%d, %d) ", X[i], Y);
    }
    //printf("\n   ->\n  ");
    printf("  ");
    // sort X[7]
    int MinX = MAXINT;
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