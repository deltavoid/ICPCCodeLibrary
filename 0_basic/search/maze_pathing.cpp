#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<PII, int> Node;

const int N = 100;
const int INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int n;
char str[N + 10];
int a[N + 10][N + 10];
bool vis[N + 10][N + 10];

bool inside(int x, int y)
{
    return x >= 1 && x <= n && y >= 0 && y <= n;
}

int solve()
{
    bool flag = false;
    int ans = INF;
    PII src = PII(1, 1), dst = PII(n, n);
    queue<Node> Q;
    Q.push(Node(src, 0));

    while (!flag && !Q.empty())
    {
        Node now = Q.front();  
        Q.pop();

        for (int i = 0; i < 4; i++)
        {   int x = now.first.first + dx[i];
            int y = now.first.second + dy[i];

            if  (inside(x, y) && a[x][y] == 1 && !vis[x][y])
            {   
                if  (x == dst.first && y == dst.second)
                {   flag = true;
                    ans = now.second + 1;
                    break;
                }
                Q.push(Node(PII(x, y), now.second + 1));
            }
        }
    }

    return ans;
}


/* 
sample input
5
*.***
*.***
*.*.*
***.*
....*
*/

int main()
{
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++)
    {   scanf("%s", str);
        for (int j = 1; j <= n; j++)
            if  (str[j - 1] == '*')  a[i][j] = 1;
            else if  (str[j - 1] == '.')  a[i][j] = 0;
    }

    for (int i = 1; i <= n; i++)
    {   for (int j = 1; j <= n; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    int ans = solve();

    printf("%d\n", ans);

    return 0;
}
