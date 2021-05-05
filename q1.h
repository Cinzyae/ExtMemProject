//
// Created by 14153 on 2021/5/2.
//

#ifndef EXTMEM_C_Q1_H
#define EXTMEM_C_Q1_H
/*
 * 实现基于线性搜索的关系选择算法：
 * 基于ExtMem程序库，使用C语言实现线性搜索算法，选出S.C=50的元组，
 * 记录IO读写次数，并将选择结果存放在磁盘上。
 * （模拟实现selectS.C, S.D from S where S.C = 50）
 */

int
writeBlockToDisk4q1(unsigned char *finalblk, int *outputNum, Buffer *buf, int *finalmark,
                    unsigned char *data);

int q1(Buffer *buf);

#endif //EXTMEM_C_Q1_H
