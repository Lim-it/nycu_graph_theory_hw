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

struct Edge{
    int v, u;
    int cap, flow;
    Edge(int u, int v, int cap, int flow):u(u), v(v), cap(cap), flow(flow){}
};

class Dinic{
public:
    const int inf = 2e9;
    vector<Edge> e;
    vector<vi> adj;
    int n, m = 0;
    int s, t;
    vi level, ptr;
    queue<int> q;
    Dinic(int, int, int);
    void add_edge(int, int, int);
    bool bfs();
    int dfs(int, int);
    int flow();
};

Dinic::Dinic(int n, int s, int t): n(n), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
}

void Dinic::add_edge(int u, int v, int cap){
    e.emplace_back(u, v, cap, 0);
    e.emplace_back(v, u, cap, 0);
    adj[u].push_back(m);
    adj[v].push_back(m + 1);
    m += 2;
}

bool Dinic::bfs(){ //build level
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i : adj[u]){
            if(e[i].cap - e[i].flow <= 0) continue;
            if(level[e[i].v] != -1) continue;
            level[e[i].v] = level[u] + 1;
            q.push(e[i].v);
        }
    }
    return level[t] != -1; //check
}

int Dinic::dfs(int u, int pushed){
    if(pushed == 0) return 0;
    if(u == t) return pushed; //reach end
    for(int& x = ptr[u]; x < (int)adj[u].size(); x++){
        int i = adj[u][x];
        int v = e[i].v;
        if(level[u] + 1 != level[v] || e[i].cap - e[i].flow < 1) continue;
        int res = dfs(v, min(pushed, e[i].cap - e[i].flow));
        if(res == 0) continue;
        e[i].flow += res;
        e[i ^ 1].flow -= res;
        return res;
    }
    return 0;
}

int Dinic::flow(){
    int f = 0;
    while(1){
        fill(level.begin(), level.end(), -1);
        fill(ptr.begin(), ptr.end(), 0);
        level[s] = 0;
        q.push(s);
        if(!bfs()) break;
        while(int push = dfs(s, inf)){
            f += push;
        }
    }
    return f;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    Dinic d(n + m + 3, 0, n + m + 2);
    d.add_edge(0, n + m + 1, k);
    for(int i = 1; i <= n; i++){
        d.add_edge(0, i, 1);
        d.add_edge(n + m + 1, i ,1);
        int h;
        cin >> h;
        for(int j = 0; j < h; j++){
            int to; cin >> to;
            d.add_edge(i, n + to, 1);
        }
    }
    for(int i = 1; i <= m; i++){
        d.add_edge(n + i, n + m + 2, 1);
    }

    cout << d.flow();

    return 0;
}
