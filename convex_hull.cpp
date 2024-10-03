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
typedef ll ftype;
struct point2d {
    ftype x, y;
    point2d() {}
    point2d(ftype x, ftype y): x(x), y(y) {}
    point2d& operator+=(const point2d &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
 
    point2d operator+(const point2d &t) const {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const {
        return point2d(*this) -= t;
    }
    point2d operator*(ftype t) const {
        return point2d(*this) *= t;
    }
    point2d operator/(ftype t) const {
        return point2d(*this) /= t;
    }
};
 
point2d operator*(ftype a, point2d b) {
    return b * a;
}
ftype dot(point2d a, point2d b) {
    return a.x * b.x + a.y * b.y;
}
ftype norm(point2d a) {
    return dot(a, a);
}
double abs(point2d a) {
    return sqrt(norm(a));
}
ftype cross(point2d a, point2d b) {
    return a.x * b.y - a.y * b.x;
}
 
vector<point2d> convexhull(vector<point2d>& p) {
  int n = p.size();
  if (n <= 3) return p;
 
  sort(all(p), [](auto p1, auto p2){
      if (p1.x == p2.x) return p1.y < p2.y;
      return p1.x < p2.x;
      });
  vector<point2d> u, l;
  l.reserve(n), u.reserve(n);
  for (int i = 0; i < n; i++) {
    while(l.size() > 1 and cross(l.back() - *next(l.rbegin()), p[i] - *next(l.rbegin())) < 0) {
      l.pop_back();
    }
    l.pb(p[i]);
  }
 
  for (int i = n-1; i >= 0; i--) {
    while(u.size() > 1 and cross(u.back() - *next(u.rbegin()), p[i] - *next(u.rbegin())) < 0) {
      u.pop_back();
    }
    u.pb(p[i]);
  }
  u.pop_back();
  l.pop_back();
  u.insert(u.end(), all(l));
  return u; 
}
