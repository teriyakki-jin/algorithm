#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector <int> v;
int digit_sum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

bool noduplicate(int a, int b) {
    map<int, bool> map;
    if (a < 100 && a % 10 == 0) {
        return false;
    }
    for (int i = a; i > 0; i /= 10) {
        if (map.find(i % 10) != map.end()) {
            return false;
        }
        else {
            map.insert({ i % 10,true });
        }
    }
    for (int i = b; i > 0; i /= 10) {
        if (map.find(i % 10) != map.end()) {
            return false;
        }
        else {
            map.insert({ i % 10,true });
        }
    }
    return true;
}

int main() {
    int num;
    cin >> num;
    int max_sum = 0;
    int max_a = 0, max_b = 0;
    for (int i = 10; i <= num / 2; i++) {
        int a = i;
        int b = num - i;
        if (a < 100 && b < 100) continue;
        int sum = 0;
        if (noduplicate(a, b)) {
            sum = digit_sum(a) + digit_sum(b);
            if (sum > max_sum) {
                max_sum = sum;
                max_a = a;
                max_b = b;
            }
        }
        else continue;
    }
    if (max_sum == 0) {
        cout << -1 << '\n';
    }
    else {
        if (max_a < 100) cout << 0;
        cout << max_a << ' ' << max_b << ' ' << max_sum << '\n';
    }

    return 0;
}