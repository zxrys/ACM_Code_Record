#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll MM = 10;  // 矩阵边长
ll mod;

struct matrix
{
    ll m[MM][MM];

    matrix()  // 自动调用初始化此矩阵
    {
        memset(m, 0, sizeof(m));
    }

    matrix operator *(const matrix b)  // 重写乘法
    {
        matrix res;
        for (int i = 0; i < MM; i++)
        {
            for (int j = 0; j < MM; j++)
            {
                for (int k = 0; k < MM; k++)
                {
                    res.m[i][j] = (res.m[i][j] + m[i][k] * b.m[k][j]) % mod;
                }
            }
        }
        return res;
    }
};

matrix q_p(ll k, matrix base);

int main()
{
    ll k;
    while (scanf("%lld %lld", &k, &mod) != EOF)
    {
        matrix base;  // 基础矩阵
        // 基础矩阵初始化
        for (int i = 0; i < MM; i++)
        {
            scanf("%lld", &base.m[0][i]);
        }
        ll i, j;
        for (i = 1, j = 0; i < MM; i++, j++)
        {
            base.m[i][j] = 1;
        }

        // for (int i = 0; i < MM; i++)
        // {
        //     for (int j = 0; j < MM; j++)
        //     {
        //         printf("%lld ", base.m[i][j]);
        //     }
        //     printf("\n");
        // }

        matrix res = q_p(k - 9, base);
        ll ans = 0;
        for (ll i = 0; i < MM; i++)
        {
            ans = (ans + res.m[0][MM-i-1] * (i)) % mod;
            //printf("%lld %lld\n", res.m[0][MM-i-1], ans);
        }
        printf("%lld\n", ans);
    }

    return 0;
}

matrix q_p(ll k, matrix base)  // 矩阵快速幂
{
    matrix res;
    ll i, j;
    for (i = j = 0; i < MM; i++, j++)  // 单位矩阵
    {
        res.m[i][j] = 1;
    }

    while (k > 0)
    {
        if (k & 1)
            res = res * base;
        base = base * base;
        k >>= 1;
    }

    return res;
}
