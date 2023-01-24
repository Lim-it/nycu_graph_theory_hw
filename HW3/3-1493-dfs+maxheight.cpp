//run dfs to find max height between next nodes 

#include <queue>
#include <iostream>
#include <ios>
#include <stack>

using namespace std;

vector<int> h;
vector<vector<int>> adj;

int dfs(int s){
    if(adj[s].empty()) return 0;
    int maxh = -1;
    for(auto i : adj[s]) {
        maxh = max(maxh, 1 + dfs(i));
    }
    h[s] = maxh;
    return maxh;
}

int main()
{
    int n;
    cin >> n;

    adj.assign(n, vector<int>());
    vector<int> parent(n, 0);
    vector<bool> visit(n, false);
    h.assign(n, 0);
    parent[0] = -2;
    visit[0] = true;
    for(int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        x--; y--;
        if(visit[y]) swap(x, y);
        parent[y] = x;
        adj[x].push_back(y);
        visit[y] = true;
    }

    dfs(0);

    for(int i = 0; i < n; i ++){
        cout << h[i] << ' ' << parent[i] + 1 << '\n';
    }

    return 0;
}
