#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 1e4 + 10;
const int maxm = 5e4 + 10;
int n, m, nx[maxm<<1], to[maxm<<1], val[maxm<<1], fa[maxn], ft[maxm<<1], hv[maxn][32][2], f[maxn];
int cnt = 0, dep[maxn];
struct L{
    int x, y, w;
    bool operator<(const L &z)const {
        return w > z.w;
    }
}e[maxm];
int find(int x){
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}
void merge(int x, int y){
    f[find(x)] = find(y);
    f[find(y)] = find(x);
}
void add(int x, int y, int w){
    nx[++cnt] = ft[x];
    ft[x] =cnt;
    to[cnt] = y;
    val[cnt] = w;
}
void lift(){
    int num = 0;
    for (int i = 0; i < m; i++){
        if (num == n - 1) return;
        if (find(e[i].x) != find(e[i].y)){
            merge(e[i].x, e[i].y);
            cnt++;
            add(e[i].x, e[i].y, e[i].w);
            add(e[i].y, e[i].x, e[i].w);
        }
    }
}

void dfs(int x, int d, int weight){
    dep[x] = d;
    hv[x][0][0] = fa[x];
    hv[x][0][1] =  weight;
    for (int i = 1; (1 << i) <= dep[x]; i++){
        hv[x][i][0] = hv[hv[x][i - 1][0]][i - 1][0];
        hv[x][i][1] = std::min(hv[x][i - 1][1], hv[hv[x][i - 1][0]][i - 1][1]);
    }
    for (int i = ft[x]; i; i = nx[i]){
        if (fa[x] != to[i]){
            fa[to[i]] = x;
            dfs(to[i], d + 1, val[i]);
        }
    }
}
int lca(int x, int y){
    if (find(x) != find(y)) return 0;
    int we = 0x3f3f3f3f;
    if (dep[x] > dep[y]) std::swap(x, y);
    for (int i = (int)log2(dep[y] - dep[x]); i >= 0; i--){
        if (hv[y][i][0] && dep[hv[y][i][0]] >= dep[x]){
            we = std::min(we, hv[y][i][1]);
            y = hv[y][i][0];
        }
    }
    if (x == y) return we;
    for (int i = log2(dep[x]); i >= 0; i--){
        if (hv[x][i][0] != hv[y][i][0]){
            we = std::min(we, hv[x][i][1]);
            we = std::min(we, hv[y][i][1]);
            x = hv[x][i][0];
            y = hv[y][i][0];
        }
    }
    we = std::min(we, hv[x][0][1]);
    we = std::min(we, hv[y][0][1]);
    return we;
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
    for (int i = 0; i < m; i++){
        scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
    }
    for (int i = 0; i <= n;i++) f[i] = i;
    std::sort(e, e + m);
    lift();
    dfs(1, 0, 0x3f3f3f3f);
    int q;
    scanf("%d", &q);
    int x, y;
    for (int i = 0; i < q; i++){
        scanf("%d%d", &x, &y);
        x = lca(x, y);
        if (x == 0) x = -1;
        printf("%d\n", x);
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