#include  <bits/stdc++.h>
using namespace std;
#define forn(i,n) for(int i = 0; i < n; i++)

bool er(vector<int>& d,int n){
    vector<long long> h(n, 0);
    h[0] = d[0];
    for(int i = 1; i < n; i++){
        h[i] = h[i-1] + (long long)d[i];
    }
    long long w = n;
    for(long long i = 1; i <= n; i++) {
        while(w > 0 && d[w - 1] < i) w--;
        long long y = max(i, w);
        if(h[i - 1] > i * (y - 1) + h[n - 1] - h[y - 1])
            return false;
    }
    return true;
}

void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> deg;
    bool plan = true;
    int sum = 0;
    int tttt;
    forn(i, n){
        cin >> tttt;
        deg.push_back(tttt);
        sum += (tttt % 2);
    }

    if(sum % 2 == 1) plan = false;

    int ma, mb;
    forn(i, m){
        cin >> ma >> mb;
        ma--; mb--;
        deg[ma]--; deg[mb]--;
    }
    forn(i, n){
        if(deg[i] < 0 || deg[i] >= n) {
            plan = false;
            break;
        }
    }

    if(!plan) {
        cout << "No\n";
        return;
    }

    sort(deg.begin(), deg.end(), greater<>());
    plan = er(deg, deg.size());

    if(plan) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int ts;
    cin >> ts;
    while(ts--){
        solve();
    }
    return 0;
}
