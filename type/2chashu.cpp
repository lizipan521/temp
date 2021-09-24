#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct node 
{
    node *l, *r;
    int data;
};
int ans[N], k = 0;
node *creat(int x) 
{
    node *root;
    root = new node;
    root->data = x;
    if (x == 20) 
    {
        root->l = NULL;
        root->r = NULL;
    } 
    else 
    {
        root->l = creat(x + 1);
        root->r = creat(x + 1);
    }
    return root;
}
void zh(node *root) 
{
    if (k > N) return;
    if (root) 
    {
        zh(root->l);
        ans[k++] = root->data;
        zh(root->r);
    }
}
int main() 
{
    int n;
    node *root;
    root = creat(1);
    zh(root);
    cin >> n;
    for (int i = 0; i < n; i++) 
    {
        if (i == n - 1)
            cout << ans[i] << '\n';
        else
            cout << ans[i] << ' ';
    }
    system("pause");
    return 0;
}
