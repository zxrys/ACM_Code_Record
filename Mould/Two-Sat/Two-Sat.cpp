#include <bits/stdc++.h>

using namespace std;

const int MM = 6005;
const int NN = 100005;
int T, M;
int qtop, q[NN], f[MM], vis[MM];  // q数组计数，出栈顺序（第一遍dfs得到）
int ahead[MM], ato[NN], anxt[NN], atop;
int bhead[MM], bto[NN], bnxt[NN], btop;

void add_edge(int x, int y);  // 链式前向星加边

// 以下为强连通分量kosaraju算法
void dfs1(int x);
void dfs2(int x, int y);

int main()
{
    while (~scanf("%d %d", &T, &M))
    {
        memset(vis, 0, sizeof(vis));
        memset(f, -1, sizeof(f));
        memset(ahead, -1, sizeof(ahead));
        memset(bhead, -1, sizeof(bhead));
        atop = btop = qtop = 0;
        int a, b, c;
        for (int i = 0; i < T; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            add_edge(a, b + T * 3);  // a留b走
            add_edge(a, c + T * 3);  // a留c走
            add_edge(b, c);  // b走c走
            add_edge(c, b);  // c走b走
            add_edge(b, a + T * 3);  // b留a走
            add_edge(c, a + T * 3);  // c留a走
            add_edge(b + T * 3, c + T * 3);  // ...
            add_edge(c + T * 3, b + T * 3);
            add_edge(b + T * 3, a);
            add_edge(c + T * 3, a);
            add_edge(a + T * 3, b);
            add_edge(a + T * 3, c);
        }
        for (int i = 0; i < M; i++)
        {
            scanf("%d %d", &a, &b);
            add_edge(a, b + T * 3);
            add_edge(b, a + T * 3);
        }
        for (int i = 0; i < T * 6; i++)
        {
            if (!vis[i])
                dfs1(i);
        }
        for (int i = qtop - 1; i >= 0; i--)  // 按q数组从n-1到0的顺序dfs2
        {
            if (vis[q[i]])
                dfs2(q[i], q[i]);
        }
        bool flag = true;
        for (int i = 0; i < T * 3; i++)
        {
            //printf("|%d %d|\n", f[i], f[i+T*3]);
            if (f[i] == f[i + T * 3])
            {
                flag = false;
                break;
            }
        }
        if (flag)
            printf("yes\n");
        else
            printf("no\n");
    }

    return 0;
}

void add_edge(int x, int y)
{
    anxt[atop] = ahead[x];
    ato[atop] = y;
    ahead[x] = atop;
    atop ++;

    bnxt[btop] = bhead[y];
    bto[btop] = x;
    bhead[y] = btop;
    btop ++;
}

void dfs1(int x)
{
    vis[x] = 1;
    for (int i = bhead[x]; i != -1; i = bnxt[i])
    {
        if (vis[bto[i]]) continue;
        dfs1(bto[i]);
    }
    q[qtop++] = x;
}

void dfs2(int x, int y)
{
    vis[x] = 0;
    for (int i = ahead[x]; i != -1; i = anxt[i])
    {
        if (!vis[ato[i]]) continue;
        dfs2(ato[i], y);
    }
    f[x] = y;
}
