template<typename T>
struct fenwick2D{
    vector<vector<T>> f;
    fenwick2D(int n, int m){
        f.assign(n + 2, vector<T>(m + 2));
    }
    fenwick2D(){};
    void init(int n, int m){
        f.assign(n + 2, vector<T>(m + 2));
    }

    void add(int i, int j, T val){
        i++, j++;

        int _j = j;
        while (i < (int)f.size()){
            j = _j;
            while (j < (int)f[i].size()){
                f[i][j] += val;
                j += -j & j;
            }
            i += -i & i;
        }
    }

    T get(int i, int j){
        i++, j++;
        int _j = j;

        T res = 0;
        while (i > 0){
            j = _j;
            while (j > 0){
                res += f[i][j];
                j -= -j & j;
            }
            i -= -i & i;
        }

        return res;
    }

    T get(int i1, int j1, int i2, int j2){ /// a[i1 .. i2][j1 .. j2]
        T res = 0;
        res += get(i2, j2);
        res -= get(i1 - 1, j2);
        res -= get(i2, j1 - 1);
        res += get(i1 - 1, j1 - 1);
        return res;
    }

};
