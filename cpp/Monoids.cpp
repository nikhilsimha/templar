#include "Monoids.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

#include "Utils.hpp"

struct AvgState {
    int64_t sum;
    uint count;
};

struct OrderingInput {
    int64_t key;
    string value;
};

int main() {
    auto summer = monoids::Sum<int, int, int>();
    int x = 1;
    int y = 2;
    summer.merge(x, std::move(y));
    cout << x << endl;

    auto avger = monoids::Avg<int, AvgState, double>();
    int xa = 1;
    int ya = 2;
    int za = 4;
    auto state = avger.init(std::move(xa));
    avger.update(state, std::move(ya));
    avger.update(state, std::move(za));
    std::cout << avger.finalize(std::move(state)) << std::endl;

    // IDEA:
    // input -> state could be reducer
    // state -> output could be a mapper/finalizer
    // that way a single state like sum could be
    // finalized into sum and avg - saving some space in storage
    // but for now, I don't have another example of its usefulness
    auto ord = monoids::OrderBy<OrderingInput, vector<OrderingInput>, vector<string>>(4, false);
    OrderingInput inp1 = {1, "one"};
    OrderingInput inp2 = {2, "two"};
    OrderingInput inp3 = {3, "three"};
    OrderingInput inp4 = {4, "four"};
    OrderingInput inp5 = {5, "five"};
    OrderingInput inp6 = {6, "six"};
    auto state1 = ord.init(std::move(inp6));
    ord.update(state1, std::move(inp4));
    ord.update(state1, std::move(inp2));

    auto state2 = ord.init(std::move(inp5));
    ord.update(state2, std::move(inp3));
    ord.update(state2, std::move(inp1));

    ord.merge(state1, std::move(state2));
    auto fns = ord.finalize(std::move(state1));

    for(auto  elem: fns) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;

}

