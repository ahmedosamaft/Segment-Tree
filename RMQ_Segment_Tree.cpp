/****************************************************
         ❤ Bsmellah El Rahman El Rahim ❤
****************************************************/

#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define vi vector<int>
#define int ll
#define vll vector<ll>
#define ZA7med ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define debug(x) cerr << #x << " " << x << endl

struct SegmentTree {
  SegmentTree(vi &A) { build(A); }
  ll RMQ(int QL, int QR) { return RMQ(0, n - 1, 1, QL, QR); }
  void update(int QL, int QR, int val) { update(0, n - 1, 1, QL, QR, val); }

private:
  vll st;
  vi lazy;
  int n, HAMADA = -1;
  ll l(ll L) { return (L << 1); }
  ll r(ll R) { return (R << 1 | 1); }

  void build(vi &A) {
    int m = A.size();
    if ((m & (m - 1)))
      n = 1 << (__lg(A.size()) + 1);
    else
      n = m;
    st.assign((n << 1), 0);
    lazy.assign((n << 1), -1);
    for (int i = 0; i < m; ++i)
      st[i + n] = A[i];
    for (int i = n - 1; i; --i)
      st[i] = min(st[l(i)], st[r(i)]);
  }

  void propagate(int node, int L, int R) {
    if (~lazy[node]) {
      st[node] = lazy[node];
      if (L != R)
        lazy[l(node)] = lazy[r(node)] = lazy[node];
      lazy[node] = -1;
    }
  }
  ll conquer(int a, int b) {
    if (!~a)
      return b;
    if (!~b)
      return a;
    return min(a, b);
  }
  ll RMQ(int L, int R, int node, int QL, int QR) {
    propagate(node, L, R);
    if (L >= QL && QR >= R)
      return st[node];
    if (QR < L || QL > R)
      return HAMADA;
    int M = L + R >> 1;
    return conquer(RMQ(L, M, l(node), QL, min(M, QR)),
                   RMQ(M + 1, R, r(node), max(M + 1, QL), QR));
  }

  void update(int L, int R, int node, int QL, int QR, int val) {
    propagate(node, L, R);
    if (QR < L || QL > R)
      return;
    if (L >= QL && QR >= R) {
      lazy[node] = val;
      propagate(node, L, R);
    } else {
      int M = L + R >> 1;
      update(L, M, l(node), QL, min(M, QR), val);
      update(M + 1, R, r(node), max(M + 1, QL), QR, val);
      if (L != R) {
        st[node] = min(st[l(node)], st[r(node)]);
      }
    }
  }
};

signed main() {
  ZA7med;
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("error.txt", "w", stderr);
#endif
  int n, q;
  cin >> n >> q;
  vi v(n);
  for (auto &i : v)
    cin >> i;

  SegmentTree st(v);
  while (q--) {
    int op, l, r;
    cin >> op >> l >> r;
    if (op == 1) {
      st.update(l - 1, l - 1, r);
    } else
      cout << st.RMQ(l - 1, r - 1) << endl;
  }
}
