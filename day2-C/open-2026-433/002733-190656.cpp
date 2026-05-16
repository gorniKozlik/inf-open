#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<std::pair<int, int>> lr(n);
    for (std::pair<int, int>& elem : lr) {
        std::cin >> elem.first >> elem.second;
    }
    std::vector<int> que(q);
    for (int& elem : que) {
        std::cin >> elem;
    }
    for (int elem : que) {
        std::cout << elem / 2 << ' ';
    }
    std::cout << '\n';
    return 0;
}