#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll MM = 200005;

ll dp[MM], vis[MM], point_weight[MM];  // 最大点券数组记录，vis，点权
ll f[MM], q[MM], qtop;  // 强连通分量，出栈顺序，顺序记录
ll n, m;
ll u[MM*2], v[MM*2];  // 起点，目标点
ll ahead[MM], ato[MM], anext[MM], atop;  // 正向图
ll bhead[MM], bto[MM], bnext[MM], btop;  // 反向图

void dfs1(ll x);  // 建立出栈顺序
void dfs2(ll x, ll y);  // 建立强连通分量

void add_edge(ll x, ll y);  // 链式前向星双向建边

// 以下求最大点权，若只用求强连通分量到上面位置
void build_graph();  // 补建立两个强连通分量间本存在的边
void rdfs(ll x);  // 结果最大点权dfs

int main()
{
    ll T;
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld %lld", &n, &m);
        memset(q, 0, sizeof(q));
        memset(ahead, 0, sizeof(ahead));
        memset(bhead, 0, sizeof(bhead));
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        atop = btop = qtop = 0;
        for (ll i = 1; i <= n; i++)
        {
            scanf("%lld", &point_weight[i]);
        }
        for (ll i = 1; i <= m; i++)
        {
            scanf("%lld %lld", &u[i], &v[i]);
            add_edge(u[i], v[i]);
        }

        for (ll i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                dfs1(i);
            }
        }
        for (ll i = qtop - 1; i >= 0; i--)
        {
            if (vis[q[i]])
            {
                dfs2(q[i], q[i]);
            }
        }
        atop = btop = qtop = 0;
        memset(ahead, 0, sizeof(ahead));
        memset(bhead, 0, sizeof(bhead));
        build_graph();
        for (ll i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                rdfs(i);
            }
        }
        for (ll i = 1; i <= n; i++)
        {
            printf("%lld\n", dp[f[i]]);
        }
    }

    return 0;
}

void add_edge(ll x, ll y)
{
    ato[++atop] = y;
    anext[atop] = ahead[x];
    ahead[x] = atop;

    bto[++btop] = x;
    bnext[btop] = bhead[y];
    bhead[y] = btop;
}

void dfs1(ll x)
{
    vis[x] = 1;
    for (ll i = bhead[x]; i; i = bnext[i])
    {
        if (!vis[bto[i]])
        {
            dfs1(bto[i]);
        }
    }
    q[qtop++] = x;
}

void dfs2(ll x, ll y)
{
    vis[x] = 0;
    for (ll i = ahead[x]; i; i = anext[i])
    {
        if (vis[ato[i]])
        {
            dfs2(ato[i], y);
        }
    }
    f[x] = y;
    dp[y] = max(dp[y], point_weight[x]);
}

void build_graph()
{
    for (ll i = 1; i <= m; i++)
    {
        if (f[u[i]] != f[v[i]])
        {
            add_edge(f[u[i]], f[v[i]]);
        }
    }
}

void rdfs(ll x)
{
    vis[x] = 1;
    dp[f[x]] = max(point_weight[x], dp[f[x]]);
    for (ll i = ahead[x]; i; i = anext[i])
    {
        if (!vis[ato[i]])
        {
            rdfs(ato[i]);
        }
        dp[x] = max(dp[x], dp[ato[i]]);
    }
}
