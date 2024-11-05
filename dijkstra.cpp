#include<bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pl;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second

const ll mod = 1e9+7;
const ll inf = 1e18+10;

vector<vector<pl>> adj;

// O(mlog(n))
// calculate mint dist from s to all vertices
void dijkstra(int s, vl& d, vl& p) {
  int n = adj.size();
  d.assign(n, inf);
  p.assign(n, -1);

  d[s] = 0;
  set<pl> q;
  q.insert({0, s});
  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    for (auto edge : adj[v]) {
      int to = edge.first;
      int len = edge.second;

      if (d[v] + len < d[to]) {
        q.erase({d[to], to});
        d[to] = d[v] + len;
        p[to] = v;
        q.insert({d[to], to});
      }
    }
  }
}
