//
// Created by 14153 on 2021/5/5.
//
/*
 * 实现基于排序的连接操作算法（Sort-Merge-Join）：
 * 对关系S和R计算S.C连接R.A ，并统计连接次数，将连接结果存放在磁盘上。
 * （模拟实现selectS.C, S.D, R.A, R.B from S inner join R on S.C = R.A）
 */
#ifndef EXTMEM_C_Q4_H
#define EXTMEM_C_Q4_H

int
writeBlockToDisk4q4(unsigned char *finalblk, int *outputNum, Buffer *buf, int *finalmark,
                    unsigned char *data);

// while the buf from Cmark,mark to end, find data march num.return data.
unsigned char *getdata(Buffer *buf, int num, int end, int *Cmark, int *mark);

int q4(Buffer *buf);

#endif //EXTMEM_C_Q4_H
