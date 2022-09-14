// Author: Akshay A Baiju
// Problem: Sloth Naptime
// URL: https://codeforces.com/gym/102694/problem/C

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl "\n"   //not to be used in interactive problems
#define sync ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define PI 3.141592653589793238462

const int M = 1e9+7;
const int MM = 998244353;
const int N = 2e5+7;
const ll inf = 1e18;

vector <vector <ll>> up;
vector <ll> level;

void dfs(ll node, ll par, vector <ll> adj[])
{
    for (auto &it: adj[node])
    {
        if (it==par) continue;
        level[it]=level[node]+1;
        dfs(it,node,adj);
    }
}

void binary_lifting(ll node, ll par, vector <ll> adj[])
{
    up[node][0]=par;
    for (ll i=1;i<20;i++)
    {
        if (up[node][i-1]!=-1)
            up[node][i]=up[up[node][i-1]][i-1];
        else
            up[node][i]=-1;
    }
    for (auto &it: adj[node])
    {
        if (it==par) continue;
        binary_lifting(it,node,adj);
    }
}

ll lift_node(ll node, ll k)
{
    for (ll i=19;i>=0;i--)
    {
        if (node==-1 || k==0) break;
        if (k&(1LL<<i))
        {
            node=up[node][i];
            k-=(1LL<<i);
        }
    }
    return node;
}

ll LCA(ll u, ll v)
{
    // make same level
    if (level[u]<level[v]) swap(u,v);
    u=lift_node(u,level[u]-level[v]);
    if (u==v) return u;
    for (ll i=19;i>=0;i--)
    {
        ll uu=up[u][i];
        ll vv=up[v][i];
        if (uu!=vv)
        {
            u=uu;
            v=vv;
        }
    }
    ll lca=lift_node(u,1);
    return lca;
}

void solve()
{
    ll n; cin>>n;
    up.resize(n, vector <ll> (20,-1));
    level.resize(n);
    vector <ll> adj[n];
    for (ll i=0;i<n-1;i++)
    {
        ll u,v; cin>>u>>v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // dfs -> level
    level[0]=0;
    dfs(0,-1,adj);
    binary_lifting(0,-1,adj);
    ll q; cin>>q;
    while (q--)
    {
        ll a,b,c; cin>>a>>b>>c; a--; b--;
        ll lca=LCA(a,b);
        if (lca==a || lca==b)
        {
            if (level[a]>level[b])
            {
                // move upward
                ll move_up_a=min(level[a]-level[b],c);
                ll node=lift_node(a,move_up_a);
                cout<<node+1<<endl;
            }
            else
            {
                // move downwards
                ll diff=level[b]-level[a];
                if (c>=diff) cout<<b+1<<endl;
                else
                {
                    ll move_up_b=diff-c;
                    ll node=lift_node(b,move_up_b);
                    cout<<node+1<<endl;
                }
            }
        }
        else
        {
            // move from a to lca
            ll diff=level[a]-level[lca];
            if (c<diff)
            {
                ll node=lift_node(a,c);
                cout<<node+1<<endl;
            }
            else
            {
                c-=diff;
                // standing at lca
                // move down from lca to b
                ll diff=level[b]-level[lca];
                if (c>=diff) cout<<b+1<<endl;
                else
                {
                    ll move_up_b=diff-c;
                    ll node=lift_node(b,move_up_b);
                    cout<<node+1<<endl;
                }
            }
        }
    }
}

int main()
{
    sync;
    int t=1;
    // cin>>t;
    for (int test=1;test<=t;test++)
    {
        solve();
        // cout<<endl;
    }
    return 0;
}
