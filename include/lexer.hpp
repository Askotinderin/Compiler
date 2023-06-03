#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>

#include "checks.hpp"

typedef enum class TK : unsigned char{
    EOT,

    KEYWORD,
    IDENTIFIER,
    INVALID_IDENTIFIER,

    INT_NUMBER,
    FLOAT_NUMBER,
    HEX_NUMBER,
    BIN_NUMBER,
    INVALID_NUMBER,

    LOHI_EQ,
    SLL_EQ,
    SRL_EQ,
    ADD_EQ,
    SUB_EQ,
    MUL_EQ,
    DIV_EQ,
    MOD_EQ,
    OR_EQ,
    AND_EQ,
    XOR_EQ,
    LO_EQ,
    HI_EQ,
    EQ_EQ,
    NOT_EQ,
    SLL,
    SRL,
    LOR,
    LAND,
    ARR,
    SCOPE,
    IFDEF,
    DIV,
    MOD,
    EQ,
    HI,
    LO,
    XOR,
    OR,
    LNOT,
    BNOT,
    DOT,
    IF,
    THEN,

    POST_INC,
    PRE_INC,
    POST_DEC,
    PRE_DEC,
    BIN_ADD,
    UN_ADD,
    BIN_SUB,
    UN_SUB,
    BIN_MUL,
    UN_MUL,
    BIN_AND,
    UN_AND,

    INVALID_SEQUENCE

}TokenKind;

const std::unordered_map<std::string, TokenKind> op3_to_kind = {
    {"<=>", TK::LOHI_EQ},
    {"<<=", TK::SLL_EQ},
    {">>=", TK::SRL_EQ}
};

const std::unordered_map<std::string, TokenKind> op2_to_kind = {
    {"+=",  TK::ADD_EQ},
    {"-=",  TK::SUB_EQ},
    {"*=",  TK::MUL_EQ},
    {"/=",  TK::DIV_EQ},
    {"%=",  TK::MOD_EQ},
    {"|=",  TK::OR_EQ},
    {"&=",  TK::AND_EQ},
    {"^=",  TK::XOR_EQ},
    {"<=",  TK::LO_EQ},
    {">=",  TK::HI_EQ},
    {"==",  TK::EQ_EQ},
    {"!=",  TK::NOT_EQ},
    {"<<",  TK::SLL},
    {">>",  TK::SRL},
    {"||",  TK::LOR},
    {"&&",  TK::LAND},
    {"->",  TK::ARR},
    {"::",  TK::SCOPE},
    {"??",  TK::IFDEF}
};

const std::unordered_map<std::string, TokenKind> op_to_kind = {
    {"/",   TK::DIV},
    {"%",   TK::MOD},
    {"=",   TK::EQ},
    {">",   TK::HI},
    {"<",   TK::LO},
    {"^",   TK::XOR},
    {"|",   TK::OR},
    {"!",   TK::LNOT},
    {"~",   TK::BNOT},
    {".",   TK::DOT},
    {"?",   TK::IF},
    {":",   TK::THEN}
};

const std::unordered_map<std::string, std::array<TokenKind, 2>> op2_to_2kind = {
    {"++",  {TK::POST_INC,  TK::PRE_INC}},
    {"--",  {TK::POST_DEC,  TK::PRE_DEC}}
};

const std::unordered_map<std::string, std::array<TokenKind, 2>> op_to_2kind = {
    {"+",   {TK::BIN_ADD,   TK::UN_ADD}},
    {"-",   {TK::BIN_SUB,   TK::UN_SUB}},
    {"*",   {TK::BIN_MUL,   TK::UN_MUL}},
    {"&",   {TK::BIN_AND,   TK::UN_AND}}
};

