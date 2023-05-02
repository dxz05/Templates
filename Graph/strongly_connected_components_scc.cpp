vector<int> get_scc(const vector<vector<int>> &g){
    int n = (int)g.size();
    vector<vector<int>> gr(n);

    for (int i = 0; i < n; i++){
        for (int j : g[i]) gr[j].push_back(i);
    }

    vector<bool> used;
    vector<int> order;
    function<void(int)> dfs1 = [&](int v){
        used[v] = true;
        for (int u : g[v]){
            if (!used[u]) dfs1(u);
        }
        order.push_back(v);
    };

    used.assign(n, false);
    for (int i = 0; i < n; i++){
        if (!used[i]) dfs1(i);
    }

    vector<int> f(n, -1);
    function<void(int, int)> dfs2 = [&](int v, int x){
        used[v] = true;
        f[v] = x;
        for (int u : gr[v]){
            if (!used[u]) dfs2(u, x);
        }
    };

    reverse(order.begin(), order.end());

    used.assign(n, false);

    int x = 0;
    for (int i : order){
        if (!used[i]){
            dfs2(i, x);
            x++;
        }
    }

    return f;
}
