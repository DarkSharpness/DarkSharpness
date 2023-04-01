#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

const int MaxN = 500000, MaxM = 500000;

struct graph_t {
  int cnte;
  int head[MaxN + 5], to[MaxM * 2 + 5], next[MaxM * 2 + 5];

  graph_t() { cnte = 1; }

  inline void addEdge(int u, int v) {
    cnte++; to[cnte] = v;
    next[cnte] = head[u]; head[u] = cnte;
  }
};

struct union_find {
  int par[MaxN + 5];
  union_find() { memset(par, -1, sizeof par); }

  int find(int x) { return par[x] < 0 ? x : par[x] = find(par[x]); }

  inline void merge(int u, int v) {
    int p = find(u), q = find(v);
    if (p == q) return;
    par[p] += par[q];
    par[q] = p;
  }
};

int N, M;
graph_t Gr;

class two_edge_connect {
private:
  int low[MaxN + 5], dfn[MaxN + 5], dfc;
  int stk[MaxN + 5], tp;
  int bel[MaxN + 5], s;

  void dfs(int u, int fe) {
    low[u] = dfn[u] = ++dfc;
    stk[++tp] = u;
    for (int i = Gr.head[u]; i; i = Gr.next[i]) {
      if ((i ^ fe) == 1) continue;
      int v = Gr.to[i];
      if (dfn[v] == 0) {
        dfs(v, i);
        low[u] = std::min(low[u], low[v]);
      } else
        low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
      s++;
      for (;;) {
        int v = stk[tp--];
        bel[v] = s;
        if (u == v) break;
      }
    }
  }

public:
  void init() {
    memset(dfn, 0, sizeof dfn);
    dfc = tp = s = 0;
    for (int i = 1; i <= N; ++i)
      if (dfn[i] == 0) dfs(i, 0);
  }

  inline bool isbridge(int u, int v) {
    return bel[u] != bel[v];
  }
};

class three_edge_connect {
private:
  two_edge_connect bcc;
  union_find uf;
  int low[MaxN + 5], dfn[MaxN + 5], end[MaxN + 5], dfc;
  int deg[MaxN + 5];

  inline bool insubtree(int u, int v) {
    if (dfn[u] <= dfn[v] && dfn[v] <= end[u]) return true;
    else return false;
  }

  inline void absorb(std::vector<int> &path, int u, int w = 0) {
    while (path.empty() == false) {
      int v = path.back();
      if (w > 0 && insubtree(v, w) == false) break;
      path.pop_back();
      deg[u] += deg[v] - 2;
      uf.merge(u, v);
    }
  }

  void dfs(int u, int fe, std::vector<int> &pu) {
    low[u] = dfn[u] = ++dfc;
    for (int i = Gr.head[u]; i; i = Gr.next[i]) {
      int v = Gr.to[i];
      if (u == v || bcc.isbridge(u, v) == true) continue;
      deg[u]++;
      if ((i ^ fe) == 1) continue;
      if (dfn[v] == 0) {
        std::vector<int> pv;
        dfs(v, i, pv);
        if (deg[v] == 2) pv.pop_back();
        if (low[v] < low[u]) {
          low[u] = low[v];
          absorb(pu, u);
          pu = pv;
        } else absorb(pv, u);
      } else {
        if (dfn[v] > dfn[u]) {
          absorb(pu, u, v);
          deg[u] -= 2;
        } else if (dfn[v] < low[u]) {
          low[u] = dfn[v];
          absorb(pu, u);
        }
      }
    }
    end[u] = dfc;
    pu.push_back(u);
  }

public:
  void init() {
    memset(dfn, 0, sizeof dfn);
    memset(deg, 0, sizeof deg);
    dfc = 0;
    bcc.init();
    for (int i = 1; i <= N; ++i) {
      if (dfn[i] == 0) {
        std::vector<int> pi;
        dfs(i, 0, pi);
      }
    }
  }

  std::vector< std::vector<int> > getall() {
    std::vector< std::vector<int> > res(N), ans;
    for (int i = 1; i <= N; ++i) {
      int x = uf.find(i);
      res[x - 1].push_back(i);
    }
    for (int i = 0; i < N; ++i)
      if (res[i].empty() == false) ans.push_back(res[i]);
    return ans;
  }
};

void init() {
  scanf("%d %d", &N, &M);
  for (int i = 1; i <= M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    Gr.addEdge(u, v);
    Gr.addEdge(v, u);
  }
}

inline bool cmp(const std::vector<int> &x, const std::vector<int> &y) { return x[0] < y[0]; }

void solve() {
  static three_edge_connect tcc;
  tcc.init();
  std::vector< std::vector<int> > ans = tcc.getall();
  for (int i = 0; i < (int) ans.size(); ++i)
    std::sort(ans[i].begin(), ans[i].end());
  std::sort(ans.begin(), ans.end(), cmp);
//   printf("%d\n", (int) ans.size());
  long long cnt = 0;
  for (int i = 0; i < (int) ans.size(); ++i) {
    long long s = ans[i].size();
    cnt += s * (s - 1) >> 1;
    // for (int j = 0; j < s; ++j)
    //   printf("%d%c", ans[i][j], " \n"[j == s - 1]);
  }
  printf("%lld",cnt);
}

int main() {
  init();
  solve();
  return 0;
}
