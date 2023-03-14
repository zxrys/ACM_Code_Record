#include <bits/stdc++.h>

using namespace std;

int main()
{
    char c;
    int count, num_count;
    count = num_count = 0;
    stack<char> s;
    s.push('#');
    while (c = getchar(), c != '-')
    {
        if (c == '\n')
        {
            while (s.size() != 1)
            {
                if (s.top() == '{')
                {
                    count ++;
                    s.pop();
                    if (s.top() == '}')
                    {
                        count ++;
                        s.pop();
                    }
                    else
                    {
                        s.pop();
                    }
                }
                else if (s.top() == '}')
                {
                    count ++;
                    s.pop();
                    s.pop();
                }
            }
            num_count ++;
            printf("%d. %d\n", num_count, count);
            count = 0;
            continue;
        }
        if (c == '}' && s.top() == '{')
        {
            s.pop();
        }
        else
        {
            s.push(c);
        }
    }

    return 0;
}
