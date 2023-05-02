struct SuffixArray{
    string text;
    vector<int> p, c, adj_lcp;
    vector<vector<int>> table;

    void build_lcp(){
        int n = (int)p.size();

        adj_lcp.assign(n, 0);
        int k = 0;
        for (int i = 0; i < n - 1; i++){
            int pi = c[i];
            int j = p[pi - 1];
            while (max(i + k, j + k) < n && text[i + k] == text[j + k]) k++;
            adj_lcp[pi] = k;
            k = max(k - 1, 0);
        }

        int _sz = 31 - __builtin_clz(n) + 1;

        table.assign(_sz, vector<int>(n));

        for (int i = 0; i < n; i++){
            table[0][i] = adj_lcp[i];
        }

        for (int j = 1; j < _sz; j++){
            for (int i = 0; i < n; i++){
                if (i + (1 << j) - 1 >= n) continue;
                table[j][i] = min(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    void init(string s){
        s += "$";

        text = s;

        int n = (int)s.size();
        p.assign(n, 0);
        c.assign(n, 0);
        iota(p.begin(), p.end(), 0);

        sort(p.begin(), p.end(), [&](int i, int j){
            return s[i] < s[j];
        });

        c[p[0]] = 0;
        for (int i = 1; i < n; i++){
            c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
        }

        int h = 0;
        while ((1 << h) < n){
            for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << h) + n) % n;

            vector<int> pos(n);
            for (int i = 0; i < n; i++){
                if (c[i] + 1 < n) pos[c[i] + 1]++;
            }
            for (int i = 1; i < n; i++) pos[i] += pos[i - 1];

            vector<int> p_new(n);
            for (int i : p){
                int x = c[i];
                p_new[pos[x]] = i;
                pos[x]++;
            }

            swap(p, p_new);

            vector<int> c_new(n);
            c_new[p[0]] = 0;
            for (int i = 1; i < n; i++){
                pair<int, int> now = make_pair(c[p[i]], c[(p[i] + (1 << h)) % n]);
                pair<int, int> prv = make_pair(c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]);
                c_new[p[i]] = c_new[p[i - 1]] + (now != prv);
            }
            swap(c, c_new);
            h++;
        }

//        build_lcp();
    }

    void out(){
        for (int i = 0; i < text.size(); i++){
            cout << p[i] << ' ' << text.substr(p[i], text.size() - p[i]) << endl;
        }
    }

    int lcp(int i, int j){
        if (i == j) return (int)p.size() - i - 1;
        i = c[i], j = c[j];
        if (i > j) swap(i, j);
        i++;
        int x = 31 - __builtin_clz(j - i + 1);
        return min(table[x][i], table[x][j - (1 << x) + 1]);
    }

    SuffixArray(){};
    SuffixArray(string s){
        init(s);
    }

    int compare(int l1, int r1, int l2, int r2) {
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
        int x = lcp(l1, l2);
        if (len1 <= x && len2 <= x){
            return (len1 < len2 ? -1 : len1 == len2 ? 0 : 1);
        }
        if (len1 <= x) return -1;
        if (len2 <= x) return 1;
        return l1 + x == text.size() || text[l1 + x] < text[l2 + x] ? -1 : 1;
    }
};
