#pragma once

#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

enum TokenType {
	Number,
	Identifier,
	Equals,
	OpenParen,
	CloseParen,
	BinaryOperator,
	Let
};

// Reserved Identifiers
typedef std::map<std::string, TokenType> ReservedIdentifiersMap;

void INIT_RESERVED_IDENTIFIER();

struct Token {
	std::string value;
	TokenType type;
};

std::vector<Token> tokenize(std::string &sourceCode);
std::vector<std::string> splitString(const std::string &src);