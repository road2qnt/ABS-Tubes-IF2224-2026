#include "lexer.h"

bool Lexer::isWord(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::isDigit(char c){
    return c >= '0' && c <= '9';
}

bool Lexer::isWhitespace(char c){
    return c == ' ' || c == '\t' || c == '\n';
}

bool Lexer::transisiFirstSymbol(char c){
    switch (c){
        case '"' : state = STATE_CS1; return true;
        case '+' : state = STATE_PLS; return true;
        case '-' : state = STATE_MIN; return true;
        case '*' : state = STATE_TMS; return true;
        case '/' : state = STATE_DIV; return true;
        case '=' : state = STATE_EQ1; return true;
        case '<' : state = STATE_LSS; return true;
        case '>' : state = STATE_GTR; return true;
        case ',' : state = STATE_COM; return true;
        case ':' : state = STATE_COL; return true;
        case '.' : state = STATE_PRD; return true;
        case '(' : state = STATE_LPR; return true;
        case ')' : state = STATE_RPR; return true;
        case '[' : state = STATE_LBR; return true;
        case ']' : state = STATE_RBR; return true;
        case '{' : state = STATE_LKOM1; return true;
    }
    return false;
}

void Lexer::DFA(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()){
        cout << "[!] File tidak bisa dibuka.\n";
        return;
    }

    string lexeme;
    bool progress = false, finish = false;
    while (progress || file.get(c)){
        switch(state){
            case STATE_START:
                if (isWord(c)) state = STATE_NUM;
                else if (isDigit(c)) state = STATE_KID;
                else progress = transisiFirstSymbol(c);
                break;
            case STATE_KID:
                
            case STATE_NUM:

            case STATE_DOT:

            case STATE_FLO:

            case STATE_CS1:

            case STATE_CS2:

            case STATE_CV:
        }
    }
}