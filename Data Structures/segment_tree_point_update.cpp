template <typename T>
struct SegmentTree{
    int n = 0;
    vector<T> tree;
    
    T neutral_element = numeric_limits<T>().max(); // e.g. 0 for sum, INF for min ...
    
    SegmentTree(){};
    SegmentTree(int _n){
        n = _n;
        tree.assign(n * 4 + 5, neutral_element);
    }

    inline T combine(T lf, T rg){
        return min(lf, rg); // change it
    }

    inline void build(int v, int tl, int tr, const vector<T> &a){
        if (tl == tr){
            tree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build(v << 1, tl, tm, a);
        build(v << 1 | 1, tm + 1, tr, a);
        tree[v] = combine(tree[v << 1], tree[v << 1 | 1]);
    }

    inline void init(const vector<T> &a){
        n = (int)a.size();
        tree.assign(n * 4 + 5, neutral_element);
        build(1, 0, n - 1, a);
    }

    inline void update(int v, int tl, int tr, int pos, T val){
        if (tl == tr){
            tree[v] = val; // pay attention!
            return;
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm){
            update(v << 1, tl, tm, pos, val);
        } else {
            update(v << 1 | 1, tm + 1, tr, pos, val);
        }
        tree[v] = combine(tree[v << 1], tree[v << 1 | 1]);
    }

    inline void update(int pos, T val){
        update(1, 0, n - 1, pos, val);
    }

    inline T get(int v, int tl, int tr, int l, int r){
        if (l <= tl && tr <= r) return tree[v];
        if (tl > r || tr < l) return neutral_element;
        int tm = (tl + tr) >> 1;
        return combine(get(v << 1, tl, tm, l, r), get(v << 1 | 1, tm + 1, tr, l, r));
    }

    inline T get(int l, int r){
        return get(1, 0, n - 1, l, r);
    }   
    
};

/* in case of debugging:

inline void out(int v, int tl, int tr){
    if (tl == tr){
        cout << tree[v] << ' ';
        return;
    }
    int tm = (tl + tr) >> 1;
    out(v << 1, tl, tm);
    out(v << 1 | 1, tm + 1, tr);
}

inline void out(){
    out(1, 0, n - 1);
    cout << endl;
}

*/
