#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 2e4 + 5;
const int maxm = 1e5 + 5;
int n, m, ft[maxn], nx[maxm<<1], to[maxm<<1], dfn[maxn], low[maxn], cnt, times, cut[maxn],ans;
bool vis[maxn];
void add(int x, int y){
    nx[++cnt] = ft[x];
    ft[x] = cnt;
    to[cnt] = y;
} 
void tarjan(int x, int fa){
    //printf("%d\n", x);
    dfn[x] = low[x] = ++times;
    vis[x] = true;
    int child = 0;
    for (int i = ft[x]; i; i = nx[i]){
        int v = to[i];
        if (!dfn[v]){
            tarjan(v, fa);
            low[x] = std::min(low[x], low[v]);
            if (dfn[x] <= low[v] && x != fa){//自己这个点不是根节点
                cut[x] = 1;
            }
            if (x == fa) child++; //是根节点
        }
        else low[x] = std::min(low[x], dfn[v]);
    }
    if(x == fa && child >= 2) {cut[x] = 1;}
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
    int x, y;
    for (int i = 0; i < m; i++){
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    for (int i = 1; i <= n; i++){
        if (!dfn[i]) tarjan(i, i);
    }
    for(int i = 1; i <= n;i++) if (cut[i]) ans++;
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) if (cut[i]) printf("%d ", i);
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