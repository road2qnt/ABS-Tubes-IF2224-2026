#include <iostream>
#include "lexer.hpp"
#include "token.hpp"
using namespace std;
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <source_file>" << endl;
        return 1;
    }
    string filename = argv[1];
    Lexer lexer;
    lexer.DFA(filename);
    vector<Token> tokens = lexer.getTokens();
    for (const Token& token : tokens) {
        if (token.type == TokenType::IDENT || token.type == TokenType::INTCON || 
            token.type == TokenType::REALCON || token.type == TokenType::CHARCON || 
            token.type == TokenType::STRING || token.type == TokenType::ERROR ||
            token.type == TokenType::COMMENT) {
            cout << tokenToString(token.type) << " (" << token.value << ")" << endl;
        } else {
            cout << tokenToString(token.type) << endl;
        }
    }
    return 0;
}