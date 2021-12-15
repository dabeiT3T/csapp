#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void *mcalloc(size_t nmemb, size_t size);

int main()
{
    int i;
    int nmemb = ARRAY_SIZE;
    int size = sizeof(int);

    int *a = (int *)mcalloc(nmemb, size);

    for (i = 0; i < ARRAY_SIZE; ++i)
        printf("%d ", a[i]);

    printf("\n");

    return 0;
}

void *mcalloc(size_t nmemb, size_t size)
{

    if (!nmemb || !size)
        return NULL;

    size_t require = nmemb * size;
    if (require < nmemb)
        return NULL;

    void *buff = malloc(require);
    memset(buff, 0, require);

    return buff;
    
}

