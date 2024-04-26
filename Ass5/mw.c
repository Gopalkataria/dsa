#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef long long int ll;
ll *Uconn;
ll *Usize;

bool issame(ll p, ll q)
{
    while (p != Uconn[p])
    {
        p = Uconn[p];
    }
    while (q != Uconn[q])
    {
        q = Uconn[q];
    }
    return (p == q) ? true : false;
}
ll conn(ll p, ll q)
{
    while (p != Uconn[p])
    {
        p = Uconn[p];
    }
    while (q != Uconn[q])
    {
        q = Uconn[q];
    }
    ll c = Usize[p] > Usize[q] ? p : q;
    ll d = Usize[p] > Usize[q] ? q : p;
    Usize[c] += Usize[d];
    Uconn[d] = c;
    return d;
}
int main()
{
    ll n, m;
    scanf("%lld %lld", &n, &m);
    Uconn = (ll *)calloc((n + 1), sizeof(ll));
    Usize = (ll *)calloc((n + 1), sizeof(ll));
    for (ll i = 0; i <= n; i++)
    {
        Uconn[i] = i;
        Usize[i] = 1;
    }
    ll *heads = (ll *)calloc((n + 1), sizeof(ll));
    ll count = n - 1;
    ll p, q;
    for (ll x = 0; x < m; x++)
    {
        scanf("%lld %lld", &p, &q);
        if (!(issame(p, q)))
        {
            ll k = conn(p, q);
            heads[k] = 1;
            count--;
        }
    }
    printf("%lld\n", count);
    ll i = 0;
    ll printarr[n + 1];

    for (ll x = 1; x < n + 1; x++)
    {
        if (heads[x] == 0)
        {
            printarr[i++] = x;
        }
    }
    for (ll x = 1; x < i; x++)
    {
        printf("%lld %lld\n", printarr[x - 1], printarr[x]);
    }
    return 0;
}