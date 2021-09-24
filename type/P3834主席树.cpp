#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 2e5 + 10;
struct Node{
    int l, r, sum;
}zxs[maxn * 40];
int n, m, a[maxn], cnt, root[maxn];
std::vector<int>v;
inline int getid(int x){
    return std::lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}
void insert(int l, int r, int pre, int &now, int x){
    zxs[++cnt] = zxs[pre];
    now = cnt;
    zxs[now].sum++;
    if (l == r) return ;
    int mid =( l + r) >> 1;
    if (x <= mid) insert(l, mid, zxs[pre].l, zxs[now].l, x);
    else insert(mid + 1, r, zxs[pre].r, zxs[now].r, x);
}
int query(int l, int r, int L, int R, int k){
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int tmp = zxs[zxs[R].l].sum - zxs[zxs[L].l].sum;
    if (k <= tmp) return query(l, mid, zxs[L].l, zxs[R].l, k);
    else return query(mid + 1, r, zxs[L].r, zxs[R].r, k - tmp); 
}
int main(int argc, char const *argv[])
{
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    //clock_t c1 = clock();
    //======================================
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        v.push_back(a[i]);
    }
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    //printf("%d\n", v.size());
    for (int i = 1; i <= n; i++){
        //printf("%d\n", getid(a[i]));
        insert(1, n, root[i - 1], root[i], getid(a[i]));
    }
    int l, r, k;
    while(m--){
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", v[query(1, n, root[l - 1], root[r], k) - 1]);
    }
    //======================================
    //std::cerr << "Time:" << clock() - c1 << "ms" << std::endl;
    return 0;
}
/*
 * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
 * │Esc│   │ F1│ F2│ F3│ F4│ │ F5│ F6│ F7│ F8│ │ F9│F10│F11│F12│ │P/S│S L│P/B│  ┌┐    ┌┐    ┌┐
 * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘  └┘    └┘    └┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
 * │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BacSp │ │Ins│Hom│PUp│ │Num│ / │ * │ - │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ | \ │ │Del│End│PDn│ │ 7 │ 8 │ 9 │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │
 * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  │               │ 4 │ 5 │ 6 │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤
 * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│  Shift   │     │ ↑ │     │ 1 │ 2 │ 3 │   │
 * ├─────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤ E││
 * │ Ctrl│ Win│ Alt│         Space         │ Alt│ Win│Menu│Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │←─┘│
 * └─────┴────┴────┴───────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
 */