// source: https://github.com/the-tourist/algo/blob/master/data/sparsetable.cpp

// usage:
//   auto fun = [&](int i, int j) { return min(i, j); };
//   SparseTable<int, decltype(fun)> st(a, fun);
// or:
//   SparseTable<int> st(a, [&](int i, int j) { return min(i, j); });

template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable{
    int n;
    vector<vector<T>> table;
    F func;

    SparseTable(const vector<T> &a, const F& f){
        n = (int)a.size();
        func = f;

        int _sz = 31 - __builtin_clz(n) + 1;

        table.assign(_sz, vector<T>(n));

        table[0] = a;
        for (int j = 1; j < _sz; j++){
            for (int i = 0; i < n; i++){
                if (i + (1 << j) - 1 >= n) continue;
                table[j][i] = func(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }

    }

    T get(int l, int r){
        assert(0 <= l && l <= r && r < n);
        int x = 31 - __builtin_clz(r - l + 1);
        return func(table[x][l], table[x][r - (1 << x) + 1]);
    }

};

/*
vector<int> a = {1, 2, 5, 3, 4};

SparseTable<int> st(a, [&](int i, int j){ return max(i, j); });

*/
