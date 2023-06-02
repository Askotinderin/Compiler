#include "lexer.hpp"

Token::Token(TK kind, unsigned int pos, unsigned int line, unsigned int col, unsigned int len, std::string content)
    : kind(kind), pos(pos), line(line), col(col), len(len), content(content) {}

bool is_operand(const Token& t) {
    for (const auto& op : operands) {
        if (t.kind == op) return true;
    }
    return false;
}

Lexer::Lexer () {
    this->tokens = std::vector<Token>();
    this->pos = 0;
    this->bol = 0;
    this->line = 0;
    this->content = "";
}

void Lexer::lex_symbol(std::ifstream& file) {
    do {
        content += c;
        file >> std::noskipws >> c;
    }
    while (!file.eof() && (std::isalnum(c) || c == '_'));

    if (is_keyword(content))
        tokens.push_back(Token(TK::KEYWORD, pos, line + 1, pos - bol + 1, content.length(), content));
    else if (is_identifier(content))
        tokens.push_back(Token(TK::IDENTIFIER, pos, line + 1, pos - bol + 1, content.length(), content));
    else
        tokens.push_back(Token(TK::INVALID_IDENTIFIER, pos, line + 1, pos - bol + 1, content.length(), content));
    pos += content.length();
    content = "";
}

void Lexer::lex_number(std::ifstream& file) {
    do {
        content += c;
        file >> std::noskipws >> c;
    }
    while (!file.eof() && (std::isalnum(c) || c == '_' || c == '.'));

    if (is_int(content))
        tokens.push_back(Token(TK::INT_NUMBER, pos, line + 1, pos - bol + 1, content.length(), content));
    else if (is_float(content))
        tokens.push_back(Token(TK::FLOAT_NUMBER, pos, line + 1, pos - bol + 1, content.length(), content));
    else if (is_hex(content))
        tokens.push_back(Token(TK::HEX_NUMBER, pos, line + 1, pos - bol + 1, content.length(), content));
    else if (is_bin(content))
        tokens.push_back(Token(TK::BIN_NUMBER, pos, line + 1, pos - bol + 1, content.length(), content));
    else
        tokens.push_back(Token(TK::INVALID_NUMBER, pos, line + 1, pos - bol + 1, content.length(), content));

    pos += content.length();
    content = "";
}

bool Lexer::match_sequence (std::ifstream& file, std::string str) {
    for (unsigned int i = 0; i < str.length(); i++) {
        file >> std::noskipws >> c;
        if (file.eof() || c != str[i]) {
            for (unsigned int j = 0; j < i + 1; j++) {
                file.unget();
            }
            return false;
        }
    }
    return true;
}

std::vector<Token> Lexer::operator() (std::ifstream& file) {
    file >> std::noskipws >> c;
    while (!file.eof()) {
        if (c == ' ') {
            pos++;
            file >> std::noskipws >> c;
            continue;
        }
        if (c == '\n') {
            pos++;
            bol = pos;
            line++;
            file >> std::noskipws >> c;
            continue;
        }

        if (std::isalpha(c) || c == '_') {
            lex_symbol(file);
            continue;
        }
        if (std::isdigit(c)) {
            lex_number(file);
            continue;
        }

        bool found = false;
        for (const auto& [key, value] : op_to_kind) {
            if (match_sequence(file, key)) {
                tokens.push_back(Token(value, pos, line + 1, pos - bol + 1, key.length(), key));
                pos += key.length();
                found = true;
                break;
            }
        }
        if (found) continue;
        for (const auto& [key, value] : op_to_2kind) {
            if (match_sequence(file, key)) {
                if (is_operand(tokens[tokens.size() - 1])) {
                    tokens.push_back(Token(value[0], pos, line + 1, pos - bol + 1, key.length(), key));
                }
                else {
                    tokens.push_back(Token(value[1], pos, line + 1, pos - bol + 1, key.length(), key));
                }
                pos += key.length();
                found = true;
                break;
            }
        }
        if (found) continue;
        content += c;
        tokens.push_back(Token(TK::INVALID_SEQUENCE, pos, line + 1, pos - bol + 1, 1, content));
        content = "";
        pos++;
        file >> std::noskipws >> c;

    }
    tokens.push_back(Token(TK::EOT, pos, line + 1, pos - bol + 1, 1, "\0"));
    return tokens;
}

void operator<< (std::ostream& stream, const Token& t) {
    for (const auto& [key, value] : kind_to_str) {
        if (t.kind == key) {
            stream << value << t.content << "\nLine: " << t.line << "\nColumn: " << t.col << "\nLength: " << t.len << "\n\n";
            return;
        }
    }
}