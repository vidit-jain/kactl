/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * ExtDesc: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * Status: stress-tested
 */
#pragma once

auto add = [&](int ind, int end) {};
auto del = [&](int ind, int end) {};
auto calc = [&]() {};

vi mo(vector<pii> Q) {
	int L = 0, R = 0, blk = 350; // ~N/sqrt(Q)
	vi s(sz(Q)), res = s;
#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
	iota(all(s), 0);
	sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
	for (int qi : s) {
		pii q = Q[qi];
		while (L > q.first) add(--L, 0);
		while (R < q.second) add(R++, 1);
		while (L < q.first) del(L++, 0);
		while (R > q.second) del(--R, 1);
		res[qi] = calc();
	}
	return res;
}

vector<array<int,2>> Q(q);
auto moTree = [&](int root=0){
    int N = sz(adj), pos[2] = {}, blk = 350; // ~N/sqrt(Q)
    vi s(sz(Q)), res = s, I(N), L(N), R(N), in(N), par(N);
    add(0, 0), in[0] = 1;
    function<void(int,int,int)> dfs = [&](int x, int p, int dep){
        par[x] = p; L[x] = N;
        if (dep) I[x] = N++;
        for (auto &to : adj[x]) if (to != p) dfs(to, x, !dep);
        if (!dep) I[x] = N++;
        R[x] = N;
    };
    dfs(root, -1, 0);
    auto K = [&](auto &x) { return pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1)); };
    iota(all(s), 0);
    sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
    for (int qi : s) rep(end,0,2) {
        int &a = pos[end], b = Q[qi][end], i = 0;
        auto step = [&](int c){
            if (in[c]) del(a, end), in[a] = 0;
            else add(c, end), in[c] = 1;
            a = c;};
        while (!(L[b] <= L[a] && R[a] <= R[b]))
            I[i++] = b, b = par[b];
        while (a != b) step(par[a]);
        while (i--) step(I[i]);
        if (end) res[qi] = calc();
    }
    return res;
};