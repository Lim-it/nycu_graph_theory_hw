#include <iostream>
#include <ios>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<long, int> pli;
typedef long long ll;

vector<vector<pii>> adj;

void dj(int n, int s, vector<ll>& dis){
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dis.assign(n, 1e18);
    vector<bool> visit(n, false);
    dis[s] = 0;
    pq.push({0, s});
    while(!pq.empty()){
        ll wk = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(visit[u]) continue;
        visit[u] = true;

        for(auto [v, w] : adj[u]){
            if(wk + w < dis[v]){
                dis[v] = wk + w;
                pq.push({w, v});
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, p, q, t, tot;
    cin >> n >> m >> p >> q >> t >> tot;

    adj.assign(n + 2, vector<pii>());

    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    for(int i = 0; i < p; i++){
        int vs;
        cin >> vs;
        adj[0].push_back({vs, 0});
    }
    for(int i = 0; i < q; i++){
        int anti;
        cin >> anti;
        adj[n + 1].push_back({anti, 0});
    }

    vector<ll> virus_spread;
    vector<ll> anti_virus;

    dj(n + 2, 0, virus_spread);
    dj(n + 2, n + 1, anti_virus);

    for(auto &i : anti_virus) i+= t;
    int res = 0;
    for(int i = 1; i <= n; i++){
        if(virus_spread[i] <= tot || anti_virus[i] <= tot){
            if(virus_spread[i] < anti_virus[i]) res++;
        }
    }
    cout << res;
    return 0;
}
