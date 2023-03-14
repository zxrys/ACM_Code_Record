#include <bits/stdc++.h>

#define ll long long

using namespace std;

struct num
{
    ll val;
    ll ord;
};

const ll MM = 100005;
struct num ora[MM];
ll disc[MM];
ll ts[MM];

bool cmp(struct num n1, struct num n2);
ll lowbit(int i);
ll sum(int i);
void update(int i, int val, int n);

int main()  // 离散化+树状数组
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        memset(ts, 0, sizeof(ts));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &ora[i].val);
            ora[i].ord = i;
        }

        sort(ora + 1, ora + n + 1, cmp);
        disc[ora[1].ord] = 1;
        int i, count;
        for (i = 2, count = 1; i <= n; i++)  // 离散化
        {
            if (ora[i].val == ora[i-1].val)  // 处理相同值
                disc[ora[i].ord] = count;
            else
                disc[ora[i].ord] = ++count;
        }

        ll res = 0;
        for (i = 1; i <= n; i++)
        {
            update(disc[i], 1, n);
            res += sum(n) - sum(disc[i]);
        }
        printf("%lld\n", res);
    }

    return 0;
}

bool cmp(struct num n1, struct num n2)
{
    return n1.val < n2.val;
}

ll lowbit(int i)
{
    return i & -i;
}

ll sum(int i)
{
    ll res = 0;
    while (i > 0)
    {
        res += ts[i];
        i -= lowbit(i);
    }
    return res;
}

void update(int i, int val, int n)
{
    while (i <= n)
    {
        ts[i] += val;
        i += lowbit(i);
    }
    return ;
}
