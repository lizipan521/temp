#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 1e5 + 10;
struct L{
    int l, r, size, fact, exit, val;
}tzy[maxn];
int cnt = 0, root = 0;
std::vector<int>v;
void newnode(int &now, int val){
    now = ++cnt;
    tzy[now].val = val;
    tzy[now].exit = 1;
    tzy[now].fact = tzy[now].size = 1;
    tzy[now].l = tzy[now].r = 0;
}

bool imbalence(int now){
    if (std::max(tzy[tzy[now].l].size, tzy[tzy[now].r].size) > tzy[now].size * 0.75 ||
        (tzy[now].size - tzy[now].fact) > tzy[now].size * 0.3) return true;
    return false;
}
void lmr(int now){
    if(!now) return;
    lmr(tzy[now].l);
    if (tzy[now].exit)
        v.push_back(now);
    lmr(tzy[now].r);
}
void lift(int l, int r, int &now){
    if(l == r){
        now = v[l];
        tzy[now].fact = tzy[now].size = 1;
        tzy[now].l = tzy[now].r = 0;
        return;
    }
    int m = l + r >>1;
    while(m && l < m&& tzy[v[m]].val == tzy[v[m -1]].val) m--;
    now = v[m];
    if (l < m) lift(l, m -1, tzy[now].l);
    else tzy[now].l = 0;
    lift(m + 1, r, tzy[now].r);
    tzy[now].fact = tzy[tzy[now].l].fact + tzy[tzy[now].r].fact + tzy[now].exit;
    tzy[now].size = tzy[tzy[now].l].size + tzy[tzy[now].r].size + 1;
    
}
void rebuild(int &now){
    v.clear();
    lmr(now);
    if (v.empty()){
        now = 0;
        return;
    }
    lift(0, v.size() - 1, now);
}
void update(int now, int end){
    if (!now || now == end) return;
    if (tzy[end].val < tzy[now].val) update(tzy[now].l, end);
    else update(tzy[now].r, end);
    tzy[now].size = tzy[tzy[now].l].size + tzy[tzy[now].r].size + 1;
}
void check(int &now, int end){
    if (!now) return;
    if (imbalence(now)){
        rebuild(now);
        update(root, now);
    }
    if(tzy[end].val < tzy[now].val) check(tzy[now].l, end);
    else check(tzy[now].r, end);
}
void add(int &now, int val){
    if(!now){
        newnode(now, val);
        check(root, now);
        return;
    }
    tzy[now].fact++;
    tzy[now].size++;
    if (val < tzy[now].val){
        add(tzy[now].l, val);
    }
    else add(tzy[now].r, val);
}
void del(int now, int val){
    if(val == tzy[now].val && tzy[now].exit){
        tzy[now].exit = 0;
        tzy[now].fact--;
        check(root, now);
        return;
    }
    tzy[now].fact--;
    if (val < tzy[now].val) del(tzy[now].l, val);
    else del(tzy[now].r, val);

}
int getrank(int val){
    int now = root, rank = 1;
    while(now){
        if (val <= tzy[now].val) now = tzy[now].l;
        else{
            rank += tzy[tzy[now].l].fact + tzy[now].exit;
            now = tzy[now].r;
        }
    }
    return rank;
}
int getnum(int rank){
    int now = root;
    while(now){
        if(tzy[tzy[now].l].fact + tzy[now].exit == rank && tzy[now].exit) break;
        else if (tzy[tzy[now].l].fact >= rank) now = tzy[now].l;
        else{
            rank -= tzy[now].exit + tzy[tzy[now].l].fact;
            now = tzy[now].r;
        }
    }
    return tzy[now].val;
}
int main(int argc, char const *argv[])
{
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    //======================================
    int t, p, x;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d", &p, &x);
        switch(p){
            case 1: add(root, x); break;
            case 2: del(root, x); break;
            case 3: printf("%d\n", getrank(x)); break;
            case 4: printf("%d\n", getnum(x)); break;
            case 5: printf("%d\n", getnum(getrank(x) - 1) ); break;
            case 6: printf("%d\n", getnum(getrank(x + 1))); break;
        }
    }
    //======================================
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