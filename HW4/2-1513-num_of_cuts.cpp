#include <iostream>
#include <ios>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<long, int> pli;
typedef long long ll;

vector<vi> adj;

vector<bool> visit;
vi ent, low;
set<int> cut;
int t;

void dfs(int u, int par){
    visit[u] = true;
    ent[u] = t;
    low[u] = t;
    t++;
    int child = 0;
    for(auto v : adj[u]){
        if(v == par) continue;
        if(visit[v]) {
            low[u] = min(low[u], ent[v]);
        }
        else{
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= ent[u] && par !=-1)
                cut.insert(u);
            child++;
        }
    }
    if(par == -1 && child >= 2){
        cut.insert(u);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    adj.assign(n, vi());
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    t = 0;
    visit.assign(n, false);
    ent.assign(n, -1);
    low.assign(n, -1);
    for(int i = 0; i < n; i++) {
        if(!visit[i])
            dfs(i, -1);
    }

    cout << cut.size() << '\n';
    for(auto i : cut) cout << i + 1 << ' ';

    return 0;
}
