#include <bits/stdc++.h>

using namespace std;

const int MM = 1005;
int P[MM];
char A[MM] = " ";
char B[MM] = " ";
char End[] = "#";
char temp[MM];
int m, n;  // n母串长度，m子串长度

void pre_ope();
int KMP();

int main()
{
    while (scanf("%s", temp))
    {
        if (strcmp(End, temp) == 0)
            break;
        A[0] = B[0] = ' ';
        A[1] = B[1] = '\0';
        strcat(A, temp);
        scanf("%s", temp);
        strcat(B, temp);
        n = strlen(A) - 1;
        m = strlen(B) - 1;
        pre_ope();

        int ans = KMP();
        printf("%d\n", ans);
    }
    return 0;
}

void pre_ope()  // 预处理P数组，寻找字符串B前后匹配
{
    P[1] = 0;
    int j = 0;
    for (int i = 1; i < m; i++)
    {
        while (j > 0 && B[j + 1] != B[i + 1])  // 不能匹配且j未到达0，则后退一步
        {
            j = P[j];
        }
        if (B[j + 1] == B[i + 1])  // 能匹配，j+1
        {
            j ++;
        }
        P[i + 1] = j;  // 每趟循环求i+1位置
    }
}

int KMP()
{
    // A与B都是从下标1开始储存
    int ans = 0;
    int j = 0;  // 表示母串与子串从母串下表开始相同的个数
    for (int i = 0; i < n; i++)  // i为母串下表
    {
        while (j > 0 && B[j + 1] != A[i + 1])  // 如果不能继续匹配且j还未减少到0，减少j值
        {
            j = P[j];
        }
        if (B[j + 1] == A[i + 1])  // 能匹配则j++
        {
            j ++;
        }
        if (j == m)
        {
            ans ++;  // 记录匹配值，也可(i - m)获得子串串首出现在母串中的位置
            j = 0;  // 继续寻找且不可重叠（若想可重叠则j = P[j]）
        }
    }

    return ans;
}
