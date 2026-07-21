#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    int weight;
    int value;
    double ratio;
};

// Comparator to sort items by Value-to-Weight ratio in descending order
bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

void fractionalKnapsack(int capacity, vector<Item>& items) {
    // Compute ratio for each item
    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }

    // Sort items by ratio descending
    sort(items.begin(), items.end(), compareItems);

    double totalValue = 0.0;
    int currentWeight = 0;

    cout << fixed << setprecision(2);
    cout << "=== Fractional Knapsack Selection ===" << endl;

    for (size_t i = 0; i < items.size(); ++i) {
        if (currentWeight + items[i].weight <= capacity) {
            // Take full item
            currentWeight += items[i].weight;
            totalValue += items[i].value;
            cout << "Item (Weight: " << items[i].weight
                 << ", Value: " << items[i].value
                 << ") -> Fraction Taken: 1.00 (100%)" << endl;
        } else {
            // Take fraction of item
            int remainingCapacity = capacity - currentWeight;
            double fraction = (double)remainingCapacity / items[i].weight;
            totalValue += items[i].value * fraction;
            currentWeight += remainingCapacity;

            cout << "Item (Weight: " << items[i].weight
                 << ", Value: " << items[i].value
                 << ") -> Fraction Taken: " << fraction
                 << " (" << fraction * 100 << "%)" << endl;
            break; // Knapsack is full
        }
    }

    cout << "\nTotal Value in Knapsack: " << totalValue << endl;
}

int main() {
    int capacity = 50;
    vector<Item> items = {
        {10, 60, 0.0},
        {20, 100, 0.0},
        {30, 120, 0.0}
    };

    fractionalKnapsack(capacity, items);

    return 0;
}
