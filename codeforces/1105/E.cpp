#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

const int N = 42;

int g[N][N];
int res;
long long edges[51];
//3 ^ (n / 3)
void BronKerbosch(int n, long long R, long long P, long long X)
{
    if (P == 0LL && X == 0LL) {
        int t = __builtin_popcountll(R);
        res = max(res, t);
        return;
    }
    long long u = 0;
    while (!((1LL<<u) & (P|X))) u ++;
    for (int v = 0; v < n; v++) {
        if (((1LL << v) & P) && !((1LL << v) & edges[u])) {
            BronKerbosch(n, R | (1LL << v), P & edges[v], X & edges[v]);
            P -= (1LL << v);
            X |= (1LL << v);
        }
    }
}

int max_clique (int n)
{
    res = 0;
    for (int i = 1; i <= n; i++) {
        edges[i] = 0;
        for (int j = 1; j <= n; j++)  if (g[i][j]) edges[i - 1] |= ( 1LL << (j - 1) );
    }
    BronKerbosch(n, 0, (1LL << n) - 1, 0);
    return res;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    map<string, int> mp;
    set<int>se;
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n + 1; i++){
        int ty;
        if(i <= n) cin >> ty;
        if(ty == 1 || i > n){
            for(auto x: se) for(auto y: se) g[x][y] = 1, g[y][x] = 1;
            se.clear();
        }
        else{
            string s; cin >> s;
            if(mp.find(s) == mp.end()){
                mp[s]; mp[s] = mp.size();
            }
            int p = mp[s]; se.insert(p);
        }
    }
    for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++) g[i][j] = !g[i][j];
    for(int i = 1; i <= m; i++) g[i][i] = 0;
    cout << max_clique(m) << '\n';
    return 0;
}
