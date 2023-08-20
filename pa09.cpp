#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

struct Point {          // ��ǥ��ȣ�� cnt
    int x;
    int y;
    int cnt;
};

int shortestDistance;
vector<int> shortestOrder;

// �� ���� ������ ����ư �Ÿ��� ����ϴ� �Լ�
int manhattanDistance(const Point& p1, const Point& p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
// order �� ��ȿ�˻�
bool isValid(const vector<int>& order, const vector<Point>& orders) {
    int cnt = 0;
    for (int i = 0; i < order.size(); i++) {
        if (order[i] > 0)
            cnt++;
        else
            cnt--;
        if (cnt >= 3)   // ���濡 2���Ѱ� ���� ���°� ����
            return false;
    }
    vector<bool> visited(orders.size(), false);
    for (int i = 0; i < order.size(); i++) {
        int idx = order[i];
        if (idx > 0) {
            visited[idx - 1] = true;   
        }
        else if (idx < 0) {
            if (!visited[abs(idx) - 1]) {   // ���Ĺ����ʰ� ����ϴ°�� false
                return false;
            }
        }
    }
    return true;
}

void DeliveryOrder(vector<Point>& orders, vector<int>& order, vector<bool>& visited,
                    Point currLoca, int totalDistance) {
    if (!isValid(order, orders)) return;    // isvValid Ȯ��

    if (order.size() == orders.size()) {
        if (totalDistance < shortestDistance) {
         // ���� �ֹ� ������ �̵� �Ÿ��� �ִ� �Ÿ����� ������ �ִ� �Ÿ� �� ������ ������Ʈ
            shortestDistance = totalDistance;
            shortestOrder = order;
        }
        else if (totalDistance == shortestDistance) {
            // ������ ���� ������Ʈ
            if (order < shortestOrder) {
                shortestOrder = order;
            }
        }
        return;
    }

    for (int i = 0; i < orders.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            order.push_back(orders[i].cnt); // �ֹ� ������ �߰�

            Point dst = orders[i];  // ���� �ֹ��� ��ǥ ��������
            int distance = manhattanDistance(currLoca, dst); // ��ǥ ����ư �Ÿ� ���
            DeliveryOrder(orders, order, visited, dst, totalDistance + distance);  
            // ��ͷ� �ֹ����� ����
            order.pop_back();
            visited[i] = false;

        }
    }
}

int main() {
    int n; // �ֹ��� ����
    cin >> n;

    vector<Point> orders(2 * n); // �ֹ� ������ ������ ����

    for (int i = 0; i < 2 * n; i += 2) {
        cin >> orders[i].x >> orders[i].y >> orders[i + 1].x >> orders[i + 1].y;
        orders[i].cnt = (i / 2) + 1;
        orders[i + 1].cnt = -(i + 2) / 2;
    }

    shortestDistance = numeric_limits<int>::max();
    vector<int> order;
    vector<bool> visited(orders.size(), false);
    Point currLoca = { 500, 500 }; // �ʱ� ��ġ�� (500, 500)
    DeliveryOrder(orders, order, visited, currLoca, 0);

    for (int i = 0; i < 2 * n; i++) {
        cout << shortestOrder[i] << " "; // 0-based index�� 1-based index�� ��ȯ�Ͽ� ���
    }
    cout << endl;
    cout << shortestDistance;

    return 0;
}
