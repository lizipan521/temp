#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
const double inf = 1e20;
struct point {
    double x, y;
    bool operator<(point z){
        if(x == z.x) return y < z.y;
        else return x < z.x;
    }
}p[maxn];
int temp[maxn];
int cmp(const int &a, const int &b){
    return p[a].y < p[b].y;
}
double distance(int x, int y){
    return sqrt((p[x].x - p[y].x) * (p[x].x - p[y].x) + (p[x].y - p[y].y) * (p[x].y - p[y].y));
}
double merge(int l, int r){
    double dis = inf;
  
    if (l == r)   {
        return dis;
    }
    if (l + 1 == r)  {
        return distance(l, r);
    }

    int mid = (l + r)>>1;
    double d1 = merge(l, mid);
    double d2 = merge(mid + 1, r);
    if (d1 > d2) dis = d2;
    else dis = d1;
    int k = 0;
    for (int i = l; i <= r; i++){
        if (fabs(p[i].x - p[mid].x) <= dis)
            temp[k++] = i;
    }
    
    sort(temp, temp + k, cmp);
    for (int i = 0; i < k; i++){
        for (int j = i + 1; j < k && fabs(p[temp[i]].y - p[temp[j]].y) <= dis; j++){
            dis = min(dis, distance(temp[i], temp[j]));
        }
    }
    
    return dis;
}
int main(){
    //freopen("input.in", "r", stdin);
    //freopen("output.out","w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf %lf", &p[i].x, &p[i].y);
    sort(p, p + n);
    
    printf("%.4lf", merge(0, n - 1));
    //system("pause");
    return 0;
}
/*
2
22990 6691
37281 24938
*/