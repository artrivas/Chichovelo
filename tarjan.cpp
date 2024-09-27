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

/** Takes in an adjacency list and calculates the SCCs of the graph. */
class trj {
  private:
	vector<vl> rev_adj;
  vl post;
  vl comp;

	vector<bool> visited;
	ll timer = 0;
	ll id = 0;

	void fill_post(int at) {
		visited[at] = true;
		for (int n : rev_adj[at]) {
			if (!visited[n]) { fill_post(n); }
		}
		post[at] = timer++;
	}

	void find_comp(int at) {
		visited[at] = true;
		comp[at] = id;
		for (int n : adj[at]) {
			if (!visited[n]) { find_comp(n); }
		}
	}

  public:
	const vector<vl> &adj;

	trj(const vector<vl> &adj)
	    : adj(adj), rev_adj(adj.size()), post(adj.size()), comp(adj.size()),
	      visited(adj.size()) {
		vector<int> nodes(adj.size());
		for (int n = 0; n < adj.size(); n++) {
			nodes[n] = n;
			for (int next : adj[n]) { rev_adj[next].pb(n); }
		}

		for (int n = 0; n < adj.size(); n++) {
			if (!visited[n]) { fill_post(n); }
		}
		sort(all(nodes), [&](int n1, int n2) { return post[n1] > post[n2]; });

		visited.assign(adj.size(), false);
		for (int n : nodes) {
			if (!visited[n]) {
				find_comp(n);
				id++;
			}
		}
	}
	int size() const { return id; }
	int scc_of(int n) const { return comp[n]; }
};
