//
// Created by 14153 on 2021/5/4.
//

/*
 * 实现基于索引的关系选择算法：
 * 利用（2）中的排序结果为关系S建立索引文件，利用索引文件选出S.C=50的元组，
 * 并将选择结果存放在磁盘上。记录IO读写次数，与（1）中的结果对比。
 * （模拟实现selectS.C, S.D from S where S.C = 50 ）
 */

#ifndef EXTMEM_C_Q3_H
#define EXTMEM_C_Q3_H

int q3(Buffer *buf);

int buildIndex(Buffer *buf, int start, int end);

int searchBlock(unsigned char *blk, int num);

int handleResult(Buffer *buf, int BlockNum);

int searchIndex(Buffer *buf, int start, int end);

#endif //EXTMEM_C_Q3_H
