// cf546E
// 网络流, dinic
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;


struct Edge
{   int u, v;
    int cap, res;
    int next;
};

class Dinic
{public:
    static const int N = 300;
    static const int M = 2000;
    static const int Inf = 0x3f3f3f3f;
    int n, m;
    Edge E[M+10];
    int s[N+10];
    int src, snk;

    int que[N+10];
    bool vis[N+10];
    int dist[N+10];
    int cur[N+10];


    void init()
    {   
        memset(s, 0, sizeof(s));
        n = 0;  m = 1;
    }

    void add_edge(int u, int v, int cap)
    {
        int p = ++m;
        E[p].u = u;  E[p].v = v;  E[p].res = E[p].cap = cap;
        E[p].next = s[u];  s[u] = p;
    }

    void add_edge2(int u, int v, int cap)
    {
        add_edge(u, v, cap);
        add_edge(v, u, 0);
    }

    bool bfs()
    {
        memset(que, 0, sizeof(que));
        memset(vis, 0, sizeof(vis));
        memset(dist, 0, sizeof(dist));
    
        int f = 1, p = 2;
        que[1] = src;  vis[src] = true;
    
        while (f < p)
        {
            int u = que[f++];
    
            for (int i = s[u]; i != 0; i = E[i].next)
            if  (E[i].res > 0 && !vis[E[i].v])
            {   int v = E[i].v;
    
                que[p++] = v;
                vis[v] = true;
                dist[v] = dist[u] + 1;
            }
        }
    
        return vis[snk];
    }

    int dfs(int u, int neck)
    {
        if  (u == snk || neck == 0)  return neck;
    
        int sol = 0;
        for (int& i = cur[u]; i != 0; i = E[i].next)
        if  (E[i].res > 0 && dist[E[i].v] == dist[u] + 1)
        {  
            int tmp = dfs(E[i].v, min(neck, E[i].res));
            E[i].res -= tmp;
            E[i ^ 1].res += tmp;
            neck -= tmp;
            sol += tmp;
    
            if  (neck == 0)  break;
        }
    
        return sol;
    }

    int max_flow()
    {
        int sol = 0;
        while (bfs())
        {
            memcpy(cur, s, sizeof(s));
            sol += dfs(src, Inf);
        }  
        return sol;
    }
};


const int N = 100;
int n, m;
int a[N+10], b[N+10], suma, sumb;
bool g[N+10][N+10];
int ans[N+10][N+10];

Dinic G;


void read()
{
    scanf("%d%d", &n, &m);
    suma = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), suma += a[i];
    sumb = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]), sumb += b[i];
    
    memset(g, 0, sizeof(g));
    int x, y;
    for (int i = 1; i <= m; i++)
    {   scanf("%d%d", &x, &y);
        g[x][y] = true;
        g[y][x] = true;
    }
}

void solve()
{
    if  (suma != sumb)  {  printf("NO\n");  return ;}

    G.init();
    G.n = 1 + n + n + 1;
    G.src = 1;  G.snk = 1 + n + n + 1;

    for (int i = 1; i <= n; i++)
        G.add_edge2(G.src, 1 + i, a[i]),
        G.add_edge2(1 + n + i, G.snk, b[i]);
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) 
            if  (i == j || g[i][j])
                G.add_edge2(1 + i, 1 + n + j, G.Inf);
    
    int flow = G.max_flow();

    if  (flow != sumb)  {  printf("NO\n");  return ;}
    printf("YES\n");

    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= n; i++)
        for (int j = G.s[1 + i]; j != 0; j = G.E[j].next)
        {   int v = G.E[j].v - n - 1;
            if  (v >= 1 && v <= n)
                ans[i][v] = G.E[j].cap - G.E[j].res;
        }
    
    for (int i = 1; i <= n; i++)
    {   for (int j = 1; j <= n; j++)
            printf("%d ", ans[i][j]);
        printf("\n");
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    read();

    solve();

    return 0;
}