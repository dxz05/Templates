vector<int> hashPrimes{873169819,1055926153,950843791,1074528047,804315977,831503311,819252547,1057023787,905366771,1021284727,889546787,1009837481,879310469,935039201,818474201,914475227,999946879,856160233,888580471,954226561,984217369,1049668597,914179237,1004636111,971418649,899583991,1066185467,956808847,1026272899,826972813,967967239,947477549,918732161,1095762743,1070486387,849964261,1017823537,827996413,989045339,863732159,901218847,806038021,834451643,867110903,800842897,1004594663,849112391,845251999,997198409,804336581,946065293,810904807,1077127637,965212321,825195013,1001700361,893902411,1016871533,811606459,800360369,955034749,1031399371,956506883,1075780091,923010577,1044112343,1061301433,1018608403,921659393,860730473,942503687,1071486457,804633463,1012589429,850435909,1082770061,932062489,888228023,950682973,921507571,998351059,981804269,1024925659,848553577,831330671,987704693,818805899,984016637,900536723,986062307,1015435679,1015276643,887797709,840140227,906100277,1005648487,949288733,1039363727,880800649,920727523};
const int K = 50;
int hashBase[K], hashMod[K];
vector<int> modPow[K];

void assignHashes(){
    mt19937 rngHash(chrono::high_resolution_clock::now().time_since_epoch().count());
    for (int i = 0; i < K; i++){
        int j = rngHash() % (int)hashPrimes.size();
        hashMod[i] = hashPrimes[j];
        hashBase[i] = rngHash() % (hashMod[i] - 3) + 2;
        modPow[i] = {1};
    }
}

struct __hash{
    array<vector<int>, K> h;

    inline void init(const vector<int> &a){
        if (hashBase[0] == 0){
            assignHashes();
        }

        int n = (int)a.size();
        for (int j = 0; j < K; j++){
            h[j].resize(n);

            int sz = (int) modPow[j].size();
            if (sz <= n) {
                modPow[j].resize(n + 1);
                for (int i = sz; i <= n; i++){
                    modPow[j][i] = (long long) modPow[j][i - 1] * hashBase[j] % hashMod[j];
                }
            }
        }

        for (int j = 0; j < K; j++) {
            for (int i = 0; i < n; i++) {
                h[j][i] = a[i] % hashMod[j];
                if (i > 0) h[j][i] = ((long long) h[j][i - 1] * hashBase[j] + h[j][i]) % hashMod[j];
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
            res -= (long long) modPow[j][r - l + 1] * h[j][l - 1] % hashMod[j];
            if (res < 0) res += hashMod[j];
        }
        return res;
    }

    inline array<int, K> get(int l, int r){
        array<int, K> res{};
        for (int j = 0; j < K; j++) res[j] = get(j, l, r);
        return res;
    }

};
