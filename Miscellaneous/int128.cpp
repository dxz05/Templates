using i128 = __int128;
std::ostream& operator<<(std::ostream& os, __int128 t) {
    bool neg = (t < 0);
    if (t < 0) t *= -1;

    string str;
    while (t > 0){
        str += char(t % 10 + '0');
        t /= 10;
    }
    reverse(str.begin(), str.end());
    if (str.empty()) str = "0";
    if (neg) str = "-" + str;

    return os << str;
}
