struct bits{
    int n, k; // size and block_count
    unsigned long long *b;
    int cnt; // count of set bits

    void init(int _n){
        n = _n;
        k = (n + 63) / 64;
        cnt = 0;
        b = (unsigned long long *) calloc(k, sizeof(unsigned long long));
    }

    bits(){};

    bits(int _n){
        init(_n);
    }

    void set(int i){
        assert(0 <= i && i < n);
        if (!((b[i / 64] >> (i % 64)) & 1)){
            cnt++;
            b[i / 64] |= (1ull << (i % 64));
        }
    }

    void reset(int i){
        assert(0 <= i && i < n);
        if ((b[i / 64] >> (i % 64)) & 1){
            cnt--;
            b[i / 64] &= ULLONG_MAX ^ (1ull << (i % 64));
        }
    }

    void flip(int i){
        assert(0 <= i && i < n);
        if ((b[i / 64] >> (i % 64)) & 1){
            reset(i);
        } else {
            set(i);
        }
    }

    void set(){
        cnt = n;
        for (int i = 0; i + 1 < k; i++) b[i] = ULLONG_MAX;
        b[k - 1] = (1ull << (n % 64)) - 1;
    }

    void reset(){
        cnt = 0;
        for (int i = 0; i < k; i++) b[i] = 0;
    }

    void flip(){
        cnt = n - cnt;
        for (int i = 0; i + 1 < k; i++) b[i] ^= ULLONG_MAX;
        b[k - 1] ^= (1ull << (n % 64)) - 1;
    }

    bool test(int i) const{
        assert(0 <= i && i < n);
        return (b[i / 64] >> (i % 64)) & 1;
    }

    int count() const{
        return cnt;
    }

    bool any_of() const{
        return cnt > 0;
    }

    bool none_of() const{
        return cnt == 0;
    }

    bool all_of() const{
        return cnt == n;
    }

    int find_first(){
        if (cnt == 0) return n;
        int i = 0;
        while (i < k && b[i] == 0) i++;
        return i * 64 + __builtin_ctzll(b[i]);
    }

    int find_next(int i){ // first set bit >= i
        int j = i / 64;
        unsigned long long val = b[j];
        val &= ULLONG_MAX ^ ((1ull << (i % 64)) - 1);
        if (val != 0) return j * 64 + __builtin_ctzll(val);

        j++;
        while (j < k && b[j] == 0) j++;

        if (j == k) return n;
        return j * 64 + __builtin_ctzll(b[j]);
    }

    bits operator|= (const bits &other){
        assert(n == other.n);
        cnt = 0;
        for (int i = 0; i < k; i++){
            this->b[i] |= other.b[i];
            cnt += __builtin_popcountll(this->b[i]);
        }
        return *this;
    }

    bits operator| (const bits &other){
        bits res = *this;
        res |= other;
        return res;
    }

    bits operator&= (const bits &other){
        assert(n == other.n);
        cnt = 0;
        for (int i = 0; i < k; i++){
            this->b[i] &= other.b[i];
            cnt += __builtin_popcountll(this->b[i]);
        }
        return *this;
    }

    bits operator& (const bits &other){
        bits res = *this;
        res &= other;
        return res;
    }

    bits operator^= (const bits &other){
        assert(n == other.n);
        cnt = 0;
        for (int i = 0; i < k; i++){
            this->b[i] ^= other.b[i];
            cnt += __builtin_popcountll(this->b[i]);
        }
        return *this;
    }

    bits operator^ (const bits &other){
        bits res = *this;
        res ^= other;
        return res;
    }

    bits operator>> (const int t){
        bits res(n);
        for (int i = t; i < n; i++){
            if (test(i)) res.set(i - t);
        }
        return res;
    }

    bits operator>>= (const int t){
        *this = *this >> t;
        return *this;
    }

    bits operator<< (const int t){
        bits res(n);
        for (int i = 0; i + t < n; i++){
            if (test(i)) res.set(i + t);
        }
        return res;
    }

    bits operator<<= (const int t){
        *this = *this << t;
        return *this;
    }

};
