template<typename T>
struct MergeSortTree{
    int size = 1;
    vector<vector<T>> tree;

    inline void merge(vector<T> &t, const vector<T> &foo, const vector<T> &hoo){
        int n = (int)foo.size(), m = (int)hoo.size();
        int i = 0, j = 0;
        t.reserve(n + m);

        while (i < n || j < m){
            if (i < n && (j == m || foo[i] < hoo[j])){
                t.push_back(foo[i]);
                i++;
            } else {
                t.push_back(hoo[j]);
                j++;
            }
        }
    }

    inline void build(int v, int tl, int tr, const vector<T> &a){
        if (tl == tr){
            tree[v] = vector<T>{a[tl]};
            return;
        }
        int tm = (tl + tr) >> 1;
        build(v << 1, tl, tm, a);
        build(v << 1 | 1, tm + 1, tr, a);
        merge(tree[v], tree[v << 1], tree[v << 1 | 1]);
    }

    inline void init(const vector<T> &a){
        size = a.size();
        tree.assign(4 * size + 2, vector<T>());
        build(1, 0, size - 1, a);
    }

    inline int binsearch(int v, T val, const string &type){
        if (type == "<=") { // count of tree[v][i] <= val
            return upper_bound(tree[v].begin(), tree[v].end(), val) - tree[v].begin();
        }
        if (type == "<") { // count of tree[v][i] < val
            return lower_bound(tree[v].begin(), tree[v].end(), val) - tree[v].begin();
        }
        if (type == ">=") { // count of tree[v][i] >= val
            return tree[v].end() - lower_bound(tree[v].begin(), tree[v].end(), val);
        }
        if (type == ">") { // count of tree[v][i] > val
            return tree[v].end() - upper_bound(tree[v].begin(), tree[v].end(), val);
        }
        assert(false);
        return -1;
    }

    inline int get(int v, int tl, int tr, int l, int r, T val, const string &type){
        if (l <= tl && tr <= r){
            return binsearch(v, val, type);
        }
        if (tl > r || tr < l) return 0;
        int tm = (tl + tr) >> 1;
        return get(v << 1, tl, tm, l, r, val, type) + get(v << 1 | 1, tm + 1, tr, l, r, val, type);
    }

    inline int get(int l, int r, T val, const string &type){
        return get(1, 0, size - 1, l, r, val, type);
    }
};
