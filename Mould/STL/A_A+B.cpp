#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b;
    set<int> s;

    while (scanf("%d %d", &a, &b) != EOF)
    {
        int temp;
        for (int i = 0; i < a; i++)
        {
            scanf("%d", &temp);
            s.insert(temp);
        }
        for (int i = 0; i < b; i++)
        {
            scanf("%d", &temp);
            s.insert(temp);
        }
        set<int>::iterator iter;
        for (iter = s.begin(); iter != s.end(); iter++)
        {
            printf("%d ", *iter);
        }
        printf("\n");
        s.clear();
    }

    return 0;
}
