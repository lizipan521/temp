#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 10;
int a[maxn], b[maxn];
ll ans = 0;
void msort(int l, int r){
    
    if (r - l <= 1) return ;
    
    //int mid = l + (r - l) / 2;
    int mid = l + r >>1;
    msort(l, mid);
    msort(mid, r);
    //mid += 1;
    int x = l, y = mid, k = 0;

    while(x < mid || y < r){
        if (x >= mid || (y < r && a[x] > a[y])) {
            b[k++] = a[y++];
            ans += mid - x;
        }
        else b[k++] = a[x++];
    }
    for (int i = 0; i < k; i++)
        a[l + i] = b[i];
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    msort(0, n);
    //for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("%lld", ans);
    system("pause");
} // namespace std;
