#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
// using namespace std;
// typedef long long ll;


void quick_sort(int a[], int l, int r)
{
    int mid = (l + r) / 2;
    int mid_val = a[mid];

    int i = l, j = r;

    while (i < j)
    {
        while (a[i] < mid_val) i++;
        while (a[j] > mid_val) j--;

        if  (i <= j)
        {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;

            i++;
            j--;
        }
    }

    if  (l < j)  quick_sort(a, l, j);
    if  (i < r)  quick_sort(a, i, r);
}



const int N = 100000;
int n;
int a[N + 10];


int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");


    quick_sort(a, 1, n);

    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    
    return 0;
}
