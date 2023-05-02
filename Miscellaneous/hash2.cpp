struct __hash2{
    int A[2], B[2];
    __hash2(){
        A[0] = 998376389;
        A[1] = 998244853;
        B[0] = 1000678447;
        B[1] = 1000000009;
    }

    vector<int> h[2];
    vector<int> pw[2];

    inline void init(const vector<int> &a){
        int n = (int)a.size();
        for (int j = 0; j < 2; j++){
            h[j].resize(n);
            pw[j].resize(n + 1);
        }

        for (int j = 0; j < 2; j++){
            pw[j][0] = 1;
            for (int i = 1; i <= n; i++) pw[j][i] = (long long) pw[j][i - 1] * A[j] % B[j];
        }

        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < n; i++) {
                h[j][i] = a[i] % B[j];
                if (i > 0) h[j][i] = ((long long) h[j][i - 1] * A[j] + h[j][i]) % B[j];
            }
        }
    }
    
    inline void init(const string &s){
        int n = (int)s.size();
        vector<int> a(n);
        for (int i = 0; i < n; i++) a[i] = (int)s[i];
        init(a);
    }

    inline int get(int j, int l, int r){
        assert(l <= r);
        int res = h[j][r];
        if (l > 0){
            res -= (long long) pw[j][r - l + 1] * h[j][l - 1] % B[j];
            if (res < 0) res += B[j];
        }
        return res;
    }

    inline pair<int, int> get(int l, int r){
        return make_pair(get(0, l, r), get(1, l, r));
    }

    inline bool same(int l1, int r1, int l2, int r2){
        return get(l1, r1) == get(l2, r2);
    }

};
