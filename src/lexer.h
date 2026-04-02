#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <iostream>
#include <fstream>
#include <vector>

// STATE DFA - Penjelasan State ada di Laporan!
enum state{
    STATE_START, // 0
    STATE_KID, // 1
    STATE_NUM, // 2
    STATE_DOT, // 3
    STATE_FLO, // 4
    STATE_CS1, // 5
    STATE_CS2, // 6
    STATE_CV, // 7
    STATE_SV, // 8
    STATE_STR, // 9
    STATE_PLS, // 10
    STATE_MIN, // 11
    STATE_TMS, // 12
    STATE_DIV, // 13
    STATE_EQ1, // 14
    STATE_EQ2, // 15
    STATE_LSS, // 16
    STATE_NEQ, // 17
    STATE_LEQ, // 18
    STATE_GTR, // 19
    STATE_GEQ, // 20
    STATE_COM, // 21
    STATE_COL, // 22
    STATE_BEC, // 23
    STATE_PRD, // 24
    STATE_LPR, // 25
    STATE_LKOM1, // 26
    STATE_LISI, // 27
    STATE_LKOM2, // 28
    STATE_LKOM, // 29
    STATE_RPR, // 30
    STATE_LBR, // 31
    STATE_RBR, // 32
    STATE_KOM, // 33
    STATE_ISI, // 34
    STATE_KOMF // 35
};

class Lexer {
private:
    vector<Token> tokens;
    int state;
    char c;
private:
    Lexer(){
        tokens = vector<Token>();
        state = STATE_START;
    }
    void DFA(const string& filename); 
    
    bool transisiFirstSymbol(char c);
    bool isWord(char c);
    bool isDigit(char c);
    bool isWhitespace(char c);
};








#endif