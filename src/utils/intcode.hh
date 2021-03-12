#include <fstream>
#include <iostream>
#include "misc.hh"

class IntCode {
    vector<int> memory;
    int cursor;

    public:
        vector<int> program;
        IntCode(vector<int> program) { program = program;}
        IntCode(string filename) {
            ifstream file(filename);
            string line;
            if (file.is_open() && getline(file, line)) {
                program = parseint(split(line));
            }
        }

        int read(int pos, int depth = 2) {
            if (depth == 0) {
                return pos;
            } else {
                return read(memory[pos], depth - 1);
            }
        }

        void write(int value, int pos, int depth = 2) {
            if (depth == 1) {
                memory[pos] = value;
            } else {
                write(value, memory[pos], depth - 1);
            }
        }

        int run() {
            switch (memory[cursor]) {
                case 1: {
                    int a = read(cursor + 1);
                    int b = read(cursor + 2);
                    write(a + b, cursor + 3);
                    cursor += 4;
                    break ;
                }
                case 2: {
                    int a = read(cursor + 1);
                    int b = read(cursor + 2);
                    write(a * b, cursor + 3);
                    cursor += 4;
                    break ;
                }
                case 99:
                    return memory[0];
            }

            return run();
        }

        void init() {
            memory = program;
            cursor = 0;
        }

        void print_program() {
            for (auto elt: program) {
                cout << elt << "," ;
            }
            cout << endl;
        }

        void print_memory() {
            for (auto elt: memory) {
                cout << elt << "," ;
            }
            cout << endl;
        }
};