#include "lexer.h"
#include <iostream>

/*
	Sets reserved identifiers.
	Must be called only once.
*/

ReservedIdentifiersMap reservedIdentifiers;
void INIT_RESERVED_IDENTIFIER() {
	reservedIdentifiers["let"] = TokenType::Let;
}

/*
	Removes first element from vector and returns it.
*/
std::string shift(std::vector<std::string>& src) {
	std::string current = src.front();
	src.erase(src.begin());
	return current;
}

/*
	Checks if a string is a number.
*/
bool isNumber(const std::string& str) {
	for (char c : str) {
		if (!isdigit(c))
			return false;
	}
	return true;
}

/*
	Checks if a string is a letter.
*/
bool isAlpha(const std::string& str) {
	for (char c : str) {
		if (!isalpha(c))
			return false;
	}
	return true;
}

/*
	Checks if a string is a skippable
	character, like \t or \n;
*/
bool isSkippable(char ch)
{
	return ch == ' ' || ch == '\t' || ch == '\n';
}

/*
	Splits the source code into individual words.
*/
std::vector<std::string> splitString(const std::string& src) {
	std::vector<std::string> words;
	std::string word;

	for (char c : src) {
		if (c != ' ') {
			word += c;
		}
		else if (!word.empty()) {
			words.push_back(word);
			word.clear();
		}
	}

	if (!word.empty()) {
		words.push_back(word);
	}

	return words;
}

/*
	Splits the src into individual words and processes
	each word to identify its token type.
*/
std::vector<Token> tokenize(std::string& sourceCode) {
	std::vector<Token> tokens;
	std::vector<std::string> src = splitString(sourceCode);

	while (!src.empty()) {
		// Open parenthesis
		if (src.front() == "(") {
			tokens.push_back({ shift(src), TokenType::OpenParen });
		}
		// Close parenthesis
		else if (src.front() == ")") {
			tokens.push_back({ shift(src), TokenType::CloseParen });
		}
		// Binary operators
		else if (src.front() == "+" || src.front() == "-" || src.front() == "*" || src.front() == "/") {
			tokens.push_back({ shift(src), TokenType::BinaryOperator });
		}
		// Equals
		else if (src.front() == "=") {
			tokens.push_back({ shift(src), TokenType::Equals });
		}
		// Multicharacter
		else {
			// Numbers
			if (isNumber(src.front())) {
				std::string number;
				while (!src.empty() && isNumber(src.front())) {
					number += shift(src);
				}

				tokens.push_back({ number, TokenType::Number });
			}
			// Identifiers
			else if (isAlpha(src.front())) {
				std::string identifier = shift(src);
				// check for reserved tokens
				ReservedIdentifiersMap::iterator it = reservedIdentifiers.find(identifier);
				if (it != reservedIdentifiers.end()) {
					tokens.push_back({ identifier, it->second });
				}
				else {
					tokens.push_back({ identifier, TokenType::Identifier });
				}
			}
			// Skippables
			else if (isSkippable(src.front()[0])) {
				shift(src);
			}
			else {
				std::cout << "What the fuck?" << std::endl;
				exit(1);
			}
		}
	}

	return tokens;
}