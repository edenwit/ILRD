#include <stdio.h>

int main()
{
    const int i = 3;
    int *ip = (int *)&i;
    *ip = 5;
    int arr[i];
    size_t j = 0;

    for (j = 0; j < i; ++j)
    {
        printf("%d", i);
    }
    
    printf("\n");

    return (0);
}