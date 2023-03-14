#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;
    int num[1005];
    while (scanf("%d %d", &N, &M) != EOF)
    {
        for (int i = 1; i <= N; i++)
        {
            num[i] = i;
        }
        for (int i = 0 ; i < M-1; i++)
        {
            next_permutation(num+1, num+N+1);
        }
        for (int i = 1; i <= N; i++)
        {
            printf("%d ", num[i]);
        }
        printf("\n");
    }

    return 0;
}
