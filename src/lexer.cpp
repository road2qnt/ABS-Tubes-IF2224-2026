#include "lexer.h"

// Implementasi DFA
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
                if (isWhitespace(c)) break; // Abaikan whitespace
                else if (isWord(c)) {
                    state = STATE_KID; 
                    lexeme += c;
                    progress = true;
                }
                else if (isDigit(c)) {
                    state = STATE_NUM; 
                    lexeme += c;
                }
                else progress = transisiFirstSymbol(c);
                break;
            case STATE_KID:
                progress = false;
                // Jika bukan karakter atau digit, maka input selesai di sana (Tentukan keyword atau ident di function addToken)
                if (!isWord(c) && !isDigit(c)){
                    addToken(true, state, lexeme);
                    lexeme = "";
                    state = STATE_START;
                    progress = true;
                }
                else {
                    lexeme += c;
                    progress = true;
                }
            case STATE_NUM:
                progress = false;
                if (!isDigit(c)){
                    if (c == '.'){
                        state = STATE_DOT;
                        lexeme += c;
                        progress = true;
                    }
                    else {
                        addToken(true, state, lexeme);
                        lexeme = "";
                        state = STATE_START;
                    }
                }
                else {
                    lexeme += c;
                    progress = true;
                } 
                break;
            case STATE_DOT:
                progress = false;
                if (isDigit(c)){
                    state = STATE_FLO;
                    lexeme += c;
                    progress = true;
                }
                else {
                    addToken(true, STATE_NUM, lexeme);
                    lexeme = "";
                    state = STATE_START;
                }
            case STATE_FLO:
                progress = false;
                if (!isDigit(c)){
                    addToken(true, state, lexeme);
                    lexeme = "";
                    state = STATE_START;
                }
                else {
                    lexeme += c;
                    progress = true;
                }
            case STATE_CS1:

            case STATE_CS2:

            case STATE_CV:

            case STATE_SV:

            case STATE_STR:

            case STATE_PLS:

            case STATE_MIN:

            case STATE_TMS:

            case STATE_DIV:

            case STATE_EQ1:

            case STATE_EQ2:

            case STATE_LSS:

            case STATE_NEQ:

            case STATE_LEQ:

            case STATE_GTR:

            case STATE_GEQ:

            case STATE_COM:

            case STATE_COL:

            case STATE_BEC:

            case STATE_PRD:

            case STATE_SCO:

            case STATE_LPR:

            case STATE_LKOM1:

            case STATE_LISI:

            case STATE_LKOM2:

            case STATE_LKOM:

            case STATE_RPR:

            case STATE_LBR:

            case STATE_RBR:

            case STATE_KOM:

            case STATE_ISI:

            case STATE_KOMF:

            case STATE_ERR:
                if (isWhitespace(c)){
                    addToken(true, state, lexeme);
                    lexeme = "";
                    state = STATE_START;
                }
                else {
                    lexeme += c;
                    progress = true;
                }
        }
    }

    
}

// ===HELPER===

// 1. Cek karakter atau bukan
bool Lexer::isWord(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

// 2. Cek digit atau bukan
bool Lexer::isDigit(char c){
    return c >= '0' && c <= '9';
}

// 3. Cek whitespace atau bukan
bool Lexer::isWhitespace(char c){
    return c == ' ' || c == '\t' || c == '\n';
}

// 4. Tambah token ke vector
void Lexer::addToken(bool finish, int state, string& value) {
    if (finish){
        switch (state){
            case STATE_KID:
                TokenType type = keyword(value);
                if (type == TokenType::IDENT) tokens.push_back(Token(type, value));
                else tokens.push_back(Token(type));
                break;
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
            // etc...
        }
    }
}
