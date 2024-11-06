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

int half(const point2d& p) {
  return int(p.y || (p.y == 0 && p.x < 0));
}

// graph planar -> faces in O(nlog(n))
vector<vector<size_t>> find_faces(vector<point2d> vertices, vector<vector<size_t>> adj) {
  size_t n = vertices.size();
  vector<vector<char>> used(n);
  for (size_t i = 0; i < n; i++) {
    used[i].resize(adj[i].size());
    used[i].assign(adj[i].size(), 0);
    auto compare = [&](size_t l, size_t r) {
      point2d pl = vertices[l] - vertices[i];
      point2d pr = vertices[r] - vertices[i];
      if (half(pl) != half(pr))
        return half(pl) < half(pr);
      return cross(pl, pr) > 0;
    };
    sort(adj[i].begin(), adj[i].end(), compare);
  }
  vector<std::vector<size_t>> faces;
  for (size_t i = 0; i < n; i++) {
    for (size_t edge_id = 0; edge_id < adj[i].size(); edge_id++) {
      if (used[i][edge_id]) {
        continue;
      }
      std::vector<size_t> face;
      size_t v = i;
      size_t e = edge_id;
      while (!used[v][e]) {
        used[v][e] = true;
        face.push_back(v);
        size_t u = adj[v][e];
        size_t e1 = std::lower_bound(adj[u].begin(), adj[u].end(), v, [&](size_t l, size_t r) {
          point2d pl = vertices[l] - vertices[u];
          point2d pr = vertices[r] - vertices[u];
          if (half(pl) != half(pr))
            return half(pl) < half(pr);
          return cross(pl, pr) > 0;
        }) - adj[u].begin() + 1;
        if (e1 == adj[u].size()) {
          e1 = 0;
        }
        v = u;
        e = e1;
      }
      reverse(face.begin(), face.end());
      int sign = 0;
      for (size_t j = 0; j < face.size(); j++) {
        size_t j1 = (j + 1) % face.size();
        size_t j2 = (j + 2) % face.size();
        int64_t val = cross(vertices[face[j1]] - vertices[face[j]], vertices[face[j2]] - vertices[face[j]]);
        if (val > 0) {
          sign = 1;
          break;
        } else if (val < 0) {
          sign = -1;
          break;
        }
      }
      if (sign <= 0) {
        faces.insert(faces.begin(), face);
      } else {
        faces.emplace_back(face);
      }
    }
  }
  return faces;
}
// atan2(y, x) -> transform cartesiano to angle [-pi: pi]
