//
// Created by 14153 on 2021/5/4.
//

#ifndef EXTMEM_C_Q3_H
#define EXTMEM_C_Q3_H

int q3(Buffer *buf);

int buildIndex(Buffer *buf, int start, int end);

int searchBlock(unsigned char *blk);

int handleResult(Buffer *buf, int BlockNum);

int searchIndex(Buffer *buf, int start, int end);

#endif //EXTMEM_C_Q3_H
