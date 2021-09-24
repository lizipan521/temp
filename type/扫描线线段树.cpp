#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 200010;
struct seg{
    int l, r, h, d;
}s[maxn];

bool cmp (struct seg x, struct seg y){
    return x.h < y.h;
}
struct Node{
    int l, r, cover;
    ll len;
}sgt[maxn<<3];
inline int ls(int x) {return x<<1;}
inline int rs(int x) {return x<<1|1;}
inline void pushup(int k){
    if (sgt[k].cover) sgt[k].len = sgt[k].r -sgt[k].l;
    else sgt[k].len = sgt[ls(k)].len + sgt[rs(k)].len;
}
int Hash[maxn]; 

void modify(int l, int r, int d, int k = 1){
    int x = sgt[k].l , y = sgt[k].r;
    if (l <= x && r >= y){
        sgt[k].cover += d;
        pushup(k);
        return ;
    }
    if (l < sgt[ls(k)].r) modify(l, r, d, ls(k));
    if (r > sgt[rs(k)].l) modify(l, r, d, rs(k));
    pushup(k);
}

void build(int l, int r, int k = 1){
    sgt[k].l = Hash[l], sgt[k].r = Hash[r];
    if (r - l <= 1) return;
    int m = (l + r)>>1;
    build(l, m, ls(k));
    build(m, r, rs(k));
}



int main(){
    int n, x1, x2, y1, y2, i, k;
    scanf("%d", &n);
    k = 0;
    for (i = 0; i < n; i++){
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        Hash[++k] = x1;
        s[k] = {x1, x2, y2, 1};
        Hash[++k] = x2;
        s[k] = {x1, x2, y1, -1};
    }
    sort (s + 1, s + k + 1, cmp);
    sort (Hash + 1, Hash + k + 1);
    int m = unique(Hash + 1, Hash + k + 1) - Hash - 1;
    ll ans = 0;
    build(1, m);
    for (i = 1; i <= k; i++){
        modify(s[i].l, s[i].r, s[i].d);
        ans += sgt[1].len * (s[i + 1].h - s[i].h);
        
    }
    printf("%lld", ans);

    system("pause");
    return 0;
}