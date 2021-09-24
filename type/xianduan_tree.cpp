#include<stdio.h>
#include<stdlib.h>

void creat_tree(int arr[], int tree[], int node, int start, int end) {

    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    int left_node = 2 * node + 1;
    int right_node = 2 * node + 2;
    creat_tree(arr, tree, left_node, start, mid);
    creat_tree(arr, tree, right_node, mid + 1, end);
    tree[node] = tree[left_node] + tree[right_node];
}

void update(int arr[], int tree[], int node, int start, int end, int key, int value) {
    if (start == end && start == key) {
        tree[node] = value;
        return;
    }
    int mid = (start + end) / 2;
    int lift_node = 2 * node + 1;
    int right_node = 2 * node + 2;
    if (key <= mid) {
        update(arr, tree, lift_node, start, mid, key, value);
    }
    else update(arr, tree, right_node, mid + 1, end, key, value);
    tree[node] = tree[lift_node] + tree[right_node];
}

int query_tree(int arr[], int tree[], int node, int start, int end, int L, int R) {
    if (L > end || R < start) return 0;
    if (L  <= start && R >= end) return tree[node];
    int mid = (start + end) / 2;
    int lift_node = 2 * node + 1;
    int right_node = 2 * node + 2;
    query_tree(arr, tree, lift_node, start, mid, L, R);
    query_tree(arr, tree, right_node, mid + 1, end, L, R);
    return query_tree(arr, tree, lift_node, start, mid, L, R) + query_tree(arr, tree, right_node, mid + 1, end, L, R);
}
int main() {
    int arr[6] = { 1, 3, 5, 7, 9, 11 };
    int tree[20] = { 0 };
    creat_tree(arr, tree, 0, 0, 5);
    update(arr, tree, 0, 0, 5, 3, 6);
    for (int i = 0; i < 20; i++) {
        printf("tree[%d] = %d\n", i, tree[i]);
    }
    printf("\n\n%d\n",query_tree(arr, tree, 0, 0, 5, 0, 3));
    system("pause");
}