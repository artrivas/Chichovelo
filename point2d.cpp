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

int sgn(const long long& x) { return x >= 0 ? x ? 1 : 0 : -1; }

// intersection of 2 segements 1d
bool inter1(long long a, long long b, long long c, long long d) {
  if (a > b)
    swap(a, b);
  if (c > d)
    swap(c, d);
  return max(a, c) <= min(b, d);
}

// intersection of 2 segments ab cd
bool check_inter(const point2d& a, const point2d& b, const point2d& c, const point2d& d) {
  if (cross(a - c, d - c) == 0 && cross(b - c, d - c) == 0)
    return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
  return sgn(cross(b - a, c - a)) != sgn(cross(b - a, d - a)) &&
       sgn(cross(d - c, a - c)) != sgn(cross(d - c, b - c));
}

// atan2(y, x) -> transform cartesiano to angle [-pi: pi]
