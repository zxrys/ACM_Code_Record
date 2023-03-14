#include <bits/stdc++.h>

using namespace std;

const int MM = 505;
int grapg[MM][MM], indegree[MM], res[MM];

void topsort(int n);

int main()  // 拓扑排序，一般用于处理前置要求，如比赛排名A赢了B、课程学习先学C再学ACM
{
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        memset(grapg, 0, sizeof(grapg));
        memset(indegree, 0, sizeof(indegree));
        memset(res, 0, sizeof(res));
        int t1, t2;
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d", &t1, &t2);
            if (!grapg[t1][t2])
            {
                grapg[t1][t2] = 1;
                indegree[t2] ++;
            }
        }

        topsort(n);
        for (int i = 1; res[i] != 0; i++)
        {
            printf("%d ", res[i]);
        }
        printf("\n");
    }

    return 0;
}

void topsort(int n)  // 根据具体题目修改，如要求广度优先引入priority_queue
{
    int k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (!indegree[j])
            {
                indegree[j] --;
                res[i] = j;
                k = j;
                break;
            }
        }

        for (int j = 1; j<= n; j++)
        {
            if (grapg[k][j])
            {
                grapg[k][j] --;
                indegree[j] --;
            }
        }
    }
}
