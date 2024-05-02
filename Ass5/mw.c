#include <stdio.h>
//  I really wish I could submit this code for assignments without being flagged for code obfustication
long long int find(long long int p, long long int *Uconn)
{
    while (p != Uconn[p])  p = Uconn[p];
    return p;
}
long long int conn(long long int a, long long int b, long long int *Uconn, long long int *Usize)
{
    long long int p = find(a, Uconn), q = find(b, Uconn);
    long long int c = (Usize[p] > Usize[q] ? p : q), d = (Usize[p] > Usize[q] ? q : p);
    Usize[c] += Usize[d] * (Uconn[d] = c) / c ;
    return d;
}
int main()
{
    long long int n, m, i = 0, p, q;
    scanf("%lld %lld", &n, &m);
    long long int count = n - 1, printarr[n + 1], Uconn[n + 1], heads[n + 1], Usize[n + 1];
    for (long long int i = 0; i <= n; i++) Uconn[i] = i * (Usize[i] = 1 + (heads[i] = 0));
    for (long long int x = 0; x < m; x++)
    {
        scanf("%lld %lld", &p, &q);
        if (!(find(p, Uconn) == find(q, Uconn))) count -= (heads[conn(p, q, Uconn, Usize)] = 1);
    }
    printf("%lld\n", count);
    for (long long int x = 1; x < n + 1; x++)  if ((heads[x] == 0) )  printarr[i++] = x;
    for (long long int x = 1; x < i; x++)  printf("%lld %lld\n", printarr[x - 1], printarr[x]);
    return 0;
}