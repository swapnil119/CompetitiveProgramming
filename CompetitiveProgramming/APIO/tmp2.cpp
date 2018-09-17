#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;


#define ll long long
#define db long double
#define ii pair <int, int>
#define vi vector <int>
#define fi first
#define se second
#define sz(a) (int)(a).size()
#define all(a) (a).begin(),(a).end()
#define pb push_back
#define mp make_pair
#define FN(i,n) for (int i = 0; i < (int)(n); ++i)
#define FEN(i,n) for (int i = 1;i <= (int)(n); ++i)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repv(i,a,b) for(int i=b-1;i>=a;i--)
#define SET(A, val) memset(A, val, sizeof(A))
typedef tree<ll ,null_type,less<ll>,
rb_tree_tag,tree_order_statistics_node_update>ordered_set ;

#ifdef TRACE
#define trace(...) _f(#__VA_ARGS_, _VA_ARGS_)
	template <typename Arg1>
	void __f(const char* name, Arg1&& arg1){
		cerr << name << " : " << arg1 << std::endl;
	}
	template <typename Arg1, typename... Args>
	void __f(const char* names, Arg1&& arg1, Args&&... args){
		const char* comma = strchr(names + 1, ','); cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
	}
#else
#define trace(...)
#endif

const int N = 2e5 + 10; 
int a[N];
ll pre[N];  

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL) ; cout.tie(NULL) ;
	int n; cin >> n; ll t; cin >> t; 
	ordered_set ost; 
	rep(i, 1, n + 1) {
		cin >> a[i]; 
		pre[i] = 1ll * a[i] + pre[i - 1]; 
	}
	ll ans = 0; 
	rep(i, 1, n + 1) {
		int x = order_of_key(pre[i] - t + 1ll);
		ans += 1ll * x; 
		ost.insert(pre[i]);
	}
	cout << ans << endl;
	return 0;
}
