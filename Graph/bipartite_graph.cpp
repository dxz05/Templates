struct bipartite_graph{
    int n, m;
    vector<vector<int>> g;

    void init(int _n, int _m){
        n = _n;
        m = _m;
        g.resize(n + m + 1);
    }

    void init(const vector<vector<int>> &_g){
        g = _g;
    }

    void add_edge(int u, int v){
        g[u].push_back(n + v);
        g[n + v].push_back(u);
    }

    vector<int> max_matching(){
        vector<int> mt(n + m, -1);

        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);

        sort(perm.begin(), perm.end(), [&](int i, int j){
            return g[i].size() < g[j].size();
        });

        for (int v : perm){
            for (int u : g[v]){
                if (mt[u] == -1){
                    mt[v] = u;
                    mt[u] = v;
                    break;
                }
            }
        }

        vector<bool> used;
        function<bool(int)> dfs = [&](int v){
            if (used[v]) return false;
            used[v] = true;
            for (int u : g[v]){
                if (mt[u] == -1 || dfs(mt[u])){
                    mt[u] = v;
                    mt[v] = u;
                    return true;
                }
            }
            return false;
        };

        for (int i = 0; i < n; i++){
            if (mt[i] != -1) continue;
            used.assign(n, false);
            dfs(i);
        }

        return mt;
    }

    int get_max_matching_size(){
        vector<int> mt = max_matching();
        int ans = 0;
        for (int i = 0; i < mt.size(); i++) ans += mt[i] != -1;
        return ans / 2;
    }

    vector<int> build(int flag){
        vector<int> mt = max_matching();

        vector<vector<int>> gg(n + m);
        for (int i = 0; i < n; i++){
            for (int j : g[i]){
                if (mt[i] == j && mt[j] == i){
                    gg[j].push_back(i);
                } else {
                    gg[i].push_back(j);
                }
            }
        }

        vector<bool> used(n + m, false);
        vector<int> type(n + m, 0);

        function<void(int)> dfs = [&](int v){
            used[v] = true;
            type[v] = (v < n ? 1 : 3);
            for (int u : gg[v]){
                if (!used[u]) dfs(u);
            }
        };

        for (int i = 0; i < n; i++){
            if (mt[i] == -1 && !used[i]) dfs(i);
        }

        vector<int> Lp, Lm, Rp, Rm;
        for (int i = 0; i < n + m; i++){
            if (type[i] == 0) type[i] = (i < n ? 2 : 4);
            if (type[i] == 1) Lp.push_back(i);
            if (type[i] == 2) Lm.push_back(i);
            if (type[i] == 3) Rp.push_back(i);
            if (type[i] == 4) Rm.push_back(i);
        }

        vector<int> res;
        if (flag == 1){ /// vertex cover
            for (int i : Lm) res.push_back(i);
            for (int i : Rp) res.push_back(i);
        } else { /// independent set
            for (int i : Lp) res.push_back(i);
            for (int i : Rm) res.push_back(i);
        }

        return res;
    }

    vector<int> min_vertex_cover(){
        return build(1);
    }

    vector<int> max_independent_set(){
        return build(2);
    }

};
