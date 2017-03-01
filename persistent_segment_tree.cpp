#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
 
typedef long long int ll;
typedef pair<ll, ll> ipair;
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz size()
#define ln length()
#define rep(i,n) for(i=0;i<n;i++)
#define fu(i,a,n) for(i=a;i<=n;i++)
#define fd(i,n,a) for(i=n;i>=a;i--)
#define all(a)  a.begin(),a.end() 
#define gi(n) scanf("%d",&n)
#define gl(n) scanf("%lld",&n)
#define pi(n) printf("%d",n)
#define pl(n) printf("%lld",n);
#define pp printf(" ")
#define pn printf("\n")

struct node {
	ll count;
	node *left;
	node *right;
	node(ll c, node *a, node *b) {
		count = c;
		left = a;
		right = b;
	}
};
node *null = new node(0, NULL, NULL);
node *root[100005];
ll a[100005];
ll rm[100005];
node *insert(ll start, ll end, node *r, ll val) {
	if(val >= start && val <= end) {
		if(r == null) {
			r = new node(0, null, null);
		}
		if(start == end) {
			return new node(r->count + 1, r->left, r->right);
		}
		ll mid = (start + end)/2;
		node *p = insert(start, mid, r->left, val);
		node *q = insert(mid + 1, end, r->right, val);
		return new node(p->count + q->count, p, q);
	}
	return r;
}
ll query(ll start, ll end, node *a, node *b, ll k) {
	if(start == end) {
		return start;
	}
	ll mid;
	mid = (start + end)/2;
	ll cnt = a->left->count - b->left->count;
	if(cnt >= k) {
		return query(start, mid, a->left, b->left, k);
	}
	return query(mid + 1, end, a->right, b->right, k - cnt);
}
int main() {
	ll n, q;
	gl(n);
	gl(q);
	map<ll, ll> m;
	ll i;
	fu(i, 1, n) {
		gl(a[i]);
		m[a[i]]++;
	}
	ll maxi = 1;
	map<ll, ll> :: iterator it;
	for(it = m.begin(); it != m.end(); it++) {
		m[it->first] = maxi;
		rm[maxi] = it->first;
		maxi++;
	}
	maxi--;
	null->left = null->right = null;
	fu(i, 1, n) {
		if(i == 1) {
			root[i] = insert(1, maxi, null, m[a[i]]);
		}
		else {
			root[i] = insert(1, maxi, root[i - 1], m[a[i]]);
		}
	}
	while(q--) {
		ll u, v, k;
		gl(u);
		gl(v);
		gl(k);
		ll ans = query(1, maxi, root[v], (u == 1)?null:root[u - 1], k);
		pl(rm[ans]);
		pn;
	}
	return 0;
}
