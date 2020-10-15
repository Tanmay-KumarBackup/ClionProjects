#include <iostream>
#include <cstdlib>
#include<vector>
#include<map>
#include <utility>
#include<set>
#include<algorithm>
#include<climits>
int i;
class Bag {
    int weight{};
    int holding_weight = -1;
    char id{};
public:
    Bag(int w, char id) {
        this->weight = w;
        this->id = id;

    }

    int get_weight() const {
        return this->weight;
    }

    int get_holdWeight() const {
        return this->holding_weight;
    }

    explicit Bag(int fill) {
        this->holding_weight = fill;
    }

    int get_ID() const {
        return this->id;
    }
};

class Valuables {
public:
    int weight;
    int cost;

    Valuables(int c, int w) {
        this->cost = c;
        this->weight = w;
    }
};

//int max(int a, int b) { return (a > b) ? a : b; }
int maximize(Bag *bags, int size) {
    int max = 0;
    for (i = 0; i < size; i++) {
        if (bags[i].get_holdWeight() == -1 && bags[max].get_weight() < bags[i].get_weight()) { max = i; }
    }
    if (bags[max].get_holdWeight() != -1) { max = -1; }//corrected
    return max;
}

int knapsack(Valuables *Resource, int Size, int W) {
    // Mapping weights with Profits
    std::map<int, int> unordered_map;

    std::set<std::vector<std::pair<int, int>>> set_sol;
    // Making Pairs and inserting
    // into the map
    std::vector<int> wt;
    std::vector<int> val;
    for (int i = 0; i < Size; i++) {
        wt.push_back(Resource[i].weight);
        val.push_back(Resource[i].cost);
        unordered_map.insert({wt[i], val[i]});
    }
    int result = INT_MIN;
    int remaining_weight;
    int sum = 0;

    // Loop to iterate over all the
    // possible permutations of array
    do {
        sum = 0;

        // Initially bag will be empty
        remaining_weight = W;
        std::vector<std::pair<int, int>> possible;

        // Loop to fill up the bag
        // until there is no weight
        // such which is less than
        // remaining weight of the
        // 0-1 knapsack
        for (int i = 0; i < Size; i++) {
            if (wt[i] <= remaining_weight) {

                remaining_weight -= wt[i];
                auto itr = unordered_map.find(wt[i]);
                sum += (itr->second);
                possible.emplace_back(itr->first, itr->second);
            }
        }
        sort(possible.begin(), possible.end());
        if (sum > result) {
            result = sum;
        }
        if (set_sol.find(possible) ==
            set_sol.end()) {
            for (auto sol: possible) {
                std::cout << sol.first << ": "
                          << sol.second << ", ";
            }
            std::cout << std::endl;
            set_sol.insert(possible);
        }
    } while (next_permutation(wt.begin(), wt.end()));
    std::cout << "Maximum value that this bag can hold is: \t" << result << std::endl;
    return result;
}

char Bag_char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int main() {
    int val_size;
    std::cout << "enter the number of valuables\t";
    std::cin >> val_size;
    int totalBags;
    std::cout << "enter the number of bags\t";
    std::cin >> totalBags;
    Valuables *resource_arr;
    Bag *bag_arr;
    resource_arr = (Valuables *) malloc(sizeof(Valuables) * val_size);
    bag_arr = (Bag *) malloc(sizeof(Bag) * totalBags);
    for (i = 0; i < val_size; i++) {
        int temp_cost, temp_weight;
        std::cout << "Enter the Value (" << i << ")\t";
        std::cin >> temp_cost >> temp_weight;
        resource_arr[i] = Valuables(temp_cost, temp_weight);
    }
    for (i = 0; i < totalBags; i++) {
        int temp_weight;
        std::cout << "Enter the weight of bag ( " << Bag_char[i] << ") " << std::endl;
        std::cin >> temp_weight;
        bag_arr[i] = Bag(temp_weight,
                         Bag_char[i]);//naming all the bags and also the maximum amount of weight that bag can hold...
    }
    //now i will approach to solve 0/1 knapsack problem for every bag
    //starting with the maximum weighting bag, and slowly moving to the next bag
    while (i != -1) {
        i = maximize(bag_arr, totalBags);// O(n)
        if (i != -1) {
            std::cout << "The Table for (" << bag_arr[i].get_ID() << ") is as followed:\t" << std::endl;
            bag_arr[i] = Bag(knapsack(resource_arr, val_size, bag_arr[i].get_weight()));//O(2^n)
        }
    }
    return 0;
}