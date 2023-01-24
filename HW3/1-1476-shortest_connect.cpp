//connect path while doing shortest path
//use extra read function for faster input

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef pair<int, int> pii;
int INF = 2e9;

void read(int &number)
{
    register int c;
    number = 0;

    c = getchar();

    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
}


class Graph{
public:
    int v;
    int ia;
    vector<vector<pii>> ex;
    vector<int> a;
    void addEdge(int u, int v, int w);
    void sp();
    Graph(int v);
};

Graph::Graph(int v){
    this->v = v;
    a.assign(v, 0);
    int ma = INF;
    for(int i = 0; i < v; i++) {
        read(a[i]);
        if(ma > a[i]){
            ma = a[i];
            this->ia = i;
        }
    }
    ex.assign(v, vector<pii>());
}

void Graph::addEdge(int u, int v, int w){
    if(w > a[u] + a[ia] && w > a[v] + a[ia]){
        return;
    }
    ex[u].push_back({v, w});
    ex[v].push_back({u, w});
}

void Graph::sp(){
    long long res = 0;
    deque<pii> buf;
    set<pii> pq;
    vector<int> key(v, INF);
    vector<bool> visit(v, false);
    key[ia] = 0;
    pq.insert({0, ia});
    for(int i = 0; i < v; i++){
        if(i != ia)
            buf.push_back({a[ia] + a[i], i});
    }
    sort(buf.begin(), buf.end());

    int cnt = 0;
    while(!pq.empty() || !buf.empty()){
        int u, bu, wkey = INF, bw = INF;
        if(!pq.empty()){
            u = pq.begin()->second;
            wkey = pq.begin()->first;
        }
        if(!buf.empty()){
            bu = buf.front().second;
            bw = buf.front().first;
        }
        if(wkey < bw){
            pq.erase({wkey, u});
        }
        else{
            u = bu;
            wkey = bw;
            buf.pop_front();
        }

        if(visit[u]) continue;
        visit[u] = true;
        res += wkey;
        cnt++;
        if(cnt == v) break;

        int v, w;
        for(auto i : ex[u]){
            v = i.first;
            if(visit[v]) continue;
            w = i.second;

            if (!visit[v] && key[v] > w && a[u] + a[v] > w)
            {
                key[v] = w;
                pq.insert({key[v], v});
            }
        }
    }
    cout << res << '\n';
}

void solve(){
    int n, m;
    read(n); read(m);
    int u, v, w;

    Graph g(n);

    for(int i = 0; i < m; i++){
        read(u); read(v); read(w);
        v--; u--;
        g.addEdge(u, v, w);
    }

    g.sp();
    //cout << '0';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    read(t);
    while(t--){
        solve();
    }

    return 0;
}
