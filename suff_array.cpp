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

// suffix array construction 
// O(nlog(n))

vl sort_cyclic_shifts(const string& s) {
  int n = s.size();
  const int alphabet = 256;
  vl p(n), c(n), cnt(max(alphabet, n), 0);
  for (int i = 0; i < n; i++)
    cnt[s[i]]++;
  for (int i = 1; i < alphabet; i++)
    cnt[i] += cnt[i-1];
  for (int i = 0; i < n; i++)
    p[--cnt[s[i]]] = i;
  c[p[0]] = 0;
  int classes = 1;
  for (int i = 1; i < n; i++) {
    if (s[p[i]] != s[p[i-1]])
      classes++;
    c[p[i]] = classes - 1;
  }
  vl pn(n), cn(n);
  for (int h = 0; (1 << h) < n; ++h) {
    for (int i = 0; i < n; i++) {
      pn[i] = p[i] - (1 << h);
      if (pn[i] < 0)
        pn[i] += n;
    }
    fill(cnt.begin(), cnt.begin() + classes, 0);
    for (int i = 0; i < n; i++)
      cnt[c[pn[i]]]++;
    for (int i = 1; i < classes; i++)
      cnt[i] += cnt[i-1];
    for (int i = n-1; i >= 0; i--)
      p[--cnt[c[pn[i]]]] = pn[i];
    cn[p[0]] = 0;
    classes = 1;
    for (int i = 1; i < n; i++) {
      pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
      pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
      if (cur != prev)
        ++classes;
      cn[p[i]] = classes - 1;
    }
    c.swap(cn);
  }
  return p;
}

vl suffix_array_construction(string s) {
  s += "$";
  vl sorted_shifts = sort_cyclic_shifts(s);
  sorted_shifts.erase(sorted_shifts.begin());
  return sorted_shifts;
}

// Array with lcp for pair of adjacent in sorted order
// O(n)
// To calculate differents substrings: n*(n+1)/2 - sum(all(lcp))
vl lcp_construction(const string& s, const vl& p) {
  int n = s.size();
  vl rank(n, 0);
  for (int i = 0; i < n; i++)
    rank[p[i]] = i;

  int k = 0;
  vl lcp(n-1, 0);
  for (int i = 0; i < n; i++) {
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = p[rank[i] + 1];
    while (i + k < n && j + k < n && s[i+k] == s[j+k])
      k++;
    lcp[rank[i]] = k;
    if (k)
      k--;
  }
  return lcp;
}

// c is table for all iterations in line c.swap(cn)
// compare 2 substring of same length l, k = floor(log2(l))
int compare(int i, int j, int l, int k) {
  pair<int, int> a = {c[k][i], c[k][(i+l-(1 << k))%n]};
  pair<int, int> b = {c[k][j], c[k][(j+l-(1 << k))%n]};
  return a == b ? 0 : a < b ? -1 : 1;
}
