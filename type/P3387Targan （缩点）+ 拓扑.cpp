#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 1e4 + 5;
const int maxm = 1e5 + 5;
int n, m, cnt = 0, ft[maxm<<1], to[maxm<<1], nx[maxm <<1], dfn[maxm], low[maxm], vis[maxn];
int stack_[maxm], visit[maxn], dis[maxn], dis_[maxn], ans[maxn], rd[maxn], dp[maxn];
int times = 0, path = 0, index_ = 0, tot = 0;
std::vector<int>vf[maxn], vt[maxn];
std::queue<int>q;
void add(int x, int y){
    nx[++cnt] = ft[x];
    ft[x] = cnt;
    to[cnt] = y;
}
void targan(int x){
    low[x] = dfn[x] = ++times;//记录时间
    stack_[++index_] = x;//入栈
    visit[x] = 1;
    for (int i = ft[x]; i; i = nx[i]){
        if (!dfn[to[i]]){
            targan(to[i]);
            low[x] =std::min(low[x], low[to[i]]);
        }
        else{
            if (visit[to[i]]) low[x] = std::min(low[x], low[to[i]]);
        }
    }
    if (dfn[x] == low[x]){
        tot++;//强连通分量的编号
        while(1){
            vis[stack_[index_]] = tot;
            dis_[tot] += dis[stack_[index_]];//缩点后的权值
            visit[stack_[index_]] = 0; index_--;
            if (x == stack_[index_ + 1]) break;
        }
    }
}
void topu(){
    for (int i = 1; i <= tot; i++){
        if(rd[i] == 0) q.push(i);
    }
    int cnt_ = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        ans[++cnt_] = u;
        for (int i = 0; i < vt[u].size(); i++){
            rd[vt[u][i]]--;
            if (rd[vt[u][i]] == 0) q.push(vt[u][i]);
        }
    }
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
    for (int i = 1; i <= n; i++) scanf("%d", &dis[i]);
    int x,y;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        add(x, y);
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) targan(i);
    for (int i = 1; i <= n; i++){//拓扑建边
        for (int j = ft[i]; j; j = nx[j]){
            if (vis[i] != vis[to[j]]){
                x = vis[i];
                y = vis[to[j]];
                rd[y]++;
                vt[x].push_back(y);
                vf[y].push_back(x);
            }
        }
    }
    topu();
    for (int i = 1; i <= tot; i++){
        int u = ans[i];
        dp[u] = dis_[u];
        for (int j = 0; j < vf[u].size(); j++){
            dp[u] = std::max(dp[u], dp[vf[u][j]] + dis_[u]);
        }
    }
    int Max = 0;
    for (int i = 1; i <= tot; i++) Max = std::max(Max, dp[i]);
    printf("%d", Max);
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