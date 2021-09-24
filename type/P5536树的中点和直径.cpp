#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 1e5 + 10;
int ft[maxn<<1], nx[maxn<<1], to[maxn<<1], fa[maxn], dep[maxn], dis[maxn], maxdep[maxn];
int cnt = 0, n, k;
void add(int x, int y){
    nx[++cnt] = ft[x];
    ft[x] = cnt;
    to[cnt] = y;
}
int num, max = 0;
void dfs(int x, int d){
    dep[x] = d;
    maxdep[x] = d;
    if (d > max){
        max = d;
        num = x;
    }
    for (int i = ft[x]; i; i = nx[i]){
        if (to[i] != fa[x]){
            fa[to[i]] = x;
            dfs(to[i], d + 1);
            maxdep[x] = std::max(maxdep[x], maxdep[to[i]]);
        }
    }
}

bool cmp (int x, int y){
    return  x > y;
}

int main(int argc, char const *argv[])
{
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    clock_t c1 = clock();
    //======================================
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    memset(fa, 0, sizeof(fa));
    memset(dep, 0, sizeof(dep));
    max = 0;
    dfs(num, 0);
    int mid = num;
    for (int i = 0; i < (dep[num] + 1)>>1; i++){
        mid = fa[mid];
    }
    memset(dep, 0, sizeof(dep));
    memset(fa, 0, sizeof(fa));
    memset(maxdep, 0, sizeof(maxdep));
    max = 0;
    dfs(mid, 0);
    for (int i = 1; i <= n; i++){
        dis[i] = maxdep[i] - dep[i];
        //printf("%d %d\n", i, dep[i]);
    }

    std::sort(dis + 1, dis + 1 + n, cmp);
    //for (int i = 1; i <= n; i++) printf("%d\n", dis[i]);
    printf("%d", dis[k + 1] + 1);
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