#include "utils/intcode.hh"

string parse_output(vector<long> v) {
    std::stringstream buffer;
    for (auto c : v) {
        buffer << (char)c;
    }

    auto vec = split(buffer.str(), "\n\n").back();
    vec = split(vec, "\n").front();
    return buffer.str();
}

string command_gray(int n, vector<string> items) {
    int gray = n ^ (n >> 1);
    int prev = (n - 1) ^ ((n - 1) >> 1);

    string command = gray > prev ? "drop" : "take";
    int diff = gray ^ prev;
    int i = 0;
    while (diff >>= 1) i++;

    return command + " " + items[i];
}

void run(IntCode& ic) {
    string s;
    ic.init();
    ifstream file("inputs/25-play.txt");
    std::stringstream buffer;
    if (file.is_open()) buffer << file.rdbuf();
    ic.input_string(buffer.str());
    ic.run();
    ic.get_outputs();

    vector<string> items = {"astrolabe",       "mug",          "monolith",  "ornament",
                            "weather machine", "bowl of rice", "fuel cell", "hologram"};

    int taken = 0;

    while (ic.state != done) {
        ic.input_string(command_gray(++taken, items));
        ic.input_string("north");
        ic.run();
        auto v = ic.get_outputs();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];
    auto ic = IntCode(filename);

    run(ic);

    return 0;
}