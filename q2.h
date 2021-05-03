//
// Created by 14153 on 2021/5/3.
//

#ifndef EXTMEM_C_Q2_H
#define EXTMEM_C_Q2_H

/*
 * 实现两阶段多路归并排序算法（TPMMS）：
 * 利用内存缓冲区将关系R和S分别排序，并将排序后的结果存放在磁盘上。
 * （不可定义长度大于10的整型或字符型数组）
 */
int q2(Buffer *buf);

int SortCache(Buffer *buf, int BlockNum);//sort blocks in cache

int SortBlock(Buffer *buf, int BlockNum);//sort numbers in block

int getInt(unsigned char *addr);

void SwapN(unsigned char *addr1, unsigned char *addr2);

#endif //EXTMEM_C_Q2_H
