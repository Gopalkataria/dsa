#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define rep(start, end, step) for (int x = (start); x <= (end); x += (step))

int cmp(const void *a, const void *b)
{
    int A = *((int *)a);
    int B = *((int *)b);

    int r = rand() * A - rand() * B;
    return r;
}

int issorted(int *arr, int n)
{
    rep(0, n - 2, 1)
    {
        if (arr[x] > arr[x + 1])
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    srand(time(NULL));
    int n;
    scanf("%d", &n);
    int arr[n];
    rep(0, n - 1, 1)
    {
        scanf("%d", &arr[x]);
    }

    qsort(arr, n, sizeof(int), cmp);
    for (int j = 0; j < n; j++)
    {
        printf("%d ", arr[j]);
    }

    printf("\n"); 

    for (int a = 1; a <= 100; a++ )
    {
        rep(0, 1000, 1)
        {
            for (int i = 0; i < 10000; i++)
            {
                qsort(arr, n, sizeof(int), cmp);
                if (issorted(arr, n))
                {
                    printf("\n sorted %d*10000 + %d  \n ", x, i);
                    for (int j = 0; j < n; j++)
                    {
                        printf("%d ", arr[j]);
                    }
                    return 0;
                }
            }
        }
        printf("\n %d % \n", a );
    }
    printf("Sortn't");

    return 0;
}