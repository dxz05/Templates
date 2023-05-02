template <typename T>
struct SegmentTree{
    int n;
    vector<T> tree;

    T combine(T lf, T rg){
        return max(lf, rg);
    }

    void init(int _n){
        n = _n;
        tree.resize(2 * n + 5);
    }
    void init(const vector<T> &a){
        init((int)a.size());
        for (int i = 0; i < n; i++) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
    }
    SegmentTree(){};
    SegmentTree(int _n) {
        init(_n);
    };
    SegmentTree(const vector<T> &a){
        init(a);
    };

    void update(int v, T val) {
        v += n;
        tree[v] = val;
        for (; v > 1; v >>= 1){
            tree[v >> 1] = combine(tree[v], tree[v ^ 1]);
        }
    }

    T get(int l, int r) {
        ++r;
        T res = INT_MAX; // do not forget to change res
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = combine(res, tree[l++]);
            if (r & 1) res = combine(res, tree[--r]);
        }
        return res;
    }
};