const std::unordered_map<TokenKind, std::string> kind_to_str = {
    {TK::KEYWORD,               "Keyword: "},
    {TK::IDENTIFIER,            "Identifier: "},
    {TK::INVALID_IDENTIFIER,    "Invalid identifier: "},

    {TK::INT_NUMBER,            "Integer: "},
    {TK::FLOAT_NUMBER,          "Flaot: "},
    {TK::HEX_NUMBER,            "Hexadecimal: "},
    {TK::BIN_NUMBER,            "Binary: "},
    {TK::INVALID_NUMBER,        "Invalid number: "},

    {TK::LOHI_EQ,               "Three way comparison: "},
    {TK::SLL_EQ,                "Left shift equals: "},
    {TK::SRL_EQ,                "Right shift equals: "},
    {TK::ADD_EQ,                "Plus equals: "},
    {TK::SUB_EQ,                "Minus equals: "},
    {TK::MUL_EQ,                "Times equals: "},
    {TK::DIV_EQ,                "Divide equals: "},
    {TK::MOD_EQ,                "Modulo equals: "},
    {TK::OR_EQ,                 "Or equals: "},
    {TK::AND_EQ,                "And equals: "},
    {TK::XOR_EQ,                "Xor equals: "},
    {TK::LO_EQ,                 "Less or equal: "},
    {TK::HI_EQ,                 "Greater or equal: "},
    {TK::EQ_EQ,                 "Conditional equal: "},
    {TK::NOT_EQ,                "Not equal: "},
    {TK::SLL,                   "Left shift: "},
    {TK::SRL,                   "Right shift: "},
    {TK::LOR,                   "Logical or: "},
    {TK::LAND,                  "Logical and: "},
    {TK::ARR,                   "Member access of pointer to class: "},
    {TK::SCOPE,                 "Scope resolution: "},
    {TK::IFDEF,                 "Double tenrary operator: "},
    {TK::DIV,                   "Divide: "},
    {TK::MOD,                   "Modulo: "},
    {TK::EQ,                    "Assignment: "},
    {TK::HI,                    "Greater than: "},
    {TK::LO,                    "Less than: "},
    {TK::XOR,                   "Xor: "},
    {TK::OR,                    "Bitwise or: "},
    {TK::LNOT,                  "Logical not: "},
    {TK::BNOT,                  "Bitwise not: "},
    {TK::DOT,                   "Member access of class: "},
    {TK::IF,                    "Tenary if: "},
    {TK::THEN,                  "Tenary else: "},

    {TK::POST_INC,              "Postfix increment: "},
    {TK::PRE_INC,               "Prefix increment: "},
    {TK::POST_DEC,              "Postfix decrement: "},
    {TK::PRE_DEC,               "Prefix decrement: "},
    {TK::BIN_ADD,               "Plus: "},
    {TK::UN_ADD,                "Unary plus: "},
    {TK::BIN_SUB,               "Minus: "},
    {TK::UN_SUB,                "Unary minus: "},
    {TK::BIN_MUL,               "Times: "},
    {TK::UN_MUL,                "Contents of: "},
    {TK::BIN_AND,               "Bitwise and: "},
    {TK::UN_AND,                "Adress of: "},

    {TK::EOT,                   "End of file"}
};

const std::vector<TokenKind> operands = {
    TK::IDENTIFIER,
    TK::INVALID_IDENTIFIER,
    TK::INT_NUMBER,
    TK::FLOAT_NUMBER,
    TK::HEX_NUMBER,
    TK::BIN_NUMBER,
    TK::INVALID_NUMBER
};

struct Token {
    TokenKind kind;
    unsigned int pos;
    unsigned int line;
    unsigned int col;
    unsigned int len;
    std::string content;

    Token(TokenKind kind, unsigned int pos, unsigned int line, unsigned int col, unsigned int len, std::string content);
};

bool is_operand(const Token& t);

class Lexer {
private:
    std::vector<Token> tokens;
    unsigned int pos;
    unsigned int line;
    unsigned int bol;
    char c;
    std::string content;

    void lex_symbol(std::ifstream& file);
    void lex_number(std::ifstream& file);
    bool match_sequence (std::ifstream& file, std::string str);
public:
    Lexer ();
    std::vector<Token> operator() (std::ifstream& file);
};

void operator<< (std::ostream& stream, const Token& t);