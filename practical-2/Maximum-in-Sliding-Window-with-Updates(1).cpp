#include <iostream>
using namespace std;

const int MAXN = 100005;
int tree[4 * MAXN];

void build(int node, int start, int end, int arr[]) {
    if (start == end) { tree[node] = arr[start]; return; }
    int mid = (start + end) / 2;
    build(2*node, start, mid, arr);
    build(2*node+1, mid+1, end, arr);
    tree[node] = max(tree[2*node], tree[2*node+1]);
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) { tree[node] = val; return; }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2*node, start, mid, idx, val);
    else             update(2*node+1, mid+1, end, idx, val);
    tree[node] = max(tree[2*node], tree[2*node+1]);
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return INT_MIN;
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return max(query(2*node, start, mid, l, r),
               query(2*node+1, mid+1, end, l, r));
}

int main() {
    int n, k, q;
    cout << "Enter N (array size), K (window size), Q (queries): ";
    cin >> n >> k >> q;

    int arr[n + 1];
    cout << "Enter " << n << " integers: ";
    for (int i = 1; i <= n; i++) cin >> arr[i];

    build(1, 1, n, arr);

    cout << "\nProcess " << q << " queries:\n";
    cout << "  Type 1 pos val  →  update A[pos] = val\n";
    cout << "  Type 2 i        →  max of window ending at i (size K)\n\n";

    for (int i = 0; i < q; i++) {
        int type; cin >> type;
        if (type == 1) {
            int pos, val; cin >> pos >> val;
            arr[pos] = val;
            update(1, 1, n, pos, val);
        } else {
            int idx; cin >> idx;
            cout << query(1, 1, n, idx - k + 1, idx) << "\n";
        }
    }
    return 0;
}