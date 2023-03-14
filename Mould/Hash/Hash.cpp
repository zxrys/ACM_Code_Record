#include <bits/stdc++.h>

int pin[101];
int hash[2000003];

int main()
{
    int a, b, c, d;
    for (int i = 1; i <= 101; i++)
    {
        pin[i] = i * i;
    }

    while (scanf("%d %d %d %d", &a, &b, &c, &d) != EOF)
    {
        memset(hash, 0, sizeof(hash));
        if ((a>0 && b>0 && c>0 && d>0) || (a<0 && b<0 && c<0 && d<0))
        {
            printf("0\n");
            continue;
        }

        for (int i = 1; i <= 100; i++)
        {
            for (int j = 1; j <= 100; j++)
            {
                hash[a * pin[i] + b * pin[j] + 1000000] ++;
            }
        }

        long long sum = 0;
        for (int i = 1; i <= 100; i++)
        {
            for (int j = 1; j <= 100; j++)
            {
                sum += hash[-(c * pin[i] + d * pin[j]) + 1000000];
            }
        }
        printf("%lld\n", sum * 16);
    }

    return 0;
}
