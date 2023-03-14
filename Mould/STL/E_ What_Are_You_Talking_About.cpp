#include <bits/stdc++.h>

using namespace std;

int main()
{
    string el, ml;
    string start = "START";
    string end = "END";
    map<string, string> m;

    cin >> el;
    while (cin >> el)
    {
        if (el == end)
            break;
        cin >> ml;
        m[ml] = el;
    }

    char str[100];
    char c;
    int count = 0;
    cin >> el;
    getchar();
    while(c = getchar())
    {
        if (c < 'A' || c > 'z')
        {
            if (count)
            {
                str[count] = '\0';
                map<string, string>:: iterator iter = m.find(str);
                if (str == end)
                    break;
                if (iter != m.end())
                {
                    cout << iter->second;
                }
                else
                {
                    cout << str;
                }
            }
            count = 0;
            printf("%c", c);
        }
        else
        {
            str[count] = c;
            count ++;
        }
    }
    
    return 0;
}
