#include "main.hpp"

int main (int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Invalid arguments. Usage is ./bin file.c" << std::endl;
        exit(1);
    }

    std::ifstream file;
    file.open(argv[1]);
    if (file.is_open()) {
        Lexer lex;
        std::vector<Token> tokens = lex(file);
        for (const Token& token : tokens) {
            std::cout << token;
        }
    }
    else {
         std::cerr << "No such file in directory" << std::endl;
         exit(1);
    }
    file.close();
    return 0;
}