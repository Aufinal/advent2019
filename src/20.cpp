#include <cctype>
#include <forward_list>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "utils/math.hh"
#include "utils/matrix.hh"

void parse(Matrix& m, Point& start_pos, Point& end_pos,
           unordered_map<Point, Point>& portals,
           unordered_map<Point, vector<pair<Point, int>>>& distances) {
    unordered_map<string, vector<Point>> portal_names;
    forward_list<Point> portal_list;

    for (int x = 1; x < m.size_x - 1; x++) {
        for (int y = 1; y < m.size_y - 1; y++) {
            if (isupper(m(x, y))) {
                Point pos(x, y);

                for (auto dir : directions) {
                    if (isupper(m[pos - dir]) && m[pos + dir] == '.') {
                        string pname;
                        pname += min(m[pos], m[pos - dir]);
                        pname += max(m[pos], m[pos - dir]);
                        if (pname == "AA")
                            start_pos = pos + dir;
                        else if (pname == "ZZ")
                            end_pos = pos + dir;
                        else
                            portal_names[pname].push_back(pos + dir);

                        portal_list.push_front(pos + dir);
                    }
                }
            }
        }
    }

    for (auto p : portal_list) {
        queue<Point> bfs;
        unordered_map<Point, int> dist;
        bfs.push(p);
        dist[p] = 0;

        while (!bfs.empty()) {
            auto pos = bfs.front();
            auto d = dist[pos];
            bfs.pop();
            for (auto dir : directions) {
                auto new_pos = pos + dir;
                if (m[new_pos] == '#') continue;

                if (isupper(m[new_pos])) {
                    if (pos != start_pos && pos != p) {
                        distances[p].push_back(make_pair(pos, d));
                    }
                    continue;
                }

                if (!dist.count(new_pos)) {
                    dist[new_pos] = d + 1;
                    bfs.push(new_pos);
                }
            }
        }
    }

    for (auto [pname, v] : portal_names) {
        portals[v[0]] = v[1];
        portals[v[1]] = v[0];
    }
}

using DistPoint = pair<int, Point>;

int part_1(Matrix& m) {
    Point start_pos, end_pos;
    unordered_map<Point, Point> portals;
    unordered_map<Point, vector<pair<Point, int>>> portal_dist;

    parse(m, start_pos, end_pos, portals, portal_dist);
    priority_queue<DistPoint, vector<DistPoint>, greater<DistPoint>> bfs;
    unordered_set<Point> visited;
    bfs.push(make_pair(0, start_pos));
    visited.insert(start_pos);

    while (!bfs.empty()) {
        auto [dist, pos] = bfs.top();
        bfs.pop();

        for (auto [portal, d] : portal_dist[pos]) {
            if (portal == end_pos) return dist + d;

            auto new_pos = portals[portal];

            if (!visited.count(new_pos)) {
                visited.insert(new_pos);
                bfs.push(make_pair(dist + d + 1, new_pos));
            }
        }
    }

    return -1;
}

bool is_outer(Point p, Matrix& m) {
    return real(p) == 2 || real(p) == m.size_x - 3 || imag(p) == 2 ||
           imag(p) == m.size_y - 3;
}

using DistDepPoint = tuple<int, int, Point>;

int part_2(Matrix& m) {
    Point start_pos, end_pos;
    unordered_map<Point, Point> portals;
    unordered_map<Point, vector<pair<Point, int>>> portal_dist;

    parse(m, start_pos, end_pos, portals, portal_dist);
    priority_queue<DistDepPoint, vector<DistDepPoint>, greater<DistDepPoint>> bfs;
    unordered_set<pair<int, Point>> visited;
    visited.insert(make_pair(0, start_pos));
    bfs.push(make_tuple(0, 0, start_pos));

    while (!bfs.empty()) {
        auto [dist, depth, pos] = bfs.top();
        bfs.pop();

        for (auto [portal, d] : portal_dist[pos]) {
            if (!depth) {
                if (portal == end_pos) return dist + d;
                if (is_outer(portal, m)) continue;
            } else {
                if (portal == end_pos) continue;
            }

            auto new_pos = portals[portal];
            int new_depth = depth + (is_outer(portal, m) ? -1 : 1);
            auto new_pair = make_pair(new_depth, new_pos);

            if (!visited.count(new_pair)) {
                visited.insert(new_pair);
                bfs.push(make_tuple(dist + d + 1, new_depth, new_pos));
            }
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];
    Matrix m(filename);
    cout << part_1(m) << endl;
    cout << part_2(m) << endl;

    return 0;
}