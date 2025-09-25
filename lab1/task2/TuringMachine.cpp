#include <iostream>
#include <deque>
#include <string>

const char blank = '_';

class Tape
{
private:
    std::deque<char> data;
    size_t head_position = 0;
    size_t left_indent = 100;

public:
    Tape()
    {
        head_position = left_indent;
        data.resize(left_indent + 100, blank);
    }
    char read()
    {
        if (head_position < data.size())
        {
            return data[head_position];
        }
        else
        {
            return blank;
        }
    }
    void write(char symbol)
    {
        if (head_position > data.size())
        {
            data.resize(head_position + 1, blank);
        }
        data[head_position]=symbol;
    }
    void move(char ){

    }
};

class Transition
{
    std::string new_state;
    char new_symbol;
    char direction;
};

// using namespace std;

// enum Direction { LEFT = -1, STAY = 0, RIGHT = 1 };

// struct Transition {
//     string next_state;   // во что переходим
//     char   write;        // что записать
//     Direction move;      // куда двигать головку
// };

// // Лента: двусторонне расширяемый массив
// class Tape {
//     deque<char> cells;
//     int head;
//     char blank;
// public:
//     Tape(const string& input, char blank_symbol = '_')
//         : head(0), blank(blank_symbol)
//     {
//         for (char c : input) cells.push_back(c);
//         if (cells.empty()) cells.push_back(blank);
//     }

//     char read() const { return cells[head]; }

//     void write(char c) { cells[head] = c; }

//     void move(Direction d) {
//         if (d == LEFT) {
//             if (head == 0) cells.push_front(blank);
//             else --head;
//         } else if (d == RIGHT) {
//             ++head;
//             if (head >= (int)cells.size()) cells.push_back(blank);
//         }
//     }

//     string content() const {
//         // Вернём ленту без лишних пробелов
//         int L = 0, R = (int)cells.size()-1;
//         while (L <= R && cells[L] == blank) L++;
//         while (R >= L && cells[R] == blank) R--;
//         if (L > R) return string(1, blank);
//         return string(cells.begin()+L, cells.begin()+R+1);
//     }

//     void debug() const {
//         for (int i = 0; i < (int)cells.size(); ++i) {
//             if (i == head) cout << '[' << cells[i] << ']';
//             else cout << ' ' << cells[i] << ' ';
//         }
//         cout << "\n";
//     }
// };

// // Ключ для таблицы переходов
// struct Key {
//     string state;
//     char symbol;
//     bool operator==(const Key& o) const {
//         return state == o.state && symbol == o.symbol;
//     }
// };

// struct KeyHash {
//     size_t operator()(const Key& k) const {
//         return hash<string>()(k.state) * 31 + (unsigned char)k.symbol;
//     }
// };

// class TuringMachine {
//     unordered_map<Key, Transition, KeyHash> rules;
//     string state;
//     Tape tape;
//     string halt_state;
// public:
//     TuringMachine(const string& start_state, const string& halt, const string& input)
//         : state(start_state), tape(input), halt_state(halt) {}

//     void add_rule(const string& from, char read,
//                   const string& to, char write, Direction dir)
//     {
//         rules[{from, read}] = {to, write, dir};
//     }

//     void run(bool verbose = true) {
//         int steps = 0;
//         while (state != halt_state) {
//             if (verbose) {
//                 cout << "Step " << steps
//                      << " | state=" << state << " | tape: ";
//                 tape.debug();
//             }

//             char sym = tape.read();
//             auto it = rules.find({state, sym});
//             if (it == rules.end()) break; // нет правила — стоп

//             const Transition& tr = it->second;
//             tape.write(tr.write);
//             tape.move(tr.move);
//             state = tr.next_state;
//             ++steps;
//         }

//         cout << "HALT after " << steps << " steps.\n";
//         cout << "Final tape: " << tape.content() << "\n";
//     }
// };

// int main() {
//     // Начальное содержимое ленты: "111_"
//     TuringMachine tm("q0", "HALT", "1112_");

//     // Таблица переходов:
//     // q0 + '1' -> остаёмся в q0, пишем '1', идём вправо
//     tm.add_rule("q0", '1', "q0", '1', RIGHT);
//     tm.add_rule("q0", '2', "q1", '1', LEFT);
//     tm.add_rule("q1", '1', "q0", '1', RIGHT);

//     // q0 + '_' -> пишем '1', остаёмся на месте, переходим в HALT
//     tm.add_rule("q0", '_', "HALT", '1', STAY);

//     tm.run();  // пошаговое выполнение с выводом
// }
