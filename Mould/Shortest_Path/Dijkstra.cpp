#include <bits/stdc++.h>
typedef long long ll;

const int INF = 0x7fffffff;
const int MM = 1e5 + 5;
int n, m, s;  // 点数，道路数，起点
int cnt, head[MM<<1], to[MM<<1], next[MM<<1], dis[MM<<1];  // 链式前向星记录，头，目标，下一个，边权
int dist[MM], vis[MM];  // 到此点距离，vis记录

struct node  // 优先队列优化使用
{
    int id, dis;
    bool operator<(const node &a)const{return a.dis < dis;}
};

void add_edge(int from_, int to_, int w_);
void Dijkstra();

int main()  // 优点：快（nlogn）；缺点：不易求任意两点的最短路径，无法处理负边权
{
    std::ios::sync_with_stdio(false);
    
    int a, b, c;
    while (std::cin >> n >> m)
    {
        if (!n)
        {
            break;
        }
        // 初始化
        memset(head, 0, sizeof(head));
        memset(vis, 0, sizeof(vis));
        cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            dist[i] = INF;
            // std::cout << dist[i] << "\n";
        }

        for (int i = 1; i <= m; i++)
        {
            std::cin >> a >> b >> c;
            add_edge(a, b, c);
            add_edge(b, a, c);
        }
        
        s = 1;
        Dijkstra();
        std::cout << dist[n] << "\n";
    }

    return 0;
}

void add_edge(int from_, int to_, int w_)
{
    to[++cnt] = to_;
    dis[cnt] = w_;
    next[cnt] = head[from_];
    head[from_] = cnt;
}

void Dijkstra()
{
    std::priority_queue<node> q;
    q.push(node{s, 0});

    dist[s] = 0;
    while (!q.empty())
    {
        node a = q.top();
        q.pop();
        int current = a.id;

        if (vis[current])
        {
            continue;
        }
        vis[current] = 1;
        for (int i = head[current]; i; i = next[i])
        {
            int j = to[i];

            if (dist[current] + dis[i] < dist[j])
            {
                dist[j] = dist[current] + dis[i];
                q.push(node{j, dist[j]});
            }
        }
    }
}
