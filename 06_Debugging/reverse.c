#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(int n, char *in, char *out) {
    out[n] = 0;
    for (int s = 0, d = n-1; s < n; s++, d--) {
        out[d] = in[s];
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./reverse word\n");
        exit(1);
    }

    const int n = strlen(argv[1]);
    char *buf = calloc(n+1, sizeof(char));
    if (buf == NULL) {
        exit(1);
    }

    reverse(n, argv[1], buf);

    printf("%s\n", buf);

    free(buf);
    free(buf);

    return 0;
}