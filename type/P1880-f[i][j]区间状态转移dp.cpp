#include<bits/stdc++.h>
typedef long long ll;
//======================================
const int maxn = 300;
int f[maxn][maxn], a[maxn], n,  sum[maxn], f1[maxn][maxn];
int main(int argc, char const *argv[])
{
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    //clock_t c1 = clock();
    //======================================
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {scanf("%d", &a[i]);  sum[i] += sum[i - 1] + a[i];}
    for (int i = 1; i <= n; i++)sum[i + n] = sum [i + n - 1] + a[i];
    for (int len = 1; len < n<<1; len++){
        for (int i = 1; i + len <= n<<1; i++){
            int j = i + len;
            f[i][j] =  f[i + 1][j] + sum[j] - sum[i - 1];
            f1[i][j] =  f1[i + 1][j] + sum[j] - sum[i - 1];
            for (int k = i + 1; k < j; k++){
                f[i][j] = std::max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
                f1[i][j] = std::min(f1[i][j], f1[i][k] + f1[k + 1][j] + sum[j] - sum[i - 1]);
            }
            //printf("%d %d %d\n",i, j, f1[i][j]);
        }
    }
    int Max , Min = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++){
        Max = std::max(Max, f[i][i + n - 1]);
        Min = std::min(Min, f1[i][i + n - 1]);
    }
    printf("%d\n%d", Min, Max);
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