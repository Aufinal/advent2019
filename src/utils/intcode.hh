#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <tuple>

#include "strings.hh"

enum State {
    ok,
    done,
    need_input,
};
class IntCode {
    unordered_map<long, long> memory;
    queue<long> inputs;

    long cursor;
    long offset;

    tuple<short, short, short, short> _parse(int instr) {
        int t = instr % 100;
        instr /= 100;

        return make_tuple(t, instr % 10, (instr / 10) % 10, (instr / 100) % 10);
    }

   public:
    vector<long> program;
    State state;
    queue<long> outputs;

    IntCode(vector<long> prog) { program = prog; }
    IntCode(string filename) {
        ifstream file(filename);
        string line;
        if (file.is_open() && getline(file, line)) {
            program = parseint(split(line));
        }
    }

    void add_input() {}

    template <typename... Args>
    void add_input(long i, Args... args) {
        inputs.push(i);
        add_input(args...);
    }

    bool has_output() { return !outputs.empty(); }

    long get_output() {
        long res = outputs.front();
        outputs.pop();
        return res;
    }

    vector<long> get_outputs(short n) {
        vector<long> res(n, 0);
        for (int i = 0; i < n; i++) {
            res[i] = outputs.front();
            outputs.pop();
        }
        return res;
    }

    long output_mem(long address) { return memory[address]; }

    long read(short mode) {
        if (mode == 1) {
            return memory[cursor++];
        } else {
            long address = (mode / 2) * offset + memory[cursor++];
            return memory[address];
        }
    }

    void write(long value, short mode) {
        long address = (mode / 2) * offset + memory[cursor++];
        memory[address] = value;
    }

    void advance() {
        state = ok;
        auto [opcode, m1, m2, m3] = _parse(memory[cursor++]);
        switch (opcode) {
            case 1: {
                write(read(m1) + read(m2), m3);
                break;
            }
            case 2: {
                write(read(m1) * read(m2), m3);
                break;
            }
            case 3: {
                if (inputs.empty()) {
                    cursor--;
                    state = need_input;
                } else {
                    write(inputs.front(), m1);
                    inputs.pop();
                }
                break;
            }
            case 4:
                outputs.push(read(m1));
                break;
            case 5: {
                if (read(m1) != 0) {
                    long new_cursor = read(m2);
                    cursor = new_cursor;
                } else {
                    cursor++;
                }
                break;
            }
            case 6: {
                if (read(m1) == 0) {
                    long new_cursor = read(m2);
                    cursor = new_cursor;
                } else {
                    cursor++;
                }
                break;
            }
            case 7: {
                long lhs = read(m1);
                write(lhs < read(m2), m3);
                break;
            }
            case 8: {
                write(read(m1) == read(m2), m3);
                break;
            }
            case 9: {
                offset += read(m1);
                break;
            }
            case 99:
                state = done;
                break;
        }
    }

    void run() {
        do {
            advance();
        } while (state == ok);
    }

    void init() {
        memory.clear();
        int idx = 0;
        for (auto elt : program) memory[idx++] = elt;
        cursor = 0;
        offset = 0;
        std::queue<long>().swap(inputs);
        std::queue<long>().swap(outputs);
        state = ok;
    }

    template <typename... Args>
    void start(Args... args) {
        init();
        add_input(args...);
        run();
    }
};