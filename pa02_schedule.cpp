#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long dp[5001];     // ���� �ִ����� ���� �迭
long long day[5001];    //�⺻������ ���� �迭

int main() {


    int k, n;
    cin >> k >> n;          // ��ü�⺻������ �� �۾����ɽð� �Է�

    for (int i = 0; i < n; i++) {
        day[i] = k;            // ��ü�⺻������ ����

    }
    int work_t;
    cin >> work_t;                  // �۾��� ��

    for (int t = 0; t < work_t; t++) {
        int time;               
        cin >> time;                    //�۾����� �Է�
        for (int i = 0; i < time; i++) {    
            int start, end, noise;
            cin >> start >> end >> noise;       // �۾��� �۾��ð���� ���� �Է�
            for (int j = start; j < end; j++) {
                day[j] += noise;} // �۾��� �۾��ð��뿡 ������ ���� ������ ����
        }
    }
    long long biggest = day[0];         //�����ִ밪 ���� ���� �ʱⰪ ����
    dp[0] = day[0];                         // �ʱⰪ ����
    for (int i = 1; i < n; i++) {

        dp[i] = max(day[i], dp[i - 1] + day[i]);
        biggest = max(dp[i], biggest);         
    }                                       // dynamic programming �� �̿��� ���� �ִ��� ���ϱ�


    cout << biggest << "\n";            // ���� �ִ밪 ���
    return 0;
}


