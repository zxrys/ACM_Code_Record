#include <bits/stdc++.h>
typedef long long ll;

const int INF = 999999;
const int MM = 205;
int n, m;
int dis[MM][MM];

void Floyd();

int main()  // 优点：可以一次性求出各点间的最短路，可解决负权。缺点：时间长（n^3）
{
    std::ios::sync_with_stdio(false);
    int a, b, c;
    c = 1;
    while (std::cin >> n >> m)
    {
        for (int i = 0; i < MM; i++)
        {
            for (int j = 0; j < MM; j++)
            {
                dis[i][j] = INF;
            }
        }
        // std::cout << dis[1][2] << "\n";
        for (int i = 0; i < MM; i++)
        {
            dis[i][i] = 0;
        }
        for (int i = 1; i <= m; i++)
        {
            std::cin >> a >> b;
            dis[a][b] = c;
            dis[b][a] = c;
        }
        Floyd();

        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            if (!flag)
                break;
            for (int j = 0; j < n; j++)
            {
                // std::cout << "|" << dis[i][j] << "|";
                if (dis[i][j] > 7)
                {
                    flag = false;
                    break;
                }
            }
        }

        if (flag)
        {
            std::cout << "Yes" << "\n";
        }
        else
        {
            std::cout << "No" << "\n";
        }
    }

    return 0;
}

void Floyd()
{
    for (int k = 0; k < n; k++)  // 插入点k，用于更新每次重新扫过所有路径
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}
