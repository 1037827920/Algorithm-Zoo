#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int maxValueOfCoins(const vector<vector<int>>& stacks, int k) {
    int m = stacks.size();
    vector<vector<int>>dp(m + 1, vector<int>(k + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j]; // 初始值取上一个栈的没有取硬币的状态
            int sum = 0;
            for (int t = 1; t <= (int)stacks[i - 1].size() && t <= j; ++t) {
                sum += stacks[i - 1][t - 1];
                dp[i][j] = max(dp[i][j], dp[i - 1][j - t] + sum);
            }
        }
    }
    return dp[m][k];
}

int main() {
    vector<vector<int>> stacks0 = {
        {1, 100, 3},
        { 7, 8, 9 },
    };
    cout << maxValueOfCoins(stacks0, 2) << endl;

    vector<vector<int>> stacks1 = {
        {100},
        {100},
        {100},
        {100},
        {100},
        {100},
        {1,1,1,1,1,1,700},
    };
    cout << maxValueOfCoins(stacks1, 7) << endl;
    return 0;
}