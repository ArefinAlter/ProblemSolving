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
const int mxn=5e5+9;
const ld eps=1e-9;
//ll gcd(ll a,ll b){while(b){ll x=a%b;a=b;b=x;}return a;}
//ll lcm(ll a,ll b){return a/gcd(a,b)*b;}
//ll qpow(ll n,ll k) {ll ans=1;assert(k>=0);while(k>0){if(k&1) ans=(ans*n)%mod;n=(n*n)%mod;k>>=1;}return ans%mod;}
int a[2*mxn],t[4*mxn];
vpii que[mxn];
int ans[mxn],last_occur[mxn],next_idx[mxn];
void upd(int n,int b,int e,int i,int x)
{
    if(b>i||i>e) return;
    if(b==e&&b==i){
        t[n]=x;
        return;
    }
    stree;
    upd(l,b,mid,i,x);
    upd(r,mid+1,e,i,x);
    t[n]=max(t[l],t[r]);
}
int query(int n,int b,int e,int i,int j)
{
    if(b>j||i>e) return 0;
    if(b>=i&&e<=j) return t[n];
    stree;
    return max(query(l,b,mid,i,j),query(r,mid+1,e,i,j));
}
int main()
{
    fast;
    int i,j,k,n,m,l,r,q;
    cin>>n;
    for(i=1;i<=n;i++) cin>>a[i];
    for(i=n;i>=1;i--){
        if(last_occur[a[i]]){
            next_idx[i]=last_occur[a[i]];
        }
        else{
            next_idx[i]=n+i;
            a[n+i]=a[i];
        }
        last_occur[a[i]]=i;
    }
    cin>>q;
    for(i=1;i<=q;i++){
        cin>>l>>r;
        if(l==r){
            ans[i]=a[l];
            continue;
        }
        que[l].eb(r,i);
    }
    for(i=1;i<=n;i++) if(last_occur[a[i]]==i) upd(1,1,n,i,next_idx[i]);
    for(l=1;l<=n;l++){
        for(auto x:que[l]){
            r=x.F;
            int idx=query(1,1,n,l,r);
            if(idx>r) ans[x.S]=a[idx];
        }
        if(next_idx[l]>n) continue;
        upd(1,1,n,next_idx[l],next_idx[next_idx[l]]);
    }
    for(i=1;i<=q;i++) cout<<ans[i]<<nl;
    return 0;
}
