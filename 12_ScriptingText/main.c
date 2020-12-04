#include <stdio.h>

#include "buf.h"


int main(void) {
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);

    printf("Size of the buffer is %lu\n", buf_size(a));

    buf_free(a);
}