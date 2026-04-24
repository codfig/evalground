#include "prompt_parser.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 0;
    }

    if (argc == 2 && string(argv[1]) == "prompt") {
        return executar_prompt(cin, cout, cerr) ? 0 : 1;
    }

    cerr << "Uso: eval prompt\n";
    return 1;
}
