#include <iostream>
#include <vector>
#include <algorithm>
#include "prog4.h"


istream& operator>>(istream& is, Applicant& a);
ostream& operator<<(ostream& os, Applicant& a);

pair<int, vector<Applicant>> pickTeam(int budget, vector<vector<Applicant>>& alist) {
    int positions = alist.size(); // Number of positions
    vector<vector<float>> maxBenefitsForBudget(positions + 1, vector<float>(budget + 1, 0)); // Store best benefit for max budget
    vector<vector<int>> chosen(positions + 1, vector<int>(budget + 1, -1)); // Store chosen applicant for each position and budget

    // Check if there are applicants
    if (positions == 0 || alist.empty()) {
        return make_pair(0, vector<Applicant>());
    }

    for (int i = 1; i <= positions; i++) {
        for (int j = 0; j <= budget; j++) {
            maxBenefitsForBudget[i][j] = maxBenefitsForBudget[i-1][j];  // No applicant is chosen for the i-th position
            for (int l = 0; l < alist[i-1].size(); l++) {
                if (j >= alist[i - 1][l].cost && maxBenefitsForBudget[i - 1][j - alist[i - 1][l].cost] + alist[i - 1][l].benefit > maxBenefitsForBudget[i][j]) {
                    maxBenefitsForBudget[i][j] = maxBenefitsForBudget[i - 1][j - alist[i - 1][l].cost] + alist[i - 1][l].benefit;
                    chosen[i][j] = l;
                }
            }
        }
    }

    vector<Applicant> team;
    for (int i = positions, j = budget; i > 0; i--) {
        if (chosen[i][j] != -1) {
            team.push_back(alist[i - 1][chosen[i][j]]);
            j -= alist[i - 1][chosen[i][j]].cost;
        }
    }

    return make_pair(maxBenefitsForBudget[positions][budget], team);
}

pair<int, vector<Applicant>> pickTeam_2(int budget, vector<vector<Applicant>>& alist) {
    int positions = alist.size(); // Number of positions
    vector<vector<float>> maxBenefitsForBudget(positions + 1, vector<float>(budget + 1, 0)); // Store best benefit for max budget 
    vector<vector<vector<Applicant>>> chosen(positions + 1, vector<vector<Applicant>>(budget + 1)); // Store chosen applicants for each position and budget

    // Check if there are applicants
    if (positions == 0 || alist.empty()) {
        return make_pair(0, vector<Applicant>());
    }

    for (int i = 1; i <= positions; i++) {
        for (int j = 0; j <= budget; j++) {
            maxBenefitsForBudget[i][j] = maxBenefitsForBudget[i - 1][j];
            chosen[i][j] = chosen[i - 1][j];

            for (int m = 0; m < alist[i - 1].size(); m++) {
                Applicant& a1 = alist[i - 1][m];
                if (a1.cost <= j) { // Check if the cost of a1 is within the budget
                    int benefit = maxBenefitsForBudget[i - 1][j - a1.cost] + a1.benefit; // Calculate the benefit of selecting a1
                    if (benefit > maxBenefitsForBudget[i][j]) { // Check if the benefit is greater than the current best benefit
                        maxBenefitsForBudget[i][j] = benefit;
                        chosen[i][j] = chosen[i - 1][j - a1.cost];
                        chosen[i][j].push_back(a1);
                    }
                }

                for (int k = m + 1; k < alist[i - 1].size(); k++) {
                    Applicant& a2 = alist[i - 1][k];
                    // Check if the combined cost of a1 and a2 is within the budget
                    if (a1.cost + a2.cost <= j) { 
                        int aBenefits = maxBenefitsForBudget[i - 1][j - (a1.cost + a2.cost)] + a1.benefit + a2.benefit;
                        if (aBenefits > maxBenefitsForBudget[i][j]) { // Check if the total benefits are greater than the current best benefit
                            maxBenefitsForBudget[i][j] = aBenefits;
                            chosen[i][j] = chosen[i - 1][j - (a1.cost + a2.cost)]; // Update the chosen applicants
                            chosen[i][j].push_back(a1); 
                            chosen[i][j].push_back(a2);
                        }
                    }
                }
            }
        }
    }

    return make_pair(maxBenefitsForBudget[positions][budget], chosen[positions][budget]);
}