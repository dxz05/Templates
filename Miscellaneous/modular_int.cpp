struct Mint{
    int val;
    Mint(){
        val = 0;
    }
    Mint(ll _val){
        val = _val % MOD;
        if (val < 0) val += MOD;
    }
    Mint operator- () const{
        if (val == 0) return Mint(val);
        return Mint(MOD - val);
    }
    bool operator== (const Mint &x) const{
        return val == x.val;
    }
    bool operator!= (const Mint &x) const{
        return val != x.val;
    }

    Mint pow(long long k) const{
        Mint res = 1, num = val;
        while (k > 0){
            if (k & 1){
                res *= num;
                --k;
            } else {
                num *= num;
                k >>= 1;
            }
        }
        return res;
    }
    Mint inv() const{
        assert(val != 0);
        return pow(MOD - 2);
    }
    Mint &operator*= (const Mint &x){
        val = (long long)val * x.val % MOD;
        return *this;
    }
    Mint &operator+= (const Mint &x){
        val += x.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    Mint &operator-= (const Mint &x){
        val -= x.val;
        if (val < 0) val += MOD;
        return *this;
    }
    Mint &operator/= (const Mint &x){
        return *this *= x.inv();
    }
    friend Mint operator* (const Mint &x, const Mint &y){
        Mint res = x;
        res *= y;
        return res;
    }
    friend Mint operator+ (const Mint &x, const Mint &y){
        Mint res = x;
        res += y;
        return res;
    }
    friend Mint operator- (const Mint &x, const Mint &y){
        Mint res = x;
        res -= y;
        return res;
    }
    friend Mint operator/ (const Mint &x, const Mint &y){
        Mint res = x;
        res /= y;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Mint &x){
        int v;
        is >> v;
        x = Mint(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Mint &x){
        os << x.val;
        return os;
    }
};
