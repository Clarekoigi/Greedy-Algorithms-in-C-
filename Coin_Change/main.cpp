#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void coinChange(int amount, const vector<int>& denominations) {
    int totalCoins = 0;
    int remaining = amount;

    cout << "=== Coin Change Breakdown ===" << endl;
    cout << "Initial Amount: " << amount << "\n\n";

    for (int coin : denominations) {
        if (remaining == 0) break;

        int count = remaining / coin;
        if (count > 0) {
            totalCoins += count;
            remaining %= coin;
            cout << "Selected Coin: " << coin
                 << " | Used: " << count
                 << " | Remaining Balance: " << remaining << endl;
        }
    }

    cout << "\nTotal Coins Used: " << totalCoins << endl;
}

int main() {
    // Denominations sorted in descending order for standard Greedy Choice
    vector<int> denominations = {200, 100, 50, 20, 10, 5, 1};
    int amount = 389;

    coinChange(amount, denominations);

    return 0;
}
