vector<int> z_function(const string &s){
    int n = (int)s.size();
    vector<int> z(n, 0);

    int l = 0, r = 0;
    for (int i = 1; i < n; i++){
        if (i <= r){
            z[i] = min(z[i - l], r - i + 1);
        }

        while (z[i] + i < n && s[z[i] + i] == s[z[i]]){
            z[i]++;
        }

        if (z[i] + i - 1 > r){
            l = i;
            r = z[i] + i - 1;
        }
    }

    return z;
}
