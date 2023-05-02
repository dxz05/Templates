struct ReachabilityTree {
    vector<int> p, sz;
    vector<vector<int>> g;
    int id;

    vector<int> tin, tout;
    int timer;

    ReachabilityTree(int n) {
        n++;

        int m = 2 * n + 10;

        id = n + 1;
        p.assign(m, 0);
        sz.assign(m, 1);
        g.resize(m);
        iota(p.begin(), p.end(), 0);

        tin.resize(m);
        tout.resize(m);
        timer = 0;
    }

    inline int find(int x) {
        return (x == p[x] ? x : p[x] = find(p[x]));
    }

    inline bool same(int x, int y) {
        return find(x) == find(y);
    }

    inline bool unite(int x, int y) {
        if (same(x, y)) return false;
        x = find(x);
        y = find(y);
        if (sz[x] > sz[y]) swap(x, y);

        p[x] = id;
        p[y] = id;
        sz[id] += sz[x] + sz[y];
        g[id].push_back(x);
        g[id].push_back(y);

        id++;

        return true;
    }

    void dfs(int v){
        tin[v] = tout[v] = timer++;
        for (int u : g[v]){
            dfs(u);
            tout[v] = tout[u];
        }
    }

    void run_dfs(){
        for (int i = 0; i < g.size(); i++){
            if (find(i) == i) dfs(i);
        }
    }

};
