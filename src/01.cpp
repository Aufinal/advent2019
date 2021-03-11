#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    vector<int> iv;
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];
    cout << filename << endl;
    ifstream file;
    string line;
    file.open(filename);
    while (getline(file, line)) {
        cout << line << endl;
    }

    return 0;

}