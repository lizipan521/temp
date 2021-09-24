#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 1e5 + 10;
int cow[maxn];
struct L{
    int next, to;
}edg[maxn<<1];
int cnt = 0, ft[maxn], n, m, dep[maxn], hv[maxn][30][3];//0跳到的节点， 1 是否含有h, 2是否含有v
int fa[maxn];
void add(int x, int y){
    edg[++cnt].next = ft[x];
    ft[x] = cnt;
    edg[cnt].to = y;
}
void dfs(int x, int d){
    dep[x] = d;
    hv[x][0][0] = fa[x];
    hv[x][0][1] = (cow[x] == 1 || cow[fa[x]] == 1);
    hv[x][0][2] = (cow[x] == 2|| cow[fa[x]] == 2);
    for (int i = 1; (1 << i) <= dep[x]; i++){
        hv[x][i][0] = hv[hv[x][i - 1][0]][i - 1][0];
        hv[x][i][1] = (hv[x][i - 1][1] || hv[hv[x][i - 1][0]][i - 1][1]);
        hv[x][i][2] = (hv[x][i - 1][2] || hv[hv[x][i - 1][0]][i - 1][2]);
    }
    for (int i = ft[x]; i; i = edg[i].next){
        if (fa[x] != edg[i].to){
            fa[edg[i].to] = x;
            dfs(edg[i].to, d + 1);
        }
    }
}
int jump(int x, int y, int w){
    if (dep[x] > dep[y]) std::swap(x, y);
    for (int i = (int) log2(dep[y] - dep[x]); i >= 0; i--){
        if (dep[hv[y][i][0]] >= dep[x]){
            if (hv[y][i][w]) return 1;
            y = hv[y][i][0];
        }
    }
    if (x == y){
        if (cow[x] == w) return 1;
        else return 0;
    }
    for (int i = (int)log2(dep[x]); i >= 0; i--){
        if ((1 << i) <= dep[x]){
            if (hv[x][i][0] != hv[y][i][0]){
                if (hv[x][i][w] || hv[y][i][w]) return 1;
                x = hv[x][i][0], y = hv[y][i][0];
            }
        }
    }
    if (hv[x][0][w] || hv[y][0][w]) return 1;
    else return 0;
}

int main(int argc, char const *argv[])
{
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    clock_t c1 = clock();
    //======================================
    scanf("%d%d", &n, &m);
    getchar();
    for (int i = 1; i <= n; i++){
        char ch;
        scanf("%c", &ch);
        if (ch == 'H'){
            cow[i] = 1;
        }
        else cow[i] = 2;
    }
    for (int i = 1; i < n; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);add(y, x);
    }
    dfs(1, 1);
    for (int i = 0; i < m; i++){
        int x,y, w;
        scanf("%d%d", &x, &y);
        getchar();
        char ch;
        scanf("%c", &ch);
        if (ch == 'H') w = 1;
        else w = 2;
        printf("%d", jump(x, y, w));
    }
    //======================================
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