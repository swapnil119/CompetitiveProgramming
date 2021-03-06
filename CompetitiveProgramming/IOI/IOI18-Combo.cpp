#include <bits/stdc++.h>
#include "combo.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define db long double
#define ii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define sz(a) (int)(a).size()
#define all(a) (a).begin(),(a).end()
#define pb push_back
#define mp make_pair
#define FN(i, n) for (int i = 0; i < (int)(n); ++i)
#define FEN(i,n) for (int i = 1;i <= (int)(n); ++i)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repv(i,a,b) for(int i=b-1;i>=a;i--)
#define SET(A, val) memset(A, val, sizeof(A))
typedef tree<int ,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set ;
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the kth largest element.(0-based)
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
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
string guess_sequence(int N)
{
  string ans="";
  string query="";
  query="AB";
  int x=press(query);
  if(x)
    {
      x=press("A");
      if(x==0) ans+='B';
      else ans+='A';
    }
  else
    {
      x=press("X");
      if(x==0) ans+='Y';
      else ans+='X';
    }
  if(N==1) return ans;
  rep(i,2,N)
    {
      if(ans[0]=='A')
	{
	  query=ans+"B"+ans+"XB"+ans+"XX"+ans+"XY";
	  x=press(query);
	  if(x==sz(ans)) ans+="Y";
	  else if(x==sz(ans)+1) ans+="B";
	  else ans+="X";
	}
      else if(ans[0]=='B')
	{
	  query=ans+"A"+ans+"XA"+ans+"XX"+ans+"XY";
	  x=press(query);
	  if(x==sz(ans)) ans+="Y";
	  else if(x==sz(ans)+1) ans+="A";
	  else ans+="X";
	}
      else if(ans[0]=='X')
	{
	  query=ans+"A"+ans+"BA"+ans+"BB"+ans+"BY";
	  x=press(query);
	  if(x==sz(ans)) ans+="Y";
	  else if(x==sz(ans)+1) ans+="A";
	  else ans+="B";
	}
      else
	{
	  query=ans+"A"+ans+"XA"+ans+"XX"+ans+"XB";
	  x=press(query);
	  if(x==sz(ans)) ans+="B";
	  else if(x==sz(ans)+1) ans+="A";
	  else ans+="X";
	}
    }
  if(ans[0]!='A')
    {
      query=ans+"A";
      x=press(query);
      if(x==N) return query;
    }
  if(ans[0]!='B')
    {
      query=ans+"B";
      x=press(query);
      if(x==N) return query;
    }
  if(ans[0]!='X')
    {
      if(ans[0]=='Y')
	{
	  ans+="X";
	  return ans;
	}
      query=ans+"X";
      x=press(query);
      if(x==N) return query; 
    }
  ans+="Y";
  return ans;
}
