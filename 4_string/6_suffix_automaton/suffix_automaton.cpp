// CF666E
// 后缀自动机， 倍增法， 可持久化线段树
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;


class SAM
{public:
    static const int N = 1300000;
    int son[N+10][27], par[N+10], len[N+10];
    int size, root, last;
    
    void init()
    {
        memset(son, 0, sizeof(son));
        memset(par, 0, sizeof(par));
        memset(len, 0, sizeof(len));
        size = 1;  root = 1;  last = 1;
    }
    
    void extend(int c)
    {
        int np = ++size, p = last;
        len[np] = len[p] + 1;
        
        while (p && !son[p][c])  son[p][c] = np, p = par[p];
        if  (!p)  par[np] = root;
        else 
        {   
            int q = son[p][c];
            if  (len[q] == len[p] + 1)  par[np] = q;
            else 
            {   
                int nq = ++size;
                memcpy(son[nq], son[q], sizeof(son[nq]));
                len[nq] = len[p] + 1;  par[nq] = par[q];
                while (p && son[p][c] == q)  son[p][c] = nq, p = par[p];
                par[q] = par[np] = nq;
            }
        }
        last = np;
    }
    
    int st[N+10], id[N+10];
    
    void toposort()
    {
        for (int i = 0; i <= size; i++)  st[i] = 0;
        for (int i = 1; i <= size; i++)  st[len[i]]++;
        for (int i = 1; i <= size; i++)  st[i] += st[i-1];
        for (int i = 1; i <= size; i++)  id[st[len[i]]--] = i;
    }
};

SAM sam;


struct Key
{   int val, id;
    Key(int val = 0, int id = 0) : val(val), id(id) {}
};

Key operator * (const Key& A, const Key& B)  {  return A.val == B.val? (A.id < B.id? A : B) : (A.val > B.val? A : B);}

Key operator + (const Key& A, const Key& B)  {  return Key(A.val + B.val, A.id);}

struct Node
{   Key key;
    int s1, s2;
};

class SegTree {
public:

    static const int S = SAM::N;

    Node T[S*23+10];
    int cnt, roots[S+10];

    SegTree() 
    {
        cnt = 0;
        memset(T, 0, sizeof(T));
        memset(roots, 0, sizeof(roots));
    }

    void Insert(int& x, int val, int l, int r)
    {
        if  (!x)  x = ++cnt;
        if  (l == r)  {  T[x].key.val++;  T[x].key.id = l;  return ;}
        int mid = (l + r) >> 1;
        if  (val <= mid)  Insert(T[x].s1, val, l, mid);
        else Insert(T[x].s2, val, mid+1, r);
        T[x].key = T[T[x].s1].key * T[T[x].s2].key;
    }

    int Merge(int x, int y, int l, int r)
    {
        if  (!x || !y)  return x | y;
        int z = ++cnt;
        if  (l == r)  {  T[z].key = T[x].key + T[y].key;  return z;}
        int mid = (l + r) >> 1;
        T[z].s1 = Merge(T[x].s1, T[y].s1, l, mid);
        T[z].s2 = Merge(T[x].s2, T[y].s2, mid + 1, r);
        T[z].key = T[T[z].s1].key * T[T[z].s2].key;
        return z;
    }

    Key Query(int x, int l, int r, int  L, int R)
    {
        if  (!x)  return Key(0, 0);
        if  (L <= l && R >= r)  return T[x].key;
        int mid = (l + r) >> 1;
        if  (R <= mid)  return Query(T[x].s1, l, mid, L, R);
        else if  (L > mid)  return Query(T[x].s2, mid + 1, r, L, R);
        else return Query(T[x].s1, l, mid, L, mid) * Query(T[x].s2, mid + 1, r, mid + 1, R);
    }
};

SegTree segtree;

class SAMFather {
public:

    SAM& sam;
    int father[SAM::N + 10][21];

    SAMFather(SAM& sam) : sam(sam) {}

    void build()
    {
        for (int i = 1; i <= sam.size; i++)
            father[i][0] = sam.par[i];
        for (int k = 1; k <= 20; k++)
            for (int i = 1; i <= sam.size; i++)
                father[i][k] = father[ father[i][k-1] ][k-1];
    }

    int get(int x, int len)
    {
        for (int i = 20; i >= 0; i--)
            if  (sam.len[ father[x][i] ] >= len)
                x = father[x][i];
        return x;
    }
};

SAMFather father(sam);


const int N = 500000;
int n, m, q;
char str1[N+10], str2[N+10];
int pos[N+10];


int main()
{

    sam.init();

    scanf("%s", str1+1);  n = strlen(str1+1);
    for (int i = 1; i <= n; i++)
        sam.extend(str1[i] - 'a'), pos[i] = sam.last;
    sam.extend(26);

    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {   scanf("%s", str2+1);  int l = strlen(str2+1);
        for (int j = 1; j <= l; j++)
            sam.extend(str2[j] - 'a'), segtree.Insert(segtree.roots[sam.last], i, 1, m);
        sam.extend(26);
    }
    
    sam.toposort();
    
    for (int i = sam.size; i >= 1; i--)
    {   int x = sam.id[i], p = sam.par[x];
        if  (p)  segtree.roots[p] = segtree.Merge(segtree.roots[p], segtree.roots[x], 1, m);
    }

    father.build();

    scanf("%d", &q);
    int l, r, pl, pr;
    for (int k = 1; k <= q; k++)
    {   scanf("%d%d%d%d", &l, &r, &pl, &pr);
        int x = father.get(pos[pr], pr - pl + 1);
        Key ans = segtree.Query(segtree.roots[x], 1, m, l, r);
        if  (!ans.val)  printf("%d %d\n", l, 0);
        else printf("%d %d\n", ans.id, ans.val);
    }

    return 0;
}
