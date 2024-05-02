#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef long long int ll;

ll find(ll p, ll *Uconn)
{
    while (p != Uconn[p])
        p = Uconn[p];
    return p;
}
bool issame(ll p, ll q, ll *Uconn, ll *Usize)
{
    return (find(p, Uconn) == find(q, Uconn)) ? true : false;
}
ll conn(ll a, ll b, ll *Uconn, ll *Usize)
{
    ll p = find(a, Uconn), q = find(b, Uconn);
    ll c = (Usize[p] > Usize[q] ? p : q), d = (Usize[p] > Usize[q] ? q : p);
    Usize[c] += Usize[d];
    Uconn[d] = c;
    return d;
}
int main()
{
    ll n, m, p, q;
    scanf("%lld %lld", &n, &m);
    ll count = n - 1, i = 0, printarr[n + 1];
    ll Uconn[n + 1], heads[n + 1], Usize[n + 1];
    for (ll i = 0; i <= n; i++)
        Uconn[i] = i * (Usize[i] = 1 + (heads[i] = 0));
    for (ll x = 0; x < m; x++)
    {
        scanf("%lld %lld", &p, &q);
        if (!(issame(p, q, Uconn, Usize)))
            count -= (heads[conn(p, q, Uconn, Usize)] = 1);
    }
    printf("%lld\n", count);
    for (ll x = 1; x < n + 1; x++)
        if (heads[x] == 0)
            printarr[i++] = x;
    for (ll x = 1; x < i; x++)
        printf("%lld %lld\n", printarr[x - 1], printarr[x]);
    return 0;
}