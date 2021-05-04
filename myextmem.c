#include <stdlib.h>
#include <stdio.h>
#include "extmem.h"
#include "q1.h"
#include "q2.h"
#include "q3.h"

int main(int argc, char **argv) {
    Buffer buf;
    /* Initialize the buffer */
    if (!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }
/*
    int sw = 0;
    while (1) {
        printf("-------------\ninput code to func:\n");
        printf("1. select S.C, S.D from S where S.C = 50\n");
        printf("your input:");

        scanf("%d", &sw);
        switch (sw) {
            case 1:
                q1(&buf);
                break;
            case 2:
                q2(&buf);
                break;
            case -1:
                return 0;
            default:
                printf("input wrong!\n");
        }
    }
*/
    q1(&buf);
//    q2(&buf);
    q3(&buf);
}

