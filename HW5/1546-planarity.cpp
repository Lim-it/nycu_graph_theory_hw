#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vii;
typedef pair<int, int> pii;
typedef set<int> si;
typedef map<int,int> mi;

int MAXN = 15;
int MAXDEPTH = 10;

struct Graph {
    int n, m;
    vii adj;
    vi deg, vertex_list;
    Graph(int n, int m);
    void add_edge(int u, int v);
    int contracted_v(int v);
    Graph subdivision(int u, int v, int w);
    void fixsize();
    bool isK33();
    bool isK5();
    bool isPlanar(int);
};

Graph::Graph(int n, int m):n(n), m(m){
    adj.assign(15, vi(15,0));
    deg.assign(MAXN, 0);
}

void Graph::add_edge(int u, int v){
    if(adj[u][v] == 0 && adj[v][u] == 0){
        adj[u][v] = 1;
        adj[v][u] = 1;
        deg[u]++;
        deg[v]++;
    }
}

void Graph::fixsize(){
    int count_edge = 0;
    for(int i=0;i<MAXN;i++){
        if(deg[i] > 0) vertex_list.push_back(i);
        count_edge += deg[i];
    }
    n = vertex_list.size();
    m = count_edge / 2;
}

int Graph::contracted_v(int v){
    if(deg[v] == 1){
        int u;
        for(int i=0;i<MAXN;i++){
            if(adj[v][i]) u = i;
        }
        adj[u][v] = adj[v][u] = 0;
        deg[v] = 0;
        deg[u]--;
        n--;
        m--;
    }
    else if(deg[v] == 2){
        int u = -1, w = -1;
        for(int i=0;i<MAXN;i++){
            if(adj[v][i] && u == -1) u = i;
            else if (adj[v][i]) w = i;
        }
        if(adj[u][w]) m--;
        adj[u][w] = adj[w][u] = 1;
        adj[u][v] = adj[v][u] = 0;
        adj[v][w] = adj[w][v] = 0;
        deg[v] = 0;
        n--;
        m--;
    }
    return 1;
}

Graph Graph::subdivision(int u, int v, int w){
    Graph g(n, m);
    for(int i : vertex_list){
        for(int j : vertex_list){
            if(i == v || j == v) continue;
            if(adj[i][j] && i > j) g.add_edge(i, j);
        }
    }
    if(!adj[u][w]) g.add_edge(u, w);
    g.fixsize();
    return g;
}

bool Graph::isK5(){
	for(int a : vertex_list){
        for(int b : vertex_list){
            if(!adj[a][b]) continue;
            for(int c : vertex_list){
                if(!adj[a][c] || !adj[b][c]) continue;
                for(int d : vertex_list){
                    if(!adj[a][d] || !adj[b][d] || !adj[c][d]) continue;
                    for(int e : vertex_list){
                        if(!adj[a][e] || !adj[b][e] || !adj[c][e] || !adj[d][e]) continue;
                        //cout << "FOUND K5\n";
                        //cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << '\n';
                        return true;
                    }
                }
            }
        }
	}
	return false;
}

bool Graph::isK33(){
	for (int a : vertex_list){
		for (int d : vertex_list){
			if (!adj[a][d]) continue;
			for (int b : vertex_list){
				if (!adj[b][d] || a == b) continue;
				for (int e : vertex_list){
					if (!adj[a][e] || !adj[b][e] || d == e) continue;
					for (int c : vertex_list){
						if (!adj[d][c] || !adj[e][c] || c == a || c == b) continue;
						for (int f : vertex_list){
							if (!adj[a][f] || !adj[b][f] || !adj[c][f] || f == d || f == e) continue;
							//cout << "FOUND K3\n";
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool Graph::isPlanar(int depth){
    depth++;
    if(depth == MAXDEPTH) return true;
    if(n < 5 || m < 9) return true;
    if(n == 5 && m == 9) return true;
    if(m > n * 3 - 6) {
        return false;
    }
    int j = -1, sn = n;
    do{
        j = -1;
        for(int i=0;i<sn;i++){
            if(deg[i] == 2 || deg[i] == 1) j = contracted_v(i);
        }
    }while(j != -1);

    if(n < 5 || m < 9) return true;
    if(n == 5 && m == 9) return true;
    if(m > n * 3 - 6) {
        return false;
    }

    if(isK33() || isK5()) return false;
    else{
        for(int i : vertex_list){
            for(int j : vertex_list){
                if(i == j || !adj[i][j]) continue;
                for(int k : vertex_list){
                    if(i == k || j == k || !adj[j][k] || adj[i][k]) continue;
                    if(!subdivision(i, j, k).isPlanar(depth)) return false;
                }
            }
        }
    }
    return true;
}

void solve(){
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        u--;v--;
        g.add_edge(u,v);
    }

    g.fixsize();
    if(g.isPlanar(0)) cout << "Yes\n";
    else cout << "No\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q; cin>>q;
    while(q--){
        solve();
    }
    return 0;
}
