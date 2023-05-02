template <typename T>
struct PersistentSegmentTree{
    int n = 0;
    vector<T> tree;
    vector<int> lc, rc;
    int root;

    T neutral_element; // e.g. 0 for sum, INF for min

    inline T combine(T lf, T rg){
        // return something;
    }

    int next_free = 0;

    inline int get_next(){
        int v = ++next_free;
        if (tree.size() <= v) tree.resize(v + 1, neutral_element);
        if (lc.size() <= v) lc.resize(v + 1, -1);
        if (rc.size() <= v) rc.resize(v + 1, -1);
        return v;
    }

    inline int build(int tl, int tr){
        int v = get_next();
        if (tl == tr) return v;

        int tm = (tl + tr) >> 1;
        lc[v] = build(tl, tm);
        rc[v] = build(tm + 1, tr);
        tree[v] = combine(tree[lc[v]], tree[rc[v]]);

        return v;
    }

    inline void init(int _n){
        next_free = 1;
        n = _n;

        tree.resize(n * 25, neutral_element);
        lc.resize(n * 25, -1);
        rc.resize(n * 25, -1);

        root = build(0, n - 1);
    }

    inline int update(int p, int tl, int tr, int pos, T val){
        int v = get_next();
        if (tl == tr){
            tree[v] = combine(tree[p], val);
            return v;
        }

        int tm = (tl + tr) >> 1;
        if (pos <= tm){
            lc[v] = update(lc[p], tl, tm, pos, val);
            rc[v] = rc[p];
        } else {
            lc[v] = lc[p];
            rc[v] = update(rc[p], tm + 1, tr, pos, val);
        }
        tree[v] = combine(tree[lc[v]], tree[rc[v]]);

        return v;
    }

    inline int update(int pos, T val){
        root = update(root, 0, n - 1, pos, val);
        return root;
    }

    inline T get(int v, int tl, int tr, int l, int r){
        if (l <= tl && tr <= r) return tree[v];
        if (tl > r || tr < l) return neutral_element;
        int tm = (tl + tr) >> 1;
        return combine(get(lc[v], tl, tm, l, r), get(rc[v], tm + 1, tr, l, r));
    }

    inline T get(int x, int l, int r){
        return get(x, 0, n - 1, l, r);
    }

};
