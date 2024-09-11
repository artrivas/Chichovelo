#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<long long> vl;
typedef pair<long long,long long> pl;
typedef vector<pair<long long,long long>> vpl;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define fi first
#define se second

const ll mod = 1e9+7;
const ll inf = 1e18+10;

struct node {
  ll sum;
};

node combine(const node& l, const node& r) {
  node ans;
  ans.sum = l.sum + r.sum;
  return ans;
}

node make_node(ll val) {
  if (val == inf) {
    return {};
  }
  return {val};
}

class st {
  vector<node> t;
  ll n;
  void build(const vl&a, ll v, ll tl, ll tr) {
    if (tl == tr) {
      t[v] = make_node(a[tl]);
    }
    else {
      ll tm = (tl + tr) / 2;
      build(a, v*2, tl, tm);
      build(a, v*2+1, tm+1, tr);
      t[v] = combine(t[v*2], t[v*2+1]);
    }
  }

  void update(ll v, ll tl, ll tr, ll pos, ll new_val) {
    if (tl == tr) {
      t[v] = make_node(new_val);
    }
    else {
      ll tm = (tl + tr) / 2;
      if (pos <= tm) update(v*2, tl, tm, pos, new_val);
      else update(v*2+1, tm+1, tr, pos, new_val);
      t[v] = combine(t[v*2], t[v*2+1]);
    }
  }

  node query(const ll& v, const ll& tl, const ll& tr, const ll& l, const ll& r) {
    if (l > r) return make_node(inf);
    if (l == tl && r == tr) return t[v];
    ll tm = (tl + tr)/2;
    return combine(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
  }
 public:
  st(const vl& a) {
    this->n = a.size();
    t.resize(4*n);
    build(a, 1, 0, n-1);
  }

  void update(ll pos, ll new_val) {
    update(1, 0, n-1, pos, new_val);
  }

  node query(ll l, ll r) {
    return query(1, 0, n-1, l, r);
  }
};
