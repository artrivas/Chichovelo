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
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
 
#define DBG(x) cerr << #x << " = " << (x) << endl
#define DBGY(x) cerr << #x << " = " << (x) << ", "
#define RAYA cerr << " ======================== " << endl

const ll mod = 1e9+7;
const ll inf = 1e18+10;

template<typename T>
ostream & operator<<(ostream &os, const vector<T>&v){
	os<<"[";
	forn(i,v.size()){
		if(i>0) os << ",";
		os << v[i];
	}
	return os << "]";
}




ll binpow(ll a, ll b) {
    a %= mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve(){
	
}

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--) solve();
    return 0;
}

