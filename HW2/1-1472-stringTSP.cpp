//find shortest string that every other string is substring

#include <bits/stdc++.h>

using namespace std;

string combine(string a, string b){
    for(auto k = min(a.size(), b.size()); k > 0; k--){
        if(a.substr(a.size() - k) == b.substr(0, k)){
            return a + b.substr(k);
        }
    }
    return a + b;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<string> a;
    for(int i = 0; i < n; i++){
        string tt; cin >> tt;
        a.push_back(tt);
    }

    bool repeat = true;
    while(repeat){
        repeat = false;
        int i = 0;
        while(i < a.size()){
            for(int j = 0; j < a.size(); j++){
                if(j == i) continue;
                if (a[i].find(a[j]) != std::string::npos){
                    a.erase(a.begin() + j);
                    repeat = true;
                }
            }
            i++;
        }
    }

    sort(a.begin(), a.end());
    n = a.size();

    string shortest = a[0];
    string t = a[0];

    for(int i = 1; i < n; i++){
        t = combine(t, a[i]);
        shortest = t;
    }

    while(next_permutation(a.begin(), a.end())){
        string t = a[0];
        for(int i = 1; i < n; i++){
            t = combine(t, a[i]);
        }
        if(t.length() < shortest.length()) shortest = t;
        else if(t.length() == shortest.length() && lexicographical_compare(t.begin(), t.end(), shortest.begin(), shortest.end())) shortest = t;
    }
    cout << shortest;
    return 0;
}
