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

const int N = 1000000;

vector<int> primes;
bool is_composite[N] = {};

void sieve() {
  for (int i = 2; i < N; i++) {
    if (!is_composite[i]) primes.pb(i);
    for (int j = 0; j < primes.size() && i * primes[j] < N; j++) {
      is_composite[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }
}

// multiplicative functions
// mobius
// mu(d) = 0 <-> d contiene factores primos repetidos
// mu(d) = 1 <-> d == 1 
// mu(d) = (-1) ^ k <-> k = factores primos <-> square-free
int mu[N] = {};

void mobius() {
  mu[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!is_composite[i]) {
      primes.pb(i);
      mu[i] = -1;
    }
    for (int j = 0; j < primes.size() && i*primes[j] < N; j++) {
      is_composite[i*primes[j]] = true;
      if (i % primes[j] != 0)
        mu[i*primes[j]] = mu[i] * mu[primes[j]];
      else {
        mu[i*primes[j]] = 0;
        break;
      }
    }
  }
}
