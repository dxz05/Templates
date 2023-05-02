struct __hash{
    int A, B;
    __hash(){
        A = 998376389;
        B = 1000678447;
    }

    vector<int> h;
    vector<int> pw;

    inline void init(const vector<int> &a){
        int n = (int)a.size();
        h.resize(n);
        pw.resize(n + 1);

        pw[0] = 1;
        for (int i = 1; i <= n; i++) pw[i] = (long long) pw[i - 1] * A % B;

        for (int i = 0; i < n; i++){
            h[i] = a[i] % B;
            if (i > 0) h[i] = ((long long) h[i - 1] * A + h[i]) % B;
        }
    }
    
    inline void init(const string &s){
        int n = (int)s.size();
        vector<int> a(n);
        for (int i = 0; i < n; i++) a[i] = (int)s[i];
        init(a);
    }

    inline int get(int l, int r){
        assert(l <= r);
        int res = h[r];
        if (l > 0){
            res -= (long long) pw[r - l + 1] * h[l - 1] % B;
            if (res < 0) res += B;
        }
        return res;
    }

    inline bool same(int l1, int r1, int l2, int r2){
        return get(l1, r1) == get(l2, r2);
    }

};
