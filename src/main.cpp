#include <iostream>
#include <fstream>
#include "lexer.hpp"
#include "token.hpp"
using namespace std;
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <source_file> [output_file]" << endl;
        return 1;
    }
    string filename = argv[1];
    Lexer lexer;
    lexer.DFA(filename);
    vector<Token> tokens = lexer.getTokens();

    ostream* out = &cout;
    ofstream outFile;
    if (argc >= 3) {
        outFile.open(argv[2]);
        if (!outFile.is_open()) {
            cout << "[!] Output file tidak bisa dibuka." << endl;
            return 1;
        }
        out = &outFile;
    }

    for (const Token& token : tokens) {
        if (token.type == TokenType::IDENT || token.type == TokenType::INTCON ||
            token.type == TokenType::REALCON || token.type == TokenType::CHARCON ||
            token.type == TokenType::STRING || token.type == TokenType::ERROR ||
            token.type == TokenType::COMMENT) {
            *out << tokenToString(token.type) << " (" << token.value << ")" << endl;
        } else {
            *out << tokenToString(token.type) << endl;
        }
    }
    return 0;
}
