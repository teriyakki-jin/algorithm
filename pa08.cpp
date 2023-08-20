#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<vector<int>> ingredients;
vector<int> minRequirements;
bool found = false;
vector<int> minCostSet;
vector<int> currentSet;
vector<int> currentNutrition;
int minCost = 1e9;
int maxTotalNutrition = 0;
// DFS를 사용하여 가능한 모든 조합을 탐색
void findValidSets(int index, int currentCost, int currentTotalNutrition) {


    if (currentCost > minCost) {    // 현재검사 cost 와 최소 코스트 비교하여 최소 cost 보다 크면 return 
        return;
    }

    if (index == N) {               // 검사 index 가 입력만큼 들어왔다면
        bool satisfiesRequirements = true;
        for (int i = 0; i < 4; i++) {
            if (currentNutrition[i] < minRequirements[i]) {// 영양 요구사항 불만족
                satisfiesRequirements = false;
                break;
            }
        }
        if (satisfiesRequirements) {        // 요구사항 만족하는 경우
            if (currentCost > minCost) { // 현재검사 cost 와 최소 cost 비교하여 최소 cost 보다 크면 return
                return;
            }
            else if (currentCost < minCost) {   // 현재검사 cost 가 최소 cost 보다 작으면 초기화
                minCost = currentCost;  // 최소비용 초기화
                maxTotalNutrition = currentTotalNutrition;  //최대 영양소 합 초기화
                minCostSet = currentSet;            // 최소 비용 초기화
            }
            else {                      //현재 검사 cost 와 최소 cost 가 같다면
                if (currentTotalNutrition < maxTotalNutrition) return;  // 최대 영양소 합보다 작으면 return  
                else if (currentTotalNutrition > maxTotalNutrition) {    // 최대 영양소 합보다 크면 초기화
                    maxTotalNutrition = currentTotalNutrition;  //최대 영양소 합 초기화
                    minCostSet = currentSet;                // 최소 비용 초기화
                }
                else {                                          // 최대 영양소 합 같으면
                    if (minCostSet > currentSet)                // 더 cost 가 작은 조합 선택
                        minCostSet = currentSet;
                }
            }
            found = true;    // 조합 찾음 표시
        }
        return;
    }

    // 현재 재료를 선택하지 않고 넘어감
    findValidSets(index + 1, currentCost, currentTotalNutrition);

    // 현재 재료를 선택
    for (int i = 0; i < 4; i++) {
        currentNutrition[i] += ingredients[index][i];
    }
    currentSet.push_back(index + 1);
    findValidSets(index + 1, currentCost + ingredients[index][4], currentTotalNutrition + ingredients[index][0] + 
        ingredients[index][1] + ingredients[index][2] + ingredients[index][3]);

    // 현재 재료를 선택하지 않은 경우에도 영향을 주지 않도록 상태를 복구
    currentSet.pop_back();
    for (int i = 0; i < 4; i++) {
        currentNutrition[i] -= ingredients[index][i];
    }
}


int main() {
    cin >> N;

    minRequirements.resize(4);
    for (int i = 0; i < 4; i++) {
        cin >> minRequirements[i];
    }

    ingredients.resize(N, vector<int>(5));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> ingredients[i][j];
        }
    }

    currentNutrition.resize(4, 0);

    findValidSets(0, 0, 0);  // 탐색시작

    if (!found) {           // 값 찾지 못한경우
        cout << "0" << endl;
    }
    else {

        for (int i = 0; i < minCostSet.size(); i++) {
            cout << minCostSet[i] << " ";
        }
        cout << endl;
    }

    return 0;
}