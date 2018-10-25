#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define vll vector<ll>
#define vc vector<char>
#define vs vector<string>
#define vpll vector<pll>
#define vpii vector<pii>
#define umap unordered_map
#define uset unordered_set
#define PQ priority_queue

#define printa(a,L,R) for(int i=L;i<R;i++) cout<<a[i]<<(i==R-1?'\n':' ')
#define printv(a) printa(a,0,a.size())
#define print2d(a,r,c) for(int i=0;i<r;i++) for(int j=0;j<c;j++) cout<<a[i][j]<<(j==c-1?'\n':' ')
#define pb push_back
#define eb emplace_back
#define mt make_tuple
#define fbo find_by_order
#define ook order_of_key
#define MP make_pair
#define UB upper_bound
#define LB lower_bound
#define SQ(x) ((x)*(x))
#define issq(x) (((ll)(sqrt((x))))*((ll)(sqrt((x))))==(x))
#define F first
#define S second
#define mem(a,x) memset(a,x,sizeof(a))
#define inf 1e18
#define PI (acos(-1.0))
#define E 2.71828182845904523536
#define gamma 0.5772156649
#define nl "\n"
#define lg(r,n) (int)(log2(n)/log2(r))
#define pf printf
#define sf scanf
#define _ccase printf("Case %lld: ",++cs)
#define _case cout<<"Case "<<++cs<<": "
#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }

#define asche cerr<<"Ekhane asche\n";
#define rev(v) reverse(v.begin(),v.end())
#define srt(v) sort(v.begin(),v.end())
#define grtsrt(v) sort(v.begin(),v.end(),greater<int>())
#define all(v) v.begin(),v.end()
#define mnv(v) *min_element(v.begin(),v.end())
#define mxv(v) *max_element(v.begin(),v.end())
#define toint(a) atoi(a.c_str())
#define fast ios_base::sync_with_stdio(false),cin.tie(NULL)
#define valid(tx,ty) (tx>=0&&tx<n&&ty>=0&&ty<m)
#define one(x) __builtin_popcount(x)
#define Unique(v) v.erase(unique(all(v)),v.end())
#define stree ll l=(n<<1),r=l+1,mid=b+(e-b)/2
#define fout(x) fixed<<setprecision(x)
string tostr(int n) {stringstream rr;rr<<n;return rr.str();}
template <typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//ll dx[]={1,0,-1,0,1,-1,-1,1};
//ll dy[]={0,1,0,-1,1,1,-1,-1};

#define debug(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); deb(_it, args); }
void deb(istream_iterator<string> it) {}
template<typename T, typename... Args>
void deb(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << endl;
    deb(++it, args...);
}

const int mod=1e9+7;
const int N=3e5+9;
const ld eps=1e-9;
//ll gcd(ll a,ll b){while(b){ll x=a%b;a=b;b=x;}return a;}
//ll lcm(ll a,ll b){return a/gcd(a,b)*b;}
//ll qpow(ll n,ll k) {ll ans=1;assert(k>=0);while(k>0){if(k&1) ans=(ans*n)%mod;n=(n*n)%mod;k>>=1;}return ans%mod;}

///diameter of the Articulation Bridge Tree
vi g[N],gr[N];
bool vis[N];
int T,low[N],dis[N],d[N],par[N];
set<pii>bridge;
void dfs(int u,int pre)
{
    low[u]=dis[u]=++T;
    vis[u]=1;
    for(auto v:g[u]){
        if(!vis[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>dis[u]) bridge.insert({min(u,v),max(u,v)});
        }
        else{
            if(v!=pre) low[u]=min(low[u],dis[v]);
        }
    }
}
int find_(int x)
{
    if(par[x]==x) return x;
    return par[x]=find_(par[x]);
}
void merge_(int x,int y)
{
    int u=find_(x);
    int v=find_(y);
    if(u!=v){
        if(rand()%2) par[u]=v;
        else par[v]=u;
    }
}
int bfs(int s)
{
    mem(d,-1);
    queue<int>q;
    q.push(s);
    d[s]=0;
    int u=s;
    while(!q.empty()){
        u=q.front();
        q.pop();
        for(auto v:gr[u]){
            if(d[v]==-1){
                q.push(v);
                d[v]=d[u]+1;
            }
        }
    }
    return u;
}
int main()
{
    fast;
    int i,j,k,n,m,u,v,ans=0;
    cin>>n>>m;
    for(i=1;i<=m;i++) cin>>u>>v,g[u].eb(v),g[v].eb(u);
    dfs(1,0);
    for(i=1;i<=n;i++) par[i]=i;
    for(u=1;u<=n;u++){
        for(auto v:g[u]){
            if(bridge.find({min(u,v),max(u,v)})==bridge.end()) merge_(u,v);
        }
    }
    for(u=1;u<=n;u++){
        for(auto v:g[u]){
            if(bridge.find({min(u,v),max(u,v)})!=bridge.end()){
                int x=find_(u);
                int y=find_(v);
                gr[x].eb(y);
                gr[y].eb(x);
            }
        }
    }
    u=bfs(find_(1));
    v=bfs(find_(u));
    cout<<d[v]<<nl;
    return 0;
}