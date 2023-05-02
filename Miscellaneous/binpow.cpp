long long binpow(long long n, long long k, long long mod = MOD){ // n^k % mod
    long long res = 1;
    while (k > 0){
        if (k & 1) res = res * n % mod;
        n = n * n % mod;
        k >>= 1;
    }
    return res;
}

vector<long long> fact, ifact;

void init_factorials(int MaxA){
    fact.resize(MaxA + 1);
    ifact.resize(MaxA + 1);

    fact[0] = 1;
    for (int i = 1; i <= MaxA; i++) fact[i] = fact[i - 1] * i % MOD;

    ifact[MaxA] = binpow(fact[MaxA], MOD - 2);
    for (int i = MaxA - 1; i >= 0; i--) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}

long long choose(int n, int k){
    if (k < 0 || n < k) return 0;
    return fact[n] * (ifact[k] * ifact[n - k] % MOD) % MOD;
}
