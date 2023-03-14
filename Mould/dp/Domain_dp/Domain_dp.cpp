#include <bits/stdc++.h>

using namespace std;

const int MM = 205;
const int INF = 999999999;
int A[MM], B[MM], dp[MM][MM];

int main()  // 区间dp，题目boj advance_4 P_Dire_Wolf
{
    int T, cnt, res, n;
    scanf("%d", &T);
    cnt = 1;
    while (T--)
    {
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        memset(dp, 0, sizeof(dp));
        
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &A[i]);
        }
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &B[i]);
        }
        for (int i = 0; i < MM; i++)  // 初始化
        {
            for (int j = 0; j < MM; j++)
            {
                if (i > j)
                    dp[i][j] = 0;
                else if ( i < j)
                    dp[i][j] = INF;
                else
                    dp[i][i] = A[i] + B[i-1] + B[i+1];
            }
        }
        for (int i = 0; i < n; i++)  // 枚举长度
        {
            for (int j = 1; j + i <= n; j++)  // 枚举区间左端点
            {
                int l = j;  // 左端点
                int r = j + i;  // 右端点
                for (int k = j; k <= r; k++)  // 枚举分割点，更新小区间最优解
                {
                    dp[l][r] = min(dp[l][r], dp[l][k-1] + dp[k+1][r] + A[k] + B[l-1] + B[r+1]);
                }
            }
        }
        printf("Case #%d: %d\n", cnt++, dp[1][n]);
    }
    
    return 0;
}