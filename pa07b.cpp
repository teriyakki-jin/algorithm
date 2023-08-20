#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#define NO_OF_CHARS 256
using namespace std;

//BM
int BM(string pattern, string str) {
    int count = 0;
    int j; //pp;
    int i; //pt;
    int n = str.length();
    int m = pattern.length();
    int skip[NO_OF_CHARS];

    for (i = 0; i < NO_OF_CHARS; i++) skip[i] = m;
    for (i = 0; i < m - 1; i++) skip[pattern[i]] = m - i - 1;


    while (i < n) {
        j = m - 1;

        while ((++count) && (str[i] == pattern[j])) {
            if (j == 0) return count;
            j--;
            i--;
        }
        i += (skip[str[i]] > m - j) ? skip[str[i]] : m - j;
    }
    return -1;
}

//KMP
vector<int> Preprocessing(string pattern) {
    int m = pattern.length();
    vector<int> SP(m);

    SP[0] = 0;
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = SP[j - 1];
        if (pattern[j] == pattern[i]) {
            SP[i] = ++j;
        }
    }
    return SP;
}

int KMP(string pattern, string str) {
    int count = 0;
    int m = pattern.length();
    int n = str.length();
    vector<int> SP = Preprocessing(pattern);

    int i = 1, j = 0;
    for (i = 0; i < n; i++) {
        while ((j > 0) && (str[i] != pattern[j])) {
            j = SP[j - 1];
            count++;
        }
        count++;
        if (pattern[j] == str[i]) {
            if (j == m - 1) {
                j = SP[j];
                break;
            }
            else j++;
        }
    }
    return count;
}

//RK
bool isEqual(string& pattern, string substr) {
    for (int i = 0; i < pattern.length(); i++) {
        if (pattern[i] != substr[i])
            return false;
    }
    return true;
}

int RabinKarp(string& pattern, string& str, int d, int q) {
    int m = pattern.length();
    int p = 0, b1 = 0;
    int count = 0;
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        b1 = (d * b1 + str[i]) % q;
    }
    int h = static_cast<int>(pow(d, m - 1)) % q;
    int bi = b1, bi_1 = b1;
    for (int i = 0; i < str.length() - m + 1; i++) {
        if (i != 0)
            bi = static_cast<int>((d * (bi_1 - h * str[i - 1]) + str[i + m - 1])) % q;
        if (bi < 0)
            bi += q;
        if (p == bi) {
            count += m;
            if (isEqual(pattern, str.substr(i, m))) {
                return count + i + 1;
            }
        }
        bi_1 = bi;
    }
}


int main()
{
    string pattern;
    string str;
    int num_of_pat, num_of_str;
    int RKnum, KMPnum, BMnum;
    cin >> num_of_pat;
    for (int i = 0; i < num_of_pat; i++) {
        string input;
        cin >> input;
        pattern += input;
    }
    cin >> num_of_str;
    for (int i = 0; i < num_of_str; i++) {
        string input;
        cin >> input;
        str += input;
    }

    vector<int> result;
    RKnum = RabinKarp(pattern, str, 2, 30011);
    result.push_back(RKnum);

    KMPnum = KMP(pattern, str);
    result.push_back(KMPnum);

    BMnum = BM(pattern, str);
    //cout << "BM : " << BMnum << endl;
    result.push_back(BMnum);
    cout << RKnum << " " << KMPnum << " " << BMnum << endl;
    int maxval = max(RKnum, max(KMPnum, BMnum));
    int minval = min(RKnum, min(KMPnum, BMnum));

    if (RKnum == minval) {
        if (KMPnum == minval || BMnum == minval) {
            if (KMPnum == minval) {
                cout << "0 0 3";
                return 0;
            }
        }
        else {
            if (KMPnum == BMnum) {
                cout << "1 0 0";
            }
            else {
                if (KMPnum == maxval) {
                    cout << "1 3 2";
                }
                else cout << "1 2 3";
            }
        }
    }
    else if (KMPnum == minval) {
        if (BMnum == minval) {
            cout << "0 0 1";
            return 0;
        }
        else {
            if (BMnum == RKnum) {
                cout << "2 0 0";
            }
            else {
                if (BMnum == maxval)
                    cout << "2 1 3";
                else cout << "2 3 1";
            }
        }
    }
    else {
        if (KMPnum == RKnum) {
            cout << "3 0 0";
        }
        else {
            if (KMPnum == maxval) {
                cout << "3 1 2";
            }
            else cout << "3 2 1";
        }
    }

    return 0;
}
