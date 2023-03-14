#include <bits/stdc++.h>

using namespace std;

int main()
{
    stack<char> st;
    int n;
    char c_i, c_o;
    int i_i, i_o, i_r;
    string t_i, t_o;
    int record[20];
    bool flag;
    while (cin >> n >> t_i >> t_o)
    {
        flag = true;
        i_i = i_o = i_r = 0;
        st.push('#');
        st.push(t_i[i_i]);
        record[i_r] = 1;
        i_r++;

        while (t_o[i_o] != '\0')
        {
            //printf("%c %c\n", st.top(), t_o[i_o]);
            while (st.top() != t_o[i_o])
            {
                i_i++;
                if (i_i >= n)
                {
                    flag = false;
                    break;
                }
                st.push(t_i[i_i]);
                record[i_r] = 1;
                i_r++;
            }
            if (!flag)
                break;
            st.pop();
            i_o++;
            record[i_r] = 0;
            i_r++;
        }
        if (!flag)
        {
            printf("No.\n");
        }
        else
        {
            printf("Yes.\n");
            for (int i = 0; i < n * 2; i++)
            {
                if (record[i])
                    printf("in\n");
                else
                    printf("out\n");
            }
        }
        printf("FINISH\n");
    }

    return 0;
}
