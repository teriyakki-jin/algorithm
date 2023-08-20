#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

struct Point {          // 좌표번호와 cnt
    int x;
    int y;
    int cnt;
};

int shortestDistance;
vector<int> shortestOrder;

// 두 지점 사이의 맨하튼 거리를 계산하는 함수
int manhattanDistance(const Point& p1, const Point& p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
// order 의 유효검사
bool isValid(const vector<int>& order, const vector<Point>& orders) {
    int cnt = 0;
    for (int i = 0; i < order.size(); i++) {
        if (order[i] > 0)
            cnt++;
        else
            cnt--;
        if (cnt >= 3)   // 가방에 2개넘게 음식 담기는거 방지
            return false;
    }
    vector<bool> visited(orders.size(), false);
    for (int i = 0; i < order.size(); i++) {
        int idx = order[i];
        if (idx > 0) {
            visited[idx - 1] = true;   
        }
        else if (idx < 0) {
            if (!visited[abs(idx) - 1]) {   // 음식받지않고 배달하는경우 false
                return false;
            }
        }
    }
    return true;
}

void DeliveryOrder(vector<Point>& orders, vector<int>& order, vector<bool>& visited,
                    Point currLoca, int totalDistance) {
    if (!isValid(order, orders)) return;    // isvValid 확인

    if (order.size() == orders.size()) {
        if (totalDistance < shortestDistance) {
         // 현재 주문 순서의 이동 거리가 최단 거리보다 작으면 최단 거리 및 순서를 업데이트
            shortestDistance = totalDistance;
            shortestOrder = order;
        }
        else if (totalDistance == shortestDistance) {
            // 사전순 으로 업데이트
            if (order < shortestOrder) {
                shortestOrder = order;
            }
        }
        return;
    }

    for (int i = 0; i < orders.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            order.push_back(orders[i].cnt); // 주문 순서에 추가

            Point dst = orders[i];  // 현재 주문의 좌표 가져오기
            int distance = manhattanDistance(currLoca, dst); // 좌표 맨하튼 거리 계산
            DeliveryOrder(orders, order, visited, dst, totalDistance + distance);  
            // 재귀로 주문순서 정함
            order.pop_back();
            visited[i] = false;

        }
    }
}

int main() {
    int n; // 주문의 개수
    cin >> n;

    vector<Point> orders(2 * n); // 주문 정보를 저장할 벡터

    for (int i = 0; i < 2 * n; i += 2) {
        cin >> orders[i].x >> orders[i].y >> orders[i + 1].x >> orders[i + 1].y;
        orders[i].cnt = (i / 2) + 1;
        orders[i + 1].cnt = -(i + 2) / 2;
    }

    shortestDistance = numeric_limits<int>::max();
    vector<int> order;
    vector<bool> visited(orders.size(), false);
    Point currLoca = { 500, 500 }; // 초기 위치는 (500, 500)
    DeliveryOrder(orders, order, visited, currLoca, 0);

    for (int i = 0; i < 2 * n; i++) {
        cout << shortestOrder[i] << " "; // 0-based index를 1-based index로 변환하여 출력
    }
    cout << endl;
    cout << shortestDistance;

    return 0;
}
