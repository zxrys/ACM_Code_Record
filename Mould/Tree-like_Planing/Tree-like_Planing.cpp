#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:1024000000,1024000000")
typedef long long ll;

const int MM = 2e5 + 5;
int tot, head[MM], next[MM], to[MM], val[MM];  // 链式前向星计数，head，next，to，value
int f[MM], d[MM], son[MM], size[MM], top[MM];  // 父节点，深度，儿子节点，子树大小，重链开头
int dfsn, Nid[MM], Oid[MM];  // dfs序，new id，old id
int segval[MM<<2], seglazy[MM<<2];  // 线段树值，线段树lazy
int n, m, p, mod, root;

// 以下为链式前向星加边
void add_edge(int from_, int to_);

// 以下为树状刨分操作
void dfs1(int x, int father);  // 第一遍dfs，计算size、depth、son、father
void dfs2(int x, int topx);  // 第二遍dfs，计算重链的top，同时由于dfs序原因，每个重链上点区间连续，每个子树上的点区间连续，引入线段树进行删改查操作
int lca(int x, int y);  // 最近公共祖先

// 以下为线段树操作
void push_up(int rt);
void build(int l, int r, int rt);
void push_down_change(int rt, int ln, int rn);  // 此处未用到
void push_down_add(int rt, int ln, int rn);
void update_change(int L, int R, int k, int l, int r, int rt);  // 此处未用到
void update_add(int L, int R, int k, int l, int r, int rt);
int query(int L, int R, int l, int r, int rt);

// 以下为删改查操作
void r_add(int x, int y, int k);
int r_query(int x, int y);
void s_add(int rt, int k);
int s_query(int rt);

int main()
{
    std::ios::sync_with_stdio(false);
    int a, b, c, k;
    
    while(std::cin >> n)
    {
        m = n - 1;
        for (int i = 0; i < MM; i++)
        {
            Nid[i] = Oid[i] = f[i] = d[i] = son[i] = size[i] = top[i] = 0;
            head[i] = 0;
        }
        for (int i = 0; i < (MM << 2); i++)
        {
            segval[i] = seglazy[i] = 0;
        }
        // memset(head, 0, sizeof(head));
        // memset(son, 0, sizeof(son));
        // memset(top, 0, sizeof(top));
        // d[0] = 0;
        // f[0] = 0;
        // size[0] = 0;
        tot = 0;
        dfsn = 0;

        for (int i = 1; i <= m; i++)
        {
            std::cin >> a >> b >> c;
            add_edge(a, b);
            add_edge(b, a);
        }
        dfs1(root, root);
        dfs2(root, root);
        build(1, n, 1);
        for (int i = 1; i <= p; i++)
        {
            std::cin >> c;
            // std::cout << "|" << c << "|\n";
            if (c == 1)
            {
                std::cin >> a >> b >> k;
                r_add(a, b, k);
            }
            else if (c == 2)
            {
                std::cin >> a >> b;
                std::cout << r_query(a, b) << "\n";
            }
            else if (c == 3)
            {
                std::cin >> a >> k;
                s_add(a, k);
            }
            else
            {
                std::cin >> a;
                std::cout << s_query(a) << "\n";
            }
        }
    }

    return 0;
}

void add_edge(int from_, int to_)
{
    to[++tot] = to_;
    next[tot] = head[from_];
    head[from_] = tot;
}

void dfs1(int x, int father)
{
    size[x] = 1;
    d[x] = d[father] + 1;  // d[0]=0，根节点深度为1
    son[x] = 0;  // 默认儿子不存在
    f[x] = father;
    for (int i = head[x]; i != 0; i = next[i])
    {
        int to_ = to[i];
        if (to_ == father) continue;
        dfs1(to_, x);
        size[x] += size[to_];
        if (size[son[x]] < size[to_])
        {
            son[x] = to_;
        }
    }
}

void dfs2(int x, int topx)
{
    top[x] = topx;

    Nid[x] = ++dfsn;  // 原始元素x对应的新序号
    Oid[dfsn] = x;  // 新序号对应的原始元素老编号为x，即Oid[Nid[x]] = x
    // std::cout << "|" << Nid[x] << " " << Oid[dfsn] << "|\n";

    if (son[x] == 0)  // 有限处理重边，保证d重边区间连续
    {
        return ;
    }

    dfs2(son[x], top[x]);

    for (int i = head[x]; i != 0; i = next[i])
    {
        if (to[i] != f[x] && to[i] != son[x])
        {
            dfs2(to[i], to[i]);
        }
    }
}  // 若对以x为根的整个树操作，对应区间为[Nid[x], Nid[x] + size[x] - 1]

