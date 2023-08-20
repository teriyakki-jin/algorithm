#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long dp[5001];     // 구간 최대합을 구할 배열
long long day[5001];    //기본연구량 넣을 배열

int main() {


    int k, n;
    cin >> k >> n;          // 전체기본연구량 과 작업가능시간 입력

    for (int i = 0; i < n; i++) {
        day[i] = k;            // 전체기본연구량 세팅

    }
    int work_t;
    cin >> work_t;                  // 작업팀 수

    for (int t = 0; t < work_t; t++) {
        int time;               
        cin >> time;                    //작업개수 입력
        for (int i = 0; i < time; i++) {    
            int start, end, noise;
            cin >> start >> end >> noise;       // 작업팀 작업시간대와 소음 입력
            for (int j = start; j < end; j++) {
                day[j] += noise;} // 작업팀 작업시간대에 소음에 의한 연구량 감소
        }
    }
    long long biggest = day[0];         //구간최대값 구할 변수 초기값 세팅
    dp[0] = day[0];                         // 초기값 세팅
    for (int i = 1; i < n; i++) {

        dp[i] = max(day[i], dp[i - 1] + day[i]);
        biggest = max(dp[i], biggest);         
    }                                       // dynamic programming 을 이용한 구간 최대합 구하기


    cout << biggest << "\n";            // 구한 최대값 출력
    return 0;
}


