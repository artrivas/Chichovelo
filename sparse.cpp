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

const int K = 20;
const int MAXN = 400000;

// memory O(n*log(n))
// K >= floor(log2(MAXN))
int st[K+1][MAXN];
int log2_floor(unsigned long long i) {
  return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

// build O(n*log(n))
void build(vl& array) {
  std::copy(all(array), st[0]);
  const int N = array.size();
  for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++)
      st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}

// query O(1): [L, R]
ll query(ll L, ll R) {
  int i = log2_floor(R - L + 1);
  return min(st[i][L], st[i][R - (1 << i) + 1]);
}
