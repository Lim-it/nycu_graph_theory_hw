#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> adj(n, vector<int>());
    vector<int> deg(n, 0);
    vector<int> visit(n, 0);
    vector<int> cnt(n, 0);
    vector<int> joint;
    vector<int> startnode;
    vector<pair<int, int>> startnodes;
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u; v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    int m;
    cin >> m;
    vector<int> cind(m, 0);
    for(int i = 0; i < m; i++){
        cin >> cind[i];
    }

    queue<int> q;
    for(int i = 0; i < n; i++){
        if(deg[i] == 1){
            q.push(i);
            visit[i] = 1;
        }
    }
    while(q.size()){
        int x = q.front();
        q.pop();
        for(int y : adj[x]){
            if(visit[y] == 0){
                visit[y] = 2;
                if(deg[y] == 2){
                    q.push(y);
                    visit[y] = 1;
                }
                cnt[y] = cnt[x] + 1;
            }
            else if(visit[y] == 2 && deg[y] == 3){
                startnode.push_back(y);
                startnodes.push_back({cnt[y], cnt[x] + 1});
            }
        }
    }

    q.push(startnode[0]);
    visit[startnode[0]] = 1;
    joint.push_back(startnode[0]);
    while(q.size()){
        int x = q.front();
        q.pop();
        for(int y : adj[x]){
            if(visit[y] != 1){
                q.push(y);
                if(deg[y] == 3) joint.push_back(y);
                visit[y] = 1;
            }
        }
    }

    bool samekey = true;
    if(joint.size() != m) samekey = false;
    else if((cind[0] == startnodes[0].first || cind[0] == startnodes[0].second)
            && (cind[m - 1] == startnodes[1].first || cind[m - 1] == startnodes[1].second)  ){
        for(int i = 1; i < m - 1; i++){
            if(cind[i] != cnt[joint[i]]) {
                samekey = false;
                break;
            }
        }
    }
    else if((cind[0] == startnodes[1].first || cind[0] == startnodes[1].second)
            && (cind[m - 1] == startnodes[0].first || cind[m - 1] == startnodes[0].second)  ){
        reverse(joint.begin(), joint.end());
        for(int i = 1; i < m - 1; i++){
            if(cind[i] != cnt[joint[i]]) {
                samekey = false;
                break;
            }
        }
    }
    else samekey = false;

    if(samekey) cout << "YES\n";
    else cout << "NO\n";

    return 0;
}
