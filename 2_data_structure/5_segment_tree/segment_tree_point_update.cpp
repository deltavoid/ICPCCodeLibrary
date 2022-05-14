// hdu1166
// 线段树， 单点更新
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
    int val;
};

class SegTree {
public:

    static const int N = 50000;

    Node T[N * 2 + 100];
    int tot, root;


    void init()
    {
        root = tot = 1;
    }

    void build(int rt, int a[], int l, int r)
    {
        Node& f = T[rt];
        f.l = l;  f.r = r;  f.mid = (l + r) / 2;

        if  (l == r)
            f.s1 = f.s2 = 0, f.val = a[l];
        else
        {   f.s1 = ++tot;  build(f.s1, a, f.l, f.mid);
            f.s2 = ++tot;  build(f.s2, a, f.mid + 1, f.r);
            f.val = T[f.s1].val + T[f.s2].val; 
        }
    }

    void update(int rt, int x, int val)
    {
        Node& f = T[rt];

        if  (f.l == f.r)
            f.val += val;
        else
        {   if  (x <= f.mid)  update(f.s1, x, val);
            else update(f.s2, x, val);
            f.val = T[f.s1].val + T[f.s2].val;
        }
    }

    int getsum(int rt, int l, int r)
    {
        Node& f = T[rt];

        if  (l == f.l && r == f.r)  return f.val;
        else if  (r <= f.mid)  return getsum(f.s1, l, r);
        else if  (l >= f.mid + 1)  return getsum(f.s2, l, r);
        else return getsum(f.s1, l, f.mid) + getsum(f.s2, f.mid + 1, r);
    }

    void output_tree(int rt)
    {
        Node& f = T[rt];
        printf("l:%d r:%d mid:%d val:%d s1:%d s2:%d\n", f.l, f.r, f.mid, f.val, f.s1, f.s2);
        if  (f.s1 != 0)  output_tree(f.s1);
        if  (f.s2 != 0)  output_tree(f.s2);
    }
};

SegTree segtree;

const int N = 50000;
int n;
int a[N + 10];
char op[100];


int main()
{
    int times;  scanf("%d", &times);
    for (int T = 1; T <= times; T++)
    {
        memset(a, 0, sizeof(a));
        // tot = 0;

        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        // root = ++tot;
        segtree.init();
        segtree.build(segtree.root, a, 1, n);

        printf("Case %d:\n", T);
        while (scanf("%s", op) != EOF)
        {
            int x1, x2;
            if  (strcmp(op, "Add") == 0)
            {   scanf("%d%d", &x1, &x2);
                segtree.update(segtree.root, x1, x2);
            }
            else if  (strcmp(op, "Sub") == 0)
            {   scanf("%d%d", &x1, &x2);
                segtree.update(segtree.root, x1, -x2);
            }
            else if  (strcmp(op, "Query") == 0)
            {   scanf("%d%d", &x1, &x2);
                int ans = segtree.getsum(segtree.root, x1, x2);
                printf("%d\n", ans);
            }
            else if  (strcmp(op, "End") == 0)
                break;
        }
    }
    return 0;
}
