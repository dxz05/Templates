struct dsu{
    vector<int> p, sz;

    dsu(int n){
        n++;
        p.assign(n, 0);
        sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    inline int leader(int x){
        return (x == p[x] ? x : p[x] = leader(p[x]));
    }

    inline bool same(int x, int y){
        return leader(x) == leader(y);
    }

    inline bool unite(int x, int y){
        if (same(x, y)) return false;
        x = leader(x);
        y = leader(y);
        if (sz[x] > sz[y]) swap(x, y);
        p[x] = y;
        sz[y] += sz[x];

        return true;
    }

    inline int get_size(int x){
        return sz[leader(x)];
    }

};
