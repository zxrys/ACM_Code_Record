#include <bits/stdc++.h>
typedef long long ll;

const int INF = 9999999;
const int MM = 20005;
int n, m, s;  // 点数，道路数，起点
int cnt, from[MM<<1], to[MM<<1], w[MM<<1];
int dist[MM], end[MM];  // 到此点距离，最后哪些点可以到达目标

void Bellmanfold();

int main()
{
    std::ios::sync_with_stdio(false);
    int a, b, c, num_end;
    while (std::cin >> n >> m >> s)
    {
        cnt = 0;
        for (int i = 0; i < MM; i++)
        {
            dist[i] = INF;
        }
        for (int i = 1; i <= m; i++)
        {
            std::cin >> a >> b >> c;
            from[++cnt] = b;
            to[cnt] = a;
            w[cnt] = c;
        }
        std::cin >> num_end;
        for (int i = 1; i <= num_end; i++)
        {
            std::cin >> end[i];
        }
        Bellmanfold();
        
        bool flag = false;
        for (int i = 1; i <= m; i++)
        {
            if (dist[to[i]] > dist[from[i]] + w[i])
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            std::cout << "-1\n";
            continue;
        }
        int min = INF;
        for (int i = 1; i <= num_end; i++)
        {
            if (dist[end[i]] < min)
            {
                min = dist[end[i]];
            }
        }
        if (min == INF)
        {
            std::cout << "-1\n";
        }
        else
        {
            std::cout << min << "\n";
        }
    }

    return 0;
}

void Bellmanfold()
{
    dist[s] = 0;
    for (int k = 1; k <= n - 1; k++)
    {
        for (int i = 1; i <= m; i++)
        {
            if (dist[to[i]] > dist[from[i]] + w[i])
            {
                dist[to[i]] = dist[from[i]] + w[i];
            }
        }
    }
}
