#include <iostream>
#include <vector>
#include <algorithm>
#include "prog4.h"


istream& operator>>(istream& is, Applicant& a);
ostream& operator<<(ostream& os, Applicant& a);

pair<int, vector<Applicant>> pickTeam(int budget, vector<vector<Applicant>>& alist) {
    int P = alist.size();
    vector<vector<float>> dp(P + 1, vector<float>(budget + 1, 0));
    vector<vector<int>> chosen(P + 1, vector<int>(budget + 1, -1));

    for (int i = 1; i <= P; i++) {
        for (int j = 0; j <= budget; j++) {
            dp[i][j] = dp[i-1][j];  // no applicant is chosen for the i-th position
            for (int l = 0; l < alist[i-1].size(); l++) {
                if (j >= alist[i - 1][l].cost && dp[i - 1][j - alist[i - 1][l].cost] + alist[i - 1][l].benefit > dp[i][j]) {
                    dp[i][j] = dp[i - 1][j - alist[i - 1][l].cost] + alist[i - 1][l].benefit;
                    chosen[i][j] = l;
                }
            }
        }
    }

    vector<Applicant> team;
    for (int i = P, j = budget; i > 0; i--) {
        if (chosen[i][j] != -1) {
            team.push_back(alist[i - 1][chosen[i][j]]);
            j -= alist[i - 1][chosen[i][j]].cost;
        }
    }

    return make_pair(dp[P][budget], team);
}

pair<float, vector<Applicant>> pickTeam_2(int budget, vector<vector<Applicant>>& alist) {
    vector<Applicant> app;
    return make_pair(0, app);
}
