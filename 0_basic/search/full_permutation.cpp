#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath> 

const int N = 10;
int n;
int a[N + 10];
bool vis[N + 10];


void dfs(int k, int n, int a[], bool vis[])
{
    if  (k > n)
    {
        for (int i = 1; i <= n; i++)
            printf("%d ", a[i]);
        printf("\n");
    }
    else
    {
        for (int i = 1; i <= n; i++)
        if  (!vis[i])
        {   a[k] = i;
            vis[i] = true;
            dfs(k + 1, n, a, vis);
            vis[i] = false;
            a[k] = 0;
        }
    }
}

int main()
{
    scanf("%d", &n);

    dfs(1, n, a, vis);

    return 0;
}
