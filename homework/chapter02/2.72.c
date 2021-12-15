#include <stdio.h>
#include <string.h>

#define MAX_BYTES 10

void copy_int(int val, void *buf, int maxbytes);

int main()
{
    int a[MAX_BYTES];
    int x = 12345;

    copy_int(x, a, MAX_BYTES);

    printf("%d\n", a[0]);

    return 0;
}

void copy_int(int val, void *buf, int maxbytes)
{
    if (maxbytes > 0 && maxbytes >= sizeof(val))
        memcpy(buf, (void *) &val, sizeof(val));
}

