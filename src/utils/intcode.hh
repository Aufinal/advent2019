#include <fstream>
#include <iostream>
#include <queue>
#include <tuple>

#include "strings.hh"

class IntCode {
    vector<int> memory;
    queue<int> inputs;

    int cursor;

    tuple<int, int, int> _parse(int instr) {
        int t = instr % 100;
        instr /= 100;

        return make_tuple(t, instr % 10, instr / 10);
    }

   public:
    vector<int> program;
    IntCode(vector<int> program) { program = program; }
    IntCode(string filename) {
        ifstream file(filename);
        string line;
        if (file.is_open() && getline(file, line)) {
            program = parseint(split(line));
        }
    }

    void add_input(int input) { inputs.push(input); }

    int read(int pos, int depth) {
        if (depth <= 0) {
            return pos;
        } else {
            return read(memory[pos], depth - 1);
        }
    }

    int read(int mode) { return read(cursor++, 2 - mode); }

    void write(int value, int pos, int depth = 2) {
        if (depth == 1) {
            memory[pos] = value;
        } else {
            write(value, memory[pos], depth - 1);
        }
    }

    void write(int value) { write(value, cursor++, 2); }

    int run() {
        auto [opcode, m1, m2] = _parse(memory[cursor++]);
        switch (opcode) {
            case 1: {
                write(read(m1) + read(m2));
                break;
            }
            case 2: {
                write(read(m1) * read(m2));
                break;
            }
            case 3: {
                write(inputs.front());
                inputs.pop();
                break;
            }
            case 4:
                return read(m1);
            case 5: {
                if (read(m1) != 0) {
                    int new_cursor = read(m2);
                    cursor = new_cursor;
                } else {
                    cursor++;
                }
                break;
            }
            case 6: {
                if (read(m1) == 0) {
                    int new_cursor = read(m2);
                    cursor = new_cursor;
                } else {
                    cursor++;
                }
                break;
            }
            case 7: {
                int lhs = read(m1);
                write((int)(lhs < read(m2)));
                break;
            }
            case 8: {
                write((int)(read(m1) == read(m2)));
                break;
            }
            case 99:
                return -1;
        }

        return run();
    }

    void init() {
        memory = program;
        cursor = 0;
        std::queue<int>().swap(inputs);
    }
};