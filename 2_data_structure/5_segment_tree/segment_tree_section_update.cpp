// poj3468
// 线段树， 区间更新
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;


struct Node
{   int l, r, mid;
    int s1, s2;
    ll sum, add;
};


class SegTree {
public:

    static const int N = 100000;
    
    Node T[N * 2 + 100];
    int tot, root;

    void init()
    {
        tot = root = 1;
    }

    void pushup(int rt)
    {
        Node& f = T[rt];
        f.sum = T[f.s1].sum + T[f.s2].sum;
    }

    void operate(int rt, int c)
    {
        Node& f = T[rt];
        f.add += c;
        f.sum += (ll)(f.r - f.l + 1) * c;  //ll
    }

    void pushdown(int rt)
    {
        Node& f = T[rt];
        if  (f.add)
        {   operate(f.s1, f.add);
            operate(f.s2, f.add);
            f.add = 0;
        }
    }

    void build(int rt, int a[], int l, int r)
    {
        Node& f = T[rt];
        f.l = l;  f.r = r;  f.mid = (l + r) / 2;
        f.add = 0;

        if  (l == r)
            f.s1 = f.s2 = 0, f.sum = a[l];
        else
        {   f.s1 = ++tot;  build(f.s1, a, f.l, f.mid);
            f.s2 = ++tot;  build(f.s2, a, f.mid + 1, f.r);
            pushup(rt);
        }
    }

    void update(int rt, int l, int r, int c)
    {
        Node& f = T[rt];

        if  (l == f.l && r == f.r)
            operate(rt, c);
        else
        {   pushdown(rt);
            if  (r <= f.mid)  update(f.s1, l, r, c);
            else if  (l >= f.mid + 1)  update(f.s2, l, r, c);
            else {  update(f.s1, l, f.mid, c);  update(f.s2, f.mid + 1, r, c);}
            pushup(rt);
        }
    }

    ll query(int rt, int l, int r)
    {
        Node& f = T[rt];

        if  (l == f.l && r == f.r)
            return f.sum;
        else
        {   pushdown(rt);
            if  (r <= f.mid)  return query(f.s1, l, r);
            else if  (l >= f.mid + 1)  return query(f.s2, l, r);
            else return query(f.s1, l, f.mid) + query(f.s2, f.mid + 1, r);
        }
    }

};

SegTree segtree;

const int N = 100000;
int n, m;
int a[N + 10];
char str[5];

int main()
{
    while (scanf("%d%d", &n, &m) != EOF)
    {
        //printf("n:%d m:%d\n", n, m);

        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        /*for (int i = 1; i <= n; i++)
            printf("%d ", a[i]);
        printf("\n");*/
        
        segtree.init();
        segtree.build(segtree.root, a, 1, n);

        
        int x1, x2, x3;
        for (int i = 1; i <= m; i++)
        {
            scanf("%s", str);

            if  (str[0] == 'C')
            {   scanf("%d%d%d", &x1, &x2, &x3);
                //printf("C %d %d %d\n", x1, x2, x3);
                segtree.update(segtree.root, x1, x2, x3);
            }
            else if  (str[0] == 'Q')
            {   scanf("%d%d", &x1, &x2);
                //printf("Q %d %d\n", x1, x2);
                ll ans = segtree.query(segtree.root, x1, x2);
                printf("%lld\n", ans);
            }
        }
    }
    
    return 0;
}
