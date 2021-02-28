#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices, int size) {
        int q = -10000000;
        for (int i = 0; i < size; ++i) {
            q = max(q, max(-prices[i] + maxProfit(prices, size - i), prices[i] + maxProfit(&prices[i + 2], size - i - 1)));
        }
        return q;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    vector<int> prices = {1,2,3,4};
    cout << s.maxProfit(prices, prices.size());
    return 0;
}