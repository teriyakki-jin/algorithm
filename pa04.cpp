#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int tree[21][21] = { 0, };				// 그래프 공간
bool pollutedCity[21] = { 0, };			// 오염지역 확인공간

void solve(int N, int c1, int c2) {
	vector<int> v;
	
	int  polluted = 0;
	while (polluted <= N - 2) {		// 입력으로 받은 오염지역 외 모든지역이 오염될때까지 
		
		for (int i = 1; i <= N; i++) {
			for (int j = i + 1; j <= N; j++) {
				if ((pollutedCity[i] || pollutedCity[j]) && tree[i][j] > 0) {	// 오염지역 걸쳐있는 지역에 한해
					tree[i][j]--;												// 1씩감소
					if (tree[i][j] == 0) {										// 값이 0이 되었다는것은 가장 가까운 정점 즉 그 다음 오염될 정점
						if (!pollutedCity[i]) {									// 2차원 배열이라 오염 정점 구역을 구분해서 
							v.push_back(i);										// 벡터에 추가해줍니다.
						}
						else if (!pollutedCity[j]) {							
							v.push_back(j);										// 벡터에 추가
						}
						polluted++;												// 오염지역 개수 증가

					}
				}
			}
		}
		sort(v.begin(), v.end());												// 정점 번호의 오름차순 출력
		v.erase(unique(v.begin(), v.end()), v.end());							// 중복 숫자 제거
		for (int i = 0; i < v.size(); i++) {
			pollutedCity[v[i]] = 1;
			cout << v[i] << endl;												// 출력
		}
		v.clear();																// vector clear
	}
}

int main() {
	int N, c1, c2;			
	cin >> N >> c1 >> c2;	//	정점개수, 오염지역 입력
	pollutedCity[c1] = pollutedCity[c2] = 1;	// 오염지역 표시
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			tree[i][j] = -1;		// 초기 그래프 그리기
		}
	}


	int src, dst, len;
	for (int i = 0; i < N - 1; i++) {
		cin >> src >> dst >> len;	// 그래프 좌표에 거리값 넣기
		tree[src][dst] = len;
	}

	solve(N,c1,c2);
	return 0;
}