#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>

#include "checks.hpp"

enum class TK : unsigned char{
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

};

const std::unordered_map<std::string, TK> op_to_kind = {
    {"<=>", TK::LOHI_EQ},
    {"<<=", TK::SLL_EQ},
    {">>=", TK::SRL_EQ},
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
    {"??",  TK::IFDEF},
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

const std::unordered_map<std::string, std::array<TK, 2>> op_to_2kind = {
    {"++",  {TK::POST_INC,  TK::PRE_INC}},
    {"--",  {TK::POST_DEC,  TK::PRE_DEC}},
    {"+",   {TK::BIN_ADD,   TK::UN_ADD}},
    {"-",   {TK::BIN_SUB,   TK::UN_SUB}},
    {"*",   {TK::BIN_MUL,   TK::UN_MUL}},
    {"&",   {TK::BIN_AND,   TK::UN_AND}},
};

const std::unordered_map<TK, std::string> kind_to_str = {
    {TK::KEYWORD,               "Keyword: "},
    {TK::IDENTIFIER,            "Identifier: "},
    {TK::INVALID_IDENTIFIER,    "Invalid identifier: "},
    {TK::INT_NUMBER,            "Integer: "},
    {TK::FLOAT_NUMBER,          "Flaot: "},
    {TK::HEX_NUMBER,            "Hexadecimal: "},
    {TK::BIN_NUMBER,            "Binary: "},
    {TK::INVALID_NUMBER,        "Invalid number: "},
    {TK::EOT,                   "End of file"}
};

const std::vector<TK> operands = {
    TK::IDENTIFIER,
    TK::INVALID_IDENTIFIER,
    TK::INT_NUMBER,
    TK::FLOAT_NUMBER,
    TK::HEX_NUMBER,
    TK::BIN_NUMBER,
    TK::INVALID_NUMBER
};

struct Token {
    TK kind;
    unsigned int pos;
    unsigned int line;
    unsigned int col;
    unsigned int len;
    std::string content;

    Token(TK kind, unsigned int pos, unsigned int line, unsigned int col, unsigned int len, std::string content);
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