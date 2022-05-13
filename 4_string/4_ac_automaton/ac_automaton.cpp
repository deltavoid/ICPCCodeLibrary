// hdu2222
// AC automaton
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;


struct Trie
{
    int next[500010][26], fail[500010], end[500010];
    int root, cnt;

    int newNode()
    {
        ++cnt;
        for (int i = 0; i < 26; i++)
            next[cnt][i] = -1;
        end[cnt] = 0;
        return cnt;
    }
    void init()
    {
        cnt = 0;
        root = newNode();
    }
    void insert(char buf[])
    {
        int len = strlen(buf);
        int now = root, x = 0;

        for (int i = 0; i < len; i++)
        {   x = buf[i] - 'a';
            if  (next[now][x] == -1)
                next[now][x] = newNode();
            now = next[now][x];
        }
        end[now]++;
    }
    void build()
    {
        queue<int> Q;
        Q.push(root);
        fail[root] = root;
        
        while (!Q.empty())
        {
            int now = Q.front();
            Q.pop();
            for (int i = 0; i < 26; i++)
            {   if  (next[now][i] == -1)
                    next[now][i] = now == root? root : next[fail[now]][i];
                else
                {   fail[next[now][i]] = now == root? root : next[fail[now]][i];
                    Q.push(next[now][i]);
                }
            }
        }
    }
    int query(char buf[])
    {
        int len = strlen(buf);            
        int now = root;
        int res = 0;

        for (int i = 0; i < len; i++)
        {
            now = next[now][buf[i]-'a'];

            for (int j = now; j != root; j = fail[j])//有超时嫌疑
            {   res += end[j];
                end[j] = 0;
            }
        }
        return res;
    }
};

int times;
int n;
char buf[1000010];
Trie ac;

int main()
{
    //freopen("input.txt", "r", stdin);

    scanf("%d", &times);
    for (int T = 1; T <= times; T++)
    {
        scanf("%d", &n);
        ac.init();
        for (int i = 0; i < n; i++)
        {   scanf("%s", buf);
            ac.insert(buf);
        }

        ac.build();
        scanf("%s", buf);
        int sol = ac.query(buf);
        printf("%d\n", sol);
    }
    return 0;
}