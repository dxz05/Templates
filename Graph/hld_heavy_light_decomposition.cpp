template<typename T>
struct HeavyLightDecomposition {
    vector<int> sub, tin, tout, proot, id;
    vector<vector<int>> up;
    int timer;

    void dfs0(int v, int p, const vector<vector<int>> &g) {
        sub[v] = 1;
        tin[v] = tout[v] = timer++;

        up[v][0] = p;
        for (int i = 1; i < (int)up[v].size(); i++) {
            if (up[v][i - 1] != -1) {
                up[v][i] = up[up[v][i - 1]][i - 1];
            }
        }

        for (int c : g[v]) {
            if (c != p) {
                dfs0(c, v, g);
                sub[v] += sub[c];
                tout[v] = tout[c];
            }
        }
    }

    void dfs1(int v, int p, const vector<vector<int>> &g) {
        id[v] = timer++;
        if (p == -1) proot[v] = v;

        int big = -1;
        for (int c: g[v]) {
            if (c == p) continue;
            if (big == -1 || sub[c] > sub[big]) big = c;
        }

        if (big != -1) {
            proot[big] = proot[v];
            dfs1(big, v, g);
        }

        for (int c: g[v]) {
            if (c == p || c == big) continue;
            proot[c] = c;
            dfs1(c, v, g);
        }
    }

    bool upper(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v) {
        if (upper(u, v)) return u;
        if (upper(v, u)) return v;
        for (int i = (int)up[u].size() - 1; i >= 0; i--) {
            if (up[u][i] != -1 && !upper(up[u][i], v)) u = up[u][i];
        }
        return up[u][0];
    }

    SegmentTree<T> st;

    T get_to_par(int v, int p) {
        T res = INT_MIN;
        while (true) {
            int x = proot[v];
            if (proot[p] == x) {
                res = max(res, st.get(id[p], id[v]));
                break;
            } else {
                res = max(res, st.get(id[x], id[v]));
                v = up[x][0];
            }
        }
        return res;
    }

    T get(int u, int v) {
        int p = lca(u, v);
        return max(get_to_par(u, p), get_to_par(v, p));
    }

    void update(int v, T val){
        st.update(id[v], val);
    }

    void init(const vector<vector<int>> &g, const vector<T> &a){
        int n = (int)a.size();
        int LG = 31 - __builtin_clz(n) + 1;
        sub.resize(n);
        tin.resize(n);
        tout.resize(n);
        proot.resize(n);
        id.resize(n);
        up.assign(n, vector<int>(LG, -1));

        timer = 0;
        dfs0(0, 0, g);

        timer = 0;
        dfs1(0, 0, g);

        st.init(n);
        for (int i = 0; i < n; i++){
            st.update(id[i], a[i]);
        }
    }

};
