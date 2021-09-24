#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 1e5 + 10;
struct L{
    double x, y;
    bool operator <(const L &z)const{
        if (x == z.x) return y > z.y;
        return x < z.x;
    }
}poww[maxn];
int n, sta[maxn];
double Cross(L a, L b, L c){//做叉积
    double x1 = b.x - a.x;
    double y1 = b.y - a.y;
    double x2 = c.x - a.x;
    double y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}
double len(int x, int y){
    return sqrt((poww[x].x - poww[y].x) * (poww[x].x - poww[y].x) + (poww[x].y - poww[y].y) * (poww[x].y - poww[y].y));
}
void work(){
    std::sort(poww, poww + n);
    int top = 0;
    sta[++top] = 0;
    sta[++top] = 1;
    for (int i = 2; i < n; i++){
        while(top >= 2 &&Cross(poww[sta[top - 1]], poww[sta[top]], poww[i]) >= 0) top--;
        sta[++top] = i;
    }
    double ans = 0;
    for (int i = 1; i < top; i++){
        ans += len(sta[i], sta[i + 1]);
        //printf("%lf, %lf\n", poww[sta[i]].x, poww[sta[i]].y);
    }
    top = 0;
    sta[++top] = n - 1;
    sta[++top] = n - 2;
    for (int i = n - 3; i >= 0; i--){
        while(top >= 2 && Cross(poww[sta[top - 1]], poww[sta[top]], poww[i]) >= 0) top--;
        sta[++top] = i;
    }
    for (int i = 1; i < top; i++){
        ans += len(sta[i], sta[i + 1]);
        //printf("%lf, %lf\n", poww[sta[i]].x, poww[sta[i]].y);
    }
    printf("%.2lf", ans);
}

int main(int argc, char const *argv[])
{
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    //clock_t c1 = clock();
    //======================================
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%lf%lf", &poww[i].x, &poww[i].y);
    }    
    work();
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