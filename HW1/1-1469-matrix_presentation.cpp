#include  <bits/stdc++.h>
using namespace std;
#define forn(i,n) for(int i = 0; i < n; i++)
#define MOD 1000000007

struct edge{
    int u, v, w;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(n, 0));
    vector<int> indegree(n, 0);
    vector<int> outdegree(n, 0);

    edge e;
    forn(i, m){
        cin >> e.u >> e.v >> e.w;
        mat[e.u - 1][e.v - 1] = e.w;
        outdegree[e.u - 1]++;
        indegree[e.v - 1]++;
    }

    forn(i, n){
        forn(j, n){
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }

    forn(i, n){
        cout << indegree[i] << " " << outdegree[i] << "\n";
    }

    return 0;
}
