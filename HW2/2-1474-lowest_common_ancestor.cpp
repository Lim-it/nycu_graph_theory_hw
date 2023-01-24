#include <bits/stdc++.h>

using namespace std;

struct LCA {
    vector<int> height, euler, first, segtree;
    vector<bool> visit;
    int n;

    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visit.assign(n, false);
        dfs(adj, root);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    }

    void dfs(vector<vector<int>> &adj, int x, int h = 0) {
        visit[x] = true;
        height[x] = h;
        first[x] = euler.size();
        euler.push_back(x);
        for (int y : adj[x]) {
            if (!visit[y]) {
                dfs(adj, y, h + 1);
                euler.push_back(x);
            }
        }
    }

    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r; //faster than min
        }
    }

    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return segtree[node];
        int mid = (b + e) >> 1;

        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }

    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return query(1, 0, euler.size() - 1, left, right);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> adj(n, vector<int>());
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }

    LCA tree(adj);

    int q;
    cin >> q;
    while(q--){
        int a, b;
        cin >> a >> b;
        a--; b--;
        int c = tree.lca(a, b);
        cout << tree.height[a] + tree.height[b] - 2 * tree.height[c] << "\n";
    }

    //test
    /*for(auto i : tree.euler) cout << i << " ";
    cout << endl;
    for(auto i : tree.segtree) cout << i << " ";*/

    return 0;
}
