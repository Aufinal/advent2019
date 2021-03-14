#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_map>

#include "utils/strings.hh"

typedef unordered_map<string, vector<string>> umsvs;
typedef unordered_map<string, string> umss;

tuple<umss, umsvs> parse(string filename) {
    umsvs children;
    umss parent;
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> v = split(line, ")");
            if (children.count(v[0])) {
                children[v[0]].push_back(v[1]);
            } else {
                children[v[0]] = {v[1]};
            }
            parent[v[1]] = v[0];
        }
    }

    return make_tuple(parent, children);
}

int sum_orbits(umsvs &tree, string node, int cur_sum) {
    int res = cur_sum;
    if (!tree.count(node)) {
        return res;
    }
    for (auto child : tree[node]) {
        res += sum_orbits(tree, child, cur_sum + 1);
    }

    return res;
}

vector<string> path_to_root(umss &parent, string node) {
    vector<string> res = {node};
    while (parent.count(node)) {
        node = parent[node];
        res.push_back(node);
    }

    return res;
}

int part_1(umsvs &tree) { return sum_orbits(tree, "COM", 0); }
int part_2(umss &parent, string a, string b) {
    auto path_a = path_to_root(parent, a);
    auto path_b = path_to_root(parent, b);
    auto s = path_a.size();
    auto t = path_b.size();
    auto c = 1;
    while (path_a[s - c] == path_b[t - c]) c++;
    return s + t - 2 * c;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    umsvs tree;
    umss parent;
    tie(parent, tree) = parse(filename);
    cout << "Part 1 : " << part_1(tree) << endl;
    cout << "Part 2 : " << part_2(parent, "YOU", "SAN") << endl;

    return 0;
}