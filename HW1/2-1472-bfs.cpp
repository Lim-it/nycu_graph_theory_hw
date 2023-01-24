#include  <bits/stdc++.h>
using namespace std;
#define forn(i,n) for(int i = 0; i < n; i++)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, k, t;
    cin >> n >> m >> k >> t;
    int infected = 0;

    vector<vector<int>> adj(n, vector<int>());
    vector<int> visited(n, 0);
    queue<int> toinfect;
    int toinfect_size = 0;
    forn(i, m){
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }

    int tmp;
    forn(i, k){
        cin >> tmp;
        tmp--;
        visited[tmp] = 1;
        toinfect.push(tmp);
        infected++;
        toinfect_size++;
    }

    forn(i, t - 1){
        int s = toinfect_size;
        toinfect_size = 0;
        if(s == 0) break;
        forn(j, s){
            int f = toinfect.front();
            for(auto it : adj[f]){
                if(visited[it] == 0){
                    toinfect.push(it);
                    visited[it] = 1;
                    infected++;
                    toinfect_size++;
                }
            }
            toinfect.pop();
        }
    }
    cout << infected;
    return 0;
}
