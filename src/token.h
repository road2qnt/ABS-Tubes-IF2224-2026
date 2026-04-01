#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;


enum class TokenType {
    
    INTCON, REALCON, CHARCON, STRING,//4
    
    NOTSY, ANDSY, ORSY,//7 (3)
    
    PLUS, MINUS, TIMES, IDIV, RDIV, IMOD,//13 (6)
    
    EQL, NEQ, GTR, GEQ, LSS, LEQ,//19(6)
    
    LPARENT, RPARENT, LBRACK, RBRACK,//23(4)
    COMMA, SEMICOLON, PERIOD, COLON, BECOMES,//28 (5)
    
    CONSTSY, TYPESY, VARSY, FUNCTIONSY, PROCEDURESY,//33 (5)
    ARRAYSY, RECORDSY, PROGRAMSY,//36 (3)
    
    IDENT,//37(1)
    
    BEGINSY, IFSY, CASESY, REPEATSY, WHILESY, FORSY,//43 (6)
    ENDSY, ELSESY, UNTILSY, OFSY, DOSY, TOSY, DOWNTOSY, THENSY,//51(8)
    
    COMMENT,//52(1)
    
    ERROR
};


struct Token {
    TokenType type;
    string value;

    Token(TokenType type, const string& value = "");
};


string tokenToString(TokenType type);

TokenType keyword(const string& ident);

#endif
