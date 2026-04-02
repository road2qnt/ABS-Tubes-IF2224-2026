#include "lexer.hpp"
bool Lexer::transisiFirstSymbol(char c){
    switch (c){
        case '\'' : state = STATE_CS1; return true;
        case '+' : state = STATE_PLS; return true;
        case '-' : state = STATE_MIN; return true;
        case '*' : state = STATE_TMS; return true;
        case '/' : state = STATE_DIV; return true;
        case '=' : state = STATE_EQ1; return true;
        case '<' : state = STATE_LSS; return true;
        case '>' : state = STATE_GTR; return true;
        case ',' : state = STATE_COM; return true;
        case ';' : state = STATE_SCO; return true;
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
    while (file.get(c)){
        bool char_processed = false;
        while (!char_processed) {
            switch(state){
                case STATE_START:
                    if (isWhitespace(c)) { 
                        char_processed = true; 
                    } else if (isWord(c)) {
                        state = STATE_KID; 
                        lexeme += c;
                        char_processed = true;
                    } else if (isDigit(c)) {
                        state = STATE_NUM; 
                        lexeme += c;
                        char_processed = true;
                    } else {
                        if (transisiFirstSymbol(c)) {
                            lexeme += c;
                            char_processed = true;
                        } else {
                            state = STATE_ERR;
                            lexeme += c;
                            char_processed = true;
                        }
                    }
                    break;
                case STATE_KID:
                    if (isWord(c) || isDigit(c)){
                        lexeme += c;
                        char_processed = true;
                    } else {
                        addToken(true, state, lexeme);
                        lexeme = "";
                        state = STATE_START;
                    }
                    break;
                case STATE_NUM:
                    if (isDigit(c)){
                        lexeme += c;
                        char_processed = true;
                    } else if (c == '.') {
                        state = STATE_DOT;
                        lexeme += c;
                        char_processed = true;
                    } else {
                        addToken(true, state, lexeme);
                        lexeme = "";
                        state = STATE_START;
                    }
                    break;
                case STATE_DOT:
                    if (isDigit(c)){
                        state = STATE_FLO;
                        lexeme += c;
                        char_processed = true;
                    } else {
                        string int_part = lexeme.substr(0, lexeme.length()-1);
                        if (!int_part.empty()) {
                            addToken(true, STATE_NUM, int_part);
                        }
                        string prd = ".";
                        addToken(true, STATE_PRD, prd);
                        lexeme = "";
                        state = STATE_START;
                    }
                    break;
                case STATE_FLO:
                    if (isDigit(c)){
                        lexeme += c;
                        char_processed = true;
                    } else {
                        addToken(true, state, lexeme);
                        lexeme = "";
                        state = STATE_START;
                    }
                    break;
                case STATE_CS1:
                    lexeme += c;
                    char_processed = true;
                    if (c == '\'') {
                        if (lexeme.length() == 3) {
                            state = STATE_CV; 
                        } else {
                            state = STATE_CS2; 
                        }
                        addToken(true, state, lexeme);
                        lexeme = "";
                        state = STATE_START;
                    }
                    break;
                case STATE_CS2:
                case STATE_CV:
                case STATE_SV:
                case STATE_STR:
                    break;
                case STATE_PLS:
                case STATE_MIN:
                case STATE_TMS:
                case STATE_DIV:
                case STATE_COM:
                case STATE_SCO:
                case STATE_RPR:
                case STATE_LBR:
                case STATE_RBR:
                    addToken(true, state, lexeme);
                    lexeme = "";
                    state = STATE_START;
                    break;
                case STATE_EQ1: 
                    if (c == '=') {
                        state = STATE_EQ2;
                        lexeme += c;
                        char_processed = true;
                        addToken(true, state, lexeme);
                        lexeme = ""; state = STATE_START;
                    } else {
                        state = STATE_ERR;
                        addToken(true, state, lexeme);
                        lexeme = ""; state = STATE_START;
                    }
                    break;
                case STATE_EQ2:
                    break;
                case STATE_LSS: 
                    if (c == '=') {
                        state = STATE_LEQ; lexeme += c; char_processed = true;
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    } else if (c == '>') {
                        state = STATE_NEQ; lexeme += c; char_processed = true;
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    } else {
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    }
                    break;
                case STATE_GTR: 
                    if (c == '=') {
                        state = STATE_GEQ; lexeme += c; char_processed = true;
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    } else {
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    }
                    break;
                case STATE_NEQ:
                case STATE_LEQ:
                case STATE_GEQ:
                    break;
                case STATE_COL: 
                    if (c == '=') {
                        state = STATE_BEC; lexeme += c; char_processed = true;
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    } else {
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    }
                    break;
                case STATE_BEC:
                    break;
                case STATE_PRD: 
                    addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    break;
                case STATE_LPR: 
                    if (c == '*') {
                        state = STATE_KOM; lexeme += c; char_processed = true;
                    } else {
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    }
                    break;
                case STATE_LKOM1: 
                    state = STATE_LISI;
                case STATE_LISI:
                    lexeme += c; char_processed = true;
                    if (c == '}') {
                        state = STATE_LKOM2;
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    }
                    break;
                case STATE_LKOM2:
                case STATE_LKOM:
                    break;
                case STATE_KOM: 
                case STATE_ISI:
                    lexeme += c; char_processed = true;
                    if (c == '*') state = STATE_KOMF;
                    else state = STATE_ISI;
                    break;
                case STATE_KOMF: 
                    lexeme += c; char_processed = true;
                    if (c == ')') {
                        addToken(true, state, lexeme); lexeme = ""; state = STATE_START;
                    } else if (c == '*') {
                        state = STATE_KOMF;
                    } else {
                        state = STATE_ISI;
                    }
                    break;
                case STATE_ERR:
                    if (isWhitespace(c)){
                        addToken(true, state, lexeme);
                        lexeme = "";
                        state = STATE_START;
                        char_processed = true;
                    }
                    else {
                        lexeme += c;
                        char_processed = true;
                    }
                    break;
            }
        }
    }
    if (!lexeme.empty()) {
        addToken(true, state, lexeme);
    }
}
bool Lexer::isWord(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool Lexer::isDigit(char c){
    return c >= '0' && c <= '9';
}
bool Lexer::isWhitespace(char c){
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}
void Lexer::addToken(bool finish, int state, string& value) {
    if (finish){
        switch (state){
            case STATE_KID: {
                TokenType type = keyword(value);
                if (type == TokenType::IDENT) tokens.push_back(Token(type, value));
                else tokens.push_back(Token(type)); 
                break;
            }
            case STATE_NUM:
                tokens.push_back(Token(TokenType::INTCON, value));
                break;
            case STATE_FLO:
                tokens.push_back(Token(TokenType::REALCON, value));
                break;
            case STATE_CV:
                tokens.push_back(Token(TokenType::CHARCON, value));
                break;
            case STATE_CS2:
                tokens.push_back(Token(TokenType::STRING, value));
                break;
            case STATE_PLS: tokens.push_back(Token(TokenType::PLUS)); break;
            case STATE_MIN: tokens.push_back(Token(TokenType::MINUS)); break;
            case STATE_TMS: tokens.push_back(Token(TokenType::TIMES)); break;
            case STATE_DIV: tokens.push_back(Token(TokenType::RDIV)); break;
            case STATE_EQ2: tokens.push_back(Token(TokenType::EQL)); break;
            case STATE_LSS: tokens.push_back(Token(TokenType::LSS)); break;
            case STATE_NEQ: tokens.push_back(Token(TokenType::NEQ)); break;
            case STATE_LEQ: tokens.push_back(Token(TokenType::LEQ)); break;
            case STATE_GTR: tokens.push_back(Token(TokenType::GTR)); break;
            case STATE_GEQ: tokens.push_back(Token(TokenType::GEQ)); break;
            case STATE_COM: tokens.push_back(Token(TokenType::COMMA)); break;
            case STATE_COL: tokens.push_back(Token(TokenType::COLON)); break;
            case STATE_BEC: tokens.push_back(Token(TokenType::BECOMES)); break;
            case STATE_PRD: tokens.push_back(Token(TokenType::PERIOD)); break;
            case STATE_SCO: tokens.push_back(Token(TokenType::SEMICOLON)); break;
            case STATE_LPR: tokens.push_back(Token(TokenType::LPARENT)); break;
            case STATE_RPR: tokens.push_back(Token(TokenType::RPARENT)); break;
            case STATE_LBR: tokens.push_back(Token(TokenType::LBRACK)); break;
            case STATE_RBR: tokens.push_back(Token(TokenType::RBRACK)); break;
            case STATE_LKOM2:
            case STATE_KOMF:
                tokens.push_back(Token(TokenType::COMMENT, value)); break;
            case STATE_ERR:
                tokens.push_back(Token(TokenType::ERROR, value)); break;
            default:
                tokens.push_back(Token(TokenType::ERROR, value)); break;
        }
    }
}