int lca(int x, int y)
{
    while (top[x] != top[y]) // 不在同一重链上
    {
        if (d[top[x]] < d[top[y]])  // 比较重链头节点深度大小
        {
            std::swap(x, y); // 始终让top[x]深度更大
        }
        x = f[top[x]];  // x跳到重链头的父节点
    }

    return d[x] < d[y] ? x : y;
}


void push_up(int rt)
{
    segval[rt] = (segval[rt << 1] + segval[rt << 1 | 1]) % mod;
    return ;
}

void build(int l, int r, int rt)
{
    seglazy[rt] = 0;
    if (l == r)
    {
        segval[rt] = val[Oid[l]] % mod;
        // std::cout << "|" << rt << " " << l << "|\n";
        return ;
    }

    int M = (l + r) >> 1;
    build(l, M, rt << 1);
    build(M + 1, r, rt << 1 | 1);
    push_up(rt);
}

void push_down_change(int rt, int ln, int rn)
{
    if (seglazy[rt] != 0)
    {
        seglazy[rt << 1] = seglazy[rt];
        seglazy[rt << 1 | 1] = seglazy[rt];
        segval[rt << 1] = seglazy[rt] * ln;
        segval[rt << 1 | 1] = seglazy[rt] * rn;

        seglazy[rt] = 0;
    }
    return ;
}

void push_down_add(int rt, int ln, int rn)
{
    if (seglazy[rt] != 0)
    {
        seglazy[rt << 1] += seglazy[rt];
        seglazy[rt << 1 | 1] += seglazy[rt];
        segval[rt << 1] += seglazy[rt] * ln;
        segval[rt << 1 | 1] += seglazy[rt] * rn;

        segval[rt << 1] %= mod;
        segval[rt << 1 | 1] %= mod;

        seglazy[rt] = 0;
    }
    return ;
}

void update_change(int L, int R, int k, int l, int r, int rt)  // 更新区间L，更新区间R，值，大区间l，大区间r，rt
{
    if (L <= l && R >= r)
    {
        segval[rt] = k * (r - l + 1);
        seglazy[rt] = k;
        return ;
    }

    int M = (l + r) >> 1;
    push_down_change(rt, M - l + 1, r - M);
    if (L <= M) update_change(L, R, k, l, M, rt << 1);
    if (R > M) update_change(L, R, k, M + 1, r, rt << 1 | 1);
    push_up(rt);
    return ;
}

void update_add(int L, int R, int k, int l, int r, int rt)  // 更新区间L，更新区间R，值，大区间l，大区间r，rt
{
    if (L <= l && R >= r)
    {
        segval[rt] += k * (r - l + 1);
        segval[rt] %= mod;
        seglazy[rt] += k;
        return ;
    }

    int M = (l + r) >> 1;
    push_down_add(rt, M - l + 1, r - M);
    if (L <= M) update_add(L, R, k, l, M, rt << 1);
    if (R > M) update_add(L, R, k, M + 1, r, rt << 1 | 1);
    push_up(rt);
    return ;
}

int query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        return segval[rt] % mod;
    }
    if (L > r || R < l)
    {
        return 0;
    }

    int M = (l + r) >> 1;
    push_down_add(rt, M - l + 1, r - M);
    return (query(L, R, l, M, rt << 1) + query(L, R, M + 1, r, rt << 1 | 1)) % mod;
}


// 具体实现区间的修改、查询
// 和根据需要写成不同函数
void r_add(int x, int y, int k)
{
    k %= mod;
    while (top[x] != top[y])  // 非同一重链
    {
        if (d[top[x]] < d[top[y]])
        {
            std::swap(x, y);
        }
        update_add(Nid[top[x]], Nid[x], k, 1, n, 1);
        
        x = f[top[x]];  // 跳到重链top的father
    }

    if (d[x] > d[y])
    {
        std::swap(x, y);
    }
    update_add(Nid[x], Nid[y], k, 1, n, 1);
    
    return ;
}

int r_query(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if (d[top[x]] < d[top[y]])
        {
            std::swap(x, y);
        }
        ans += query(Nid[top[x]], Nid[x], 1, n, 1);
        ans %= mod;
        x = f[top[x]];
    }

    if (d[x] > d[y])
    {
        std::swap(x, y);
    }
    ans += query(Nid[x], Nid[y], 1, n, 1);
    return ans % mod;
}

void s_add(int rt, int k)
{
    update_add(Nid[rt], Nid[rt] + size[rt] - 1, k, 1, n, 1);
}

int s_query(int rt)
{
    return query(Nid[rt], Nid[rt] + size[rt] - 1, 1, n, 1) % mod;
}
