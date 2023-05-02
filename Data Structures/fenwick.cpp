template<typename T>
struct fenwick{
    vector<T> f;
    fenwick(int n){
        f.resize(n + 2);
    }
    fenwick(){};
    void init(int n){
        f.resize(n + 2);
    }

    void add(int i, T val){
        i++;
        while (i < (int)f.size()){
            f[i] += val;
            i += -i & i;
        }
    }

    void add(int l, int r, T val){
        add(l, val);
        add(r + 1, -val);
    }

    T get(int i){
        i++;
        T res = 0;
        while (i > 0){
            res += f[i];
            i -= -i & i;
        }
        return res;
    }

    T get(int l, int r){
        if (l > r) return 0;
        return get(r) - get(l - 1);
    }
};
