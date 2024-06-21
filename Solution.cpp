#include <bits/stdc++.h>
using namespace std;

class Abhimanyu {
private:
    int maxPower,currentPower,remainingSkips,remainingRecharges;

    bool canCrossCircles(int position, int prevAction, vector<int>& chakravyuha, map<vector<int>, bool>& dp) {
        if (currentPower < 0) {
            return false;
        }
        if (position == chakravyuha.size()) {
            return true;
        }

        vector<int> state = { position, currentPower, remainingSkips, remainingRecharges, prevAction };
        if (dp.find(state) != dp.end()) {
            return dp[state];
        }

        bool canCross = false;
	    
        if (remainingSkips > 0) {
            remainingSkips--;
            canCross |= canCrossCircles(position + 1, 0, chakravyuha, dp);
            remainingSkips++;
        }

        int enemyPower = chakravyuha[position];
        if (position == 3 || position == 7) {
            if (prevAction) {
                enemyPower += chakravyuha[position - 1] / 2;
            } else {
                enemyPower += chakravyuha[position - 1];
            }
        }

        if (currentPower >= enemyPower) {
            currentPower -= enemyPower;
            canCross |= canCrossCircles(position + 1, 1, chakravyuha, dp);
            currentPower += enemyPower;
        } else if (remainingRecharges > 0) {
            int initialPower = currentPower;
            currentPower = maxPower;
            remainingRecharges--;
            canCross |= canCrossCircles(position, prevAction, chakravyuha, dp);
            remainingRecharges++;
            currentPower = initialPower;
        }

        return dp[state] = canCross;
    }

public:
    Abhimanyu(int initialPower, int skipsAllowed, int rechargesAllowed) {
        maxPower = initialPower;
        currentPower = initialPower;
        remainingSkips = skipsAllowed;
        remainingRecharges = rechargesAllowed;
    }

    bool canEscape(vector<int>& chakravyuha) {
        map<vector<int>, bool> dp;
        return canCrossCircles(0, 1, chakravyuha, dp);
    }
};

int main() {
    int initialPower, skipsAllowed, rechargesAllowed;
    vector<int> chakravyuha;

    do {
        cout << "Enter Abhimanyu's initial power (positive integer): ";
        cin >> initialPower;
    } while (initialPower <= 0);

    do {
        cout << "Enter how many times Abhimanyu can skip enemies (non-negative integer): ";
        cin >> skipsAllowed;
    } while (skipsAllowed < 0);

    do {
        cout << "Enter how many times Abhimanyu can recharge (non-negative integer): ";
        cin >> rechargesAllowed;
    } while (rechargesAllowed < 0);

    cout << "Enter enemy powers at each of the 11 circles:\n";
    for (int i = 0; i < 11; ++i) {
        int enemyPower;
        cin >> enemyPower;
        chakravyuha.push_back(enemyPower);
    }

    Abhimanyu abhimanyuObj(initialPower, skipsAllowed, rechargesAllowed);

    if (abhimanyuObj.canEscape(chakravyuha)) {
        cout << "Abhimanyu can successfully escape the Chakravyuha.\n";
    } else {
        cout << "Abhimanyu cannot escape the Chakravyuha.\n";
    }

    return 0;
}


// Test Case
// 1. 
// Max Power: 20
// Skips: 3
// Recharges: 1
// Enemy Powers: [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

// Output: Abhimanyu cannot escape the Chakravyuha

// 2.
// Max Power: 20
// Skips: 3
// Recharges: 2
// Enemy Powers: [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

// Output: Abhimanyu can successfully escape the Chakravyuha.
