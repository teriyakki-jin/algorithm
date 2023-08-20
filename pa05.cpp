#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool Init(vector<int> tmp) {		// temp 배열이 조건에 충족되는지 확인
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i] != i + 1)		// index 자리에 (index +1) 숫자가 있는지 확인
			return false;			// 조건에 맞지 않으면 false 반환
	}
	return true;					// 조건에 맞으면 true 반환
}

vector<int> flip(int start, int end, vector<int> tmp) {	// temp 배열을 뒤집는 함수
	reverse(tmp.begin() + start, tmp.begin() + end + 1);	// 배열 start 부터 end 인덱스까지
	for (int i = start; i <= end; i++)
		tmp[i] *= -1;										// 범위 내 배열 정수 -1 곱해주기
	return tmp;
}


vector<int> flip_way(vector<int> tmp, int way){
    if(way == 0) { //start
        for (int i = 0; i < tmp.size(); i++) {		// 앞에서 부터 순회하며 탐색
            if (tmp[i] != i + 1) {			// index 자리에 (index + 1) 숫자가 아니라면
                for (int j = i; j < tmp.size(); j++) {
                    if ((tmp[j] == i + 1) || (tmp[j] == -(i + 1))) {	// flip 범위 정하기
                        tmp = flip(i, j, tmp);			//  i부터 j까지 flip
                        return tmp;
                    }
                }
            }
        }
        return tmp;
    }

    if (way == 1) { //End			뒤집힌 구간과 안 뒤집힌 구간이 일부 겹치면서 한 번 더 뒤집히는 경우
        for (int i = tmp.size() - 1; i >= 0; i--) {	// 뒤에서 부터 순회하며 탐색
            if (tmp[i] != i + 1) {			// index 자리에 (index +1) 숫자가 아니라면
                for (int j = i; j >= 0; j--) {
                    if ((tmp[j] == i + 1) || (tmp[j] == -(i + 1))) {  // flip 범위 정하기
                        tmp = flip(j, i, tmp);		// j 부터 i 까지 flip
                        return tmp;
                    }
                }
            }
        }
        return tmp;
    }
}

void make_fish(vector <vector<int>>& List , int k) {
	for (int i = 0; i < 5; i++) {
		vector<int> fish;
		for (int j = 0; j < k; j++) {
			int num;
			cin >> num;					// 숫자 입력받기
			fish.push_back(num);		// 입력받은 숫자 배열 만들기
		}
		List.push_back(fish);			// 입력받은 배열 모으기
		fish.clear();
	}
}
void solve(vector <vector <int>> List) {
	for (int i = 0; i < 5; i++) {
		vector<int> tmp1 = List[i];		// 최소횟수를 구하기 위한  배열


		if (Init(tmp1)) {
			cout << "zero" << endl;		// flip을 안하고도 조건을 만족
		}
		tmp1 = flip_way(tmp1,0);		// 양수와 음수를 같이 뒤집을 일이 없음.
		if (Init(tmp1)) {
			cout << "one" << endl;		// 한번의 flip으로 조건을 만족
			continue;
		}
		tmp1 = flip_way(tmp1,0);		// 한번 더 filp
		vector<int> tmp2 = List[i];		// two 경우를 구하기 위한 카피한 배열
		for(int j = 0; j <2;j++)		// flip 을 두번
            tmp2 = flip_way(tmp2, 1);	// one 이 아닌 경우이기 때문에 뒤에서부터 flip 해보기 ;

		if (Init(tmp1) || Init(tmp2)) {	// tmp1 또는 tmp2 가 조건만족시
			cout << "two" << endl;		// 두번의 flip으로 조건을 만족
			continue;
		}

		cout << "over" << endl;			// 아니면 그 이상이거나 불가능임.
        tmp1.clear();
		tmp2.clear();
	}
}
int main()
{
	int k;
	vector<vector<int>> List;
	cin >> k;
	make_fish(List , k);
	solve(List);

	return 0;
}
