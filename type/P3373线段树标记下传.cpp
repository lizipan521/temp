#include<bits/stdc++.h>
typedef long long ll;
namespace FastIO
{
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
void read() {}
void print() {}
inline int getc()
{
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
}
inline void flush()
{
    fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
}
template <typename T, typename... T2>
inline void read(T &x, T2 &... oth)
{
    int f = 0;
    x = 0;
    char ch = getc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = 1;
        ch = getc();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - 48;
        ch = getc();
    }
    x = f ? -x : x;
    read(oth...);
}
template <typename T, typename... T2>
inline void print(T x, T2... oth)
{
    if (p3 > 1 << 20)
        flush();
    if (x < 0)
        buf2[++p3] = 45, x = -x;
    do
    {
        a[++p] = x % 10 + 48;
    } while (x /= 10);
    do
    {
        buf2[++p3] = a[p];
    } while (--p);
    buf2[++p3] = hh;
    print(oth...);
}
} // namespace FastIO
#define read FastIO::read
#define print FastIO::print
//======================================
const int maxn = 1e5 + 5;
struct L{
    int l, r;
    ll val, k1, k2;
}sgt[maxn<<2];
int n, m, p, a[maxn];
inline int ls(int k){return k<<1;}
inline int rs(int k){return k<<1|1;}
void pushup(int k){
    int l = ls(k), r = rs(k);
    if (sgt[k].k1 != 1|| sgt[k].k2 != 0){
        sgt[l].val = ((sgt[l].val * sgt[k].k1) + sgt[k].k2 * (sgt[l].r - sgt[l].l + 1))%p;
        sgt[r].val = ((sgt[r].val * sgt[k].k1) + sgt[k].k2 * (sgt[r].r - sgt[r].l + 1))%p;
        sgt[l].k2 = (sgt[l].k2 * sgt[k].k1 + sgt[k].k2)%p;
        sgt[r].k2 = (sgt[r].k2 * sgt[k].k1 + sgt[k].k2)%p;
        sgt[l].k1 = (sgt[l].k1 * sgt[k].k1)%p;
        sgt[r].k1 = (sgt[r].k1 * sgt[k].k1)%p; 
        sgt[k].k1 = 1;
        sgt[k].k2 = 0;
     }
}
void push(int k){
    sgt[k].val = sgt[ls(k)].val + sgt[rs(k)].val;
    sgt[k].val %= p;
}

void build(int l, int r, int k = 1){
    sgt[k].l = l, sgt[k].r = r, sgt[k].k1 = 1, sgt[k].k2 = 0;
    if (l == r){
        sgt[k].val = a[l];
        return;
    }
    int mid = l + r >>1;
    build(l, mid, ls(k));
    build(mid + 1, r, rs(k));
    push(k);
}
void update_1(int l, int r, int key, int k = 1){
    int x = sgt[k].l, y = sgt[k].r;
    if (l <= x && y <= r){
        sgt[k].val = (sgt[k].val * key) % p;
        sgt[k].k1 = (sgt[k].k1 * key) %p;
        sgt[k].k2 = (sgt[k].k2 * key) %p;
        return;
    }
    pushup(k);
    int mid = x + y >>1;
    if (l <= mid) update_1(l, r, key, ls(k));
    if(r > mid) update_1(l, r, key, rs(k));
    push(k);
}
void update_2(int l, int r, int key, int k = 1){
    int x = sgt[k].l, y = sgt[k].r;
    if (l <= x && y <= r){
        sgt[k].val = (sgt[k].val + key * (y - x + 1))%p;
        sgt[k].k2 = (sgt[k].k2 + key)%p;
        return;
    }
    pushup(k);
    int mid = x + y >>1;
    if (l <= mid) update_2(l, r, key, ls(k));
    if(r > mid) update_2(l, r, key, rs(k));
    push(k);
}
ll modify(int l, int r, int k = 1){
    int x = sgt[k].l, y = sgt[k].r;
    if (l <= x && r >= y){
        return sgt[k].val;
    }
    pushup(k);
    
    int mid = x + y >>1;
    ll a = 0, b = 0;
    if (l <= mid) a = modify(l, r, ls(k));
    if (r > mid) b = modify(l, r, rs(k));
    push(k);
    return (a + b)%p;
}
int main(int argc, char const *argv[])
{
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    clock_t c1 = clock();
    //======================================
    scanf("%lld%lld%lld", &n, &m, &p);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    memset(sgt, 0, sizeof(sgt));
    build(1, n);
    int k, x, y, t;
    while(m--){
        scanf("%d", &t);
        if(t == 1){
            scanf("%d%d%d", &x, &y, &k);
            update_1(x, y, k);
        }
        else if (t == 2){
            scanf("%d%d%d", &x, &y, &k);
            update_2(x, y, k);
        }
        else{
            scanf("%d%d", &x, &y);
            printf("%lld\n", modify(x, y)%p);
        }
        
    }
    //======================================
    FastIO::flush();
    std::cerr << "Time:" << clock() - c1 << "ms" << std::endl;
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