#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;




// find kth largest value
// array from large to small
int find_kth_val(int a[], int l, int r, int k)
{
    if  (l == r)
    {
        return a[l];
    }


    int mid = (l + r) / 2;
    int mid_val = a[mid];

    int i = l, j = r;

    while (i < j)
    {
        while (a[i] > mid_val) i++;
        while (a[j] < mid_val) j--;

        if  (i <= j)
        {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;

            i++;
            j--;
        }
    }

    if  (k <= j)
        return find_kth_val(a, l, j, k);
    else if  (k >= i)
        return  find_kth_val(a, i, r, k);
    else
        return a[k];
}



const int N = 10000;
int n, k;
int a[N + 10];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");

    int val = find_kth_val(a, 1, n, k);

    printf("%d\n", val);

    return 0;
}
