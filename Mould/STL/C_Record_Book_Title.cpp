#include <bits/stdc++.h>

using namespace std;

int main()
{
    set<string> s;
    int n;
    string str;
    while(cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> str;
            s.insert(str);
        }

        int count = 0;
        for (set<string>::iterator iter = s.begin(); iter != s.end(); iter ++, count ++);
        printf("%d\n", count);
        s.clear();
    }
    

    return 0;
}
