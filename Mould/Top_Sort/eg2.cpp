#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct Edge
{
    ll to, val, next;
};

const ll NN = 10005;
const ll MM = 20005;
ll head[NN];
struct Edge edge[MM];
ll indegree[NN];

ll Count, Res, Money, Out_count;

void add_edge(ll from, ll to, ll val);
void top_sort(ll n);

int main()
{
    ll n, m;
    while (scanf("%lld %lld", &n, &m) != EOF)
    {
        ll a, b;
        Count = Res = Out_count = 0;
        Money = 888;
        memset(head, -1, sizeof(head));
        memset(indegree, 0, sizeof(indegree));
        for (ll i = 0; i < m; i++)
        {
            scanf("%lld %lld", &a, &b);
            add_edge(b, a, 1);
            indegree[a] ++;
            //printf(">>\n");
        }
        top_sort(n);
        if (Out_count != n)
        {
            printf("-1\n");
        }
        else
        {
            printf("%d\n", Res);
        }
    }

    return 0;
}

void add_edge(ll from, ll to, ll val)  // 链式前向星储存实现邻接表
{
    edge[++Count].to = to;
    edge[Count].val = val;
    edge[Count].next = head[from];
    head[from] = Count;
}

void top_sort(ll n)
{
    queue<int> qu;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (!indegree[j])
            {
                indegree[j] --;
                Res += Money;
                qu.push(head[j]);
                //printf("%d\n", head[j]);
                Out_count ++;
            }
        }

        int temp;
        while(!qu.empty())
        {
            for (temp = qu.front(); temp != -1; temp = edge[temp].next)
            {
                //printf("%d\n", temp);
                edge[temp].val --;
                indegree[edge[temp].to] --;
            }
            qu.pop();
        }
        Money ++;
    }
}
