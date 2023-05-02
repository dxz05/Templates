template<typename T>
struct SparseTable{
    vector<vector<T>> mn, mx;

    void init(const vector<T> &a){
        int n = (int)a.size();
        int _sz = 31 - __builtin_clz(n) + 1;

        mn.assign(_sz, vector<T>(n));
        mx.assign(_sz, vector<T>(n));

        for (int i = 0; i < n; i++){
            mn[0][i] = mx[0][i] = a[i];
        }

        for (int j = 1; j < _sz; j++){
            for (int i = 0; i < n; i++){
                if (i + (1 << j) - 1 >= n) continue;
                mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
                mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
            }
        }

    }
    SparseTable(){};
    SparseTable(const vector<T> &a){
        init(a);
    }

    T get_min(int l, int r){
        assert(l <= r);
        int x = 31 - __builtin_clz(r - l + 1);
        return min(mn[x][l], mn[x][r - (1 << x) + 1]);
    }

    T get_max(int l, int r){
        assert(l <= r);
        int x = 31 - __builtin_clz(r - l + 1);
        return max(mx[x][l], mx[x][r - (1 << x) + 1]);
    }

};
