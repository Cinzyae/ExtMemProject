#include <stdlib.h>
#include <stdio.h>
#include "extmem.h"
#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"

int main(int argc, char **argv) {
    Buffer buf;
    /* Initialize the buffer */
    if (!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }

    int sw = 0;
    while (1) {
        printf("\n\n-------------\ninput code to func:\n");
        printf("1. select S.C, S.D from S where S.C = 50\n");
        printf("2. TPMMS\n");
        printf("3. select S.C, S.D from S where S.C = 50(base on index)\n");
        printf("4. selectS.C, S.D, R.A, R.B from S inner join R on S.C = R.A\n");
        printf("press 0 to quit\n");
        printf("your input:");

        scanf("%d", &sw);
        switch (sw) {
            case 1:
                q1(&buf);
                freeBuffer(&buf);
                break;
            case 2:
                q2(&buf);
                freeBuffer(&buf);
                break;
            case 3:
                q3(&buf);
                freeBuffer(&buf);
                break;
            case 4:
                q4(&buf);
                freeBuffer(&buf);
                break;
            case 0:
                return 0;
            default:
                printf("input wrong!\n");
        }
    }
}

/*
 * 数据：
 * 零伯：原始数据
 * 一伯：块内排序
 * 二伯；块间排序
 * 三伯：索引
 * 四伯：根据索引搜索的结果
 * 五伯：连接结果
 */