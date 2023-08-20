#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

const int MAX = 201;
const int INF = 1e9 + 7;
int dx[4] = { 0, 0, 1, -1 };    // 상하좌우 이동 시 x 좌표 변화
int dy[4] = { -1, 1, 0, 0 };    // 상하좌우 이동 시 y 좌표 변화


// 각 노드의 정보를 저장하는 구조체
struct Node {
    int x, y;       // 현재 노드의 x , y 좌표
    int f, g, h;    // f(x) = g(x) + h(x)
    bool operator<(const Node& n) const {   // pq 노드 비교 bool 판별
        return f > n.f;
    }
};

int m, n;         // 지도의 가로와 세로 크기
int map[MAX][MAX];  // 지도
bool visited[MAX][MAX]; // 해당 좌표 방문 여부
vector<pair<int, int>> obstacles;   // 장애물의 좌표를 저장하는 벡터

// 맨하탄 거리를 계산하는 함수
int Manhattan(int x, int y, int tx, int ty) {
    return abs(x - tx) + abs(y - ty);
}

// 유클리드 거리를 계산하는 함수
int Euclidean(int x, int y, int tx, int ty) {
    return (int)sqrt(pow(x - tx, 2) + pow(y - ty, 2));
}

// 해당 좌표가 지도 범위 내에 있는지 확인하는 함수
bool inRange(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

// A* 알고리즘 함수 부분
int astar(int sx, int sy, int tx, int ty) {
    priority_queue<Node> pq;
    pq.push({ sx, sy, 0, 0, 0 }); // 시작 노드인 sx,sy 을 우선순위 큐에 삽입

    while (!pq.empty()) {         // 우선순위 큐가 비어있을 때 까지
        Node current = pq.top();      // 가장 우선순위가 높은 노드를 꺼내서 처리
        pq.pop();

        if (visited[current.x][current.y]) continue;  // 이미 방문노드 무시

        visited[current.x][current.y] = true;   // 현재 노드 방문 처리

        if (current.x == tx && current.y == ty) {
            return current.f;                  // 도착점 도달시 f 반환
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i], ny = current.y + dy[i];             // 상하좌우 확인

            if (!inRange(nx, ny) || map[nx][ny] == 0 || visited[nx][ny]) continue;      // 지도 범위를 벗어나는 지역 확인하기

            int cost = 1;       // 이동비용 1로 설정



            int g = current.g + cost;               // 현재 거리까지의 코스트 구하기
            int h = Euclidean(nx, ny, tx, ty);      // 유클리디안 거리 구하기
            int f = g + h;                          // f = g + h 대입

            pq.push({ nx, ny, f, g, h });           // pq에 집어넣기
        }
    }

    return -1;
}

void build() {
    for (int x = 0; x <= m; x++) {
        for (int y = 0; y <= n; y++) {
            map[x][y] = 1;              // 주어진 맵 모두 1로 만들기
        }

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;              // row 와 column 범위 입력
    build();
    int zeroCnt , z;
    cin >> zeroCnt;                     
    for (int i = 0; i < zeroCnt; i++) {
        int x, y;
        cin   >> z >> x >> y;
        map[x][y] = 0;
    }

    char trash;
    int sx, sy, tx, ty;
    cin >> trash >> sx >> sy;
    cin >> trash >> tx >> ty;
    string s;
    int obsCnt;
    cin >> s >> obsCnt;

    for (int i = 0; i < obsCnt; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int s_sx = min(x1, x2);        // 작은부분부터 큰부분 구하기 위해 x1 , x2 중 작은 값 확인
        int s_sy = min(y1, y2);        // 작은부분부터 큰부분 구하기 위해 y1 , y2 중 작은 값 확인 
        int b_ex = max(x1, x2);        // 작은부분부터 큰부분 구하기 위해 x1 , x2 중 큰 값 확인
        int b_ey = max(y1, y2);        // 작은부분부터 큰부분 구하기 위해 y1 , y2 중 큰 값 확인
        for (int x = s_sx; x <= b_ex; x++) {    // for 구문을 사용하여 장애물지역을 0으로 표시
            for (int y = s_sy; y <= b_ey; y++) {
                map[x][y] = 0;                  
            }
        }
        obstacles.push_back({ x1, y1 });
        obstacles.push_back({ x2, y2 });
    }

    int result = astar(sx, sy, tx, ty);

    cout << result * 3<< "\n";          // 이동비용을 1로 설정해두었기때문에 곱하기 3

    return 0;
}
