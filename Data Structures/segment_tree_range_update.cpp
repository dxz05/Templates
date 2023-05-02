template <typename T>
struct SegmentTree{
    struct node{
        T val;
        T lazy;
        bool isUpdated;
        node(){
            // do something
            isUpdated = false;
        };
        node(T x){
            val = x;
            isUpdated = false;
        }
    };

    vector<node> tree;

    node neutral_element = node(numeric_limits<T>().max()); // e.g. 0 for sum, INF for min ...;

    inline void combine(node &par, node lf, node rg){
        // do something
    }

    int _begin, _end;

    inline void init(int n){
        _begin = 0;
        _end = n - 1;
        tree.resize(n * 4 + 5);
    }

    inline void upd(int v, int tl, int tr, T lazy){
        // do something
        tree[v].isUpdated = true;
    }

    inline void push(int v, int tl, int tr){
        if (tl == tr || !tree[v].isUpdated) return;
    
        int tm = (tl + tr) >> 1;
        upd(v << 1, tl, tm, tree[v].lazy);
        upd(v << 1 | 1, tm + 1, tr, tree[v].lazy);

        // do something
        tree[v].isUpdated = false;
    }

    inline void update(int v, int tl, int tr, int l, int r, T val){
        push(v, tl, tr);
        if (l <= tl && tr <= r){
            upd(v, tl, tr, val);
            return;
        }
        if (tl > r || tr < l) return;

        int tm = (tl + tr) >> 1;
        update(v << 1, tl, tm, l, r, val);
        update(v << 1 | 1, tm + 1, tr, l, r, val);

        combine(tree[v], tree[v << 1], tree[v << 1 | 1]);
    }

    inline void update(int l, int r, T val){
        update(1, _begin, _end, l, r, val);
    }

    inline node get(int v, int tl, int tr, int l, int r){
        push(v, tl, tr);
        if (l <= tl && tr <= r) return tree[v];
        if (tl > r || tr < l) return neutral_element;
        int tm = (tl + tr) >> 1;
        node res;
        combine(res, get(v << 1, tl, tm, l, r), get(v << 1 | 1, tm + 1, tr, l, r));
        return res;
    }

    inline node get(int l, int r){
        return get(1, _begin, _end, l, r);
    }

};
