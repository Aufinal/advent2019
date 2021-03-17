#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "utils/strings.hh"

using ReactionMap = unordered_map<string, pair<long, unordered_map<string, long>>>;

ReactionMap parse(string filename) {
    ifstream file(filename);
    string line;
    ReactionMap res;

    if (file.is_open()) {
        while (getline(file, line)) {
            auto v = split(line, " => ");
            int quant_rhs;
            char name_rhs[10];
            sscanf(v[1].c_str(), "%d %s", &quant_rhs, name_rhs);
            unordered_map<string, long> lhs;
            for (auto&& elt : split(v[0], ", ")) {
                int quant;
                char name[10];
                sscanf(elt.c_str(), "%d %s", &quant, name);
                lhs[name] = quant;
            }

            res[name_rhs] = make_pair(quant_rhs, lhs);
        }
    }

    return res;
}

void produce_fuel(ReactionMap& reactions, unordered_map<string, long>& quantities,
                  long n = 1) {
    quantities["FUEL"] = -n;
    string reactant;
    unordered_set<string> negative = {"FUEL"};

    while (!negative.empty()) {
        auto reactant = *negative.begin();
        auto reaction = reactions[reactant];
        auto needed = -quantities[reactant];

        auto quotient = needed / reaction.first + (needed % reaction.first != 0);
        for (auto [key, val] : reaction.second) {
            quantities[key] -= quotient * val;
            if (quantities[key] < 0 && key != "ORE") negative.insert(key);
        }
        quantities[reactant] += quotient * reaction.first;
        negative.erase(reactant);
    }
}

long part_1(ReactionMap& reactions) {
    unordered_map<string, long> quantities;
    produce_fuel(reactions, quantities);

    return -quantities["ORE"];
}

long part_2(ReactionMap& reactions, long ore) {
    unordered_map<string, long> quantities;
    quantities["ORE"] = ore;
    long fuel = 0;
    long can_produce;

    while (can_produce) {
        can_produce = quantities["ORE"];
        long result = 0;
        do {
            unordered_map<string, long> qcopy(quantities);
            produce_fuel(reactions, qcopy, can_produce);
            result = qcopy["ORE"];
            if (result < 0) can_produce /= 2;
        } while (result < 0);

        produce_fuel(reactions, quantities, can_produce);
        fuel += can_produce;
    }

    return fuel;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    auto reactions = parse(filename);

    cout << "Part 1 : " << part_1(reactions) << endl;

    cout << "Part 2 : " << part_2(reactions, 1000000000000) << endl;

    return 0;
}