#include <iostream>
#include "lexer.h"

int main(void) {
	INIT_RESERVED_IDENTIFIER();

	std::string src = "let no = 12";
	std::vector<Token> tokens = tokenize(src);

	for (int i = 0; i < tokens.size(); i++) {
		std::cout << "Value: " << tokens[i].value << " Type: " << tokens[i].type << std::endl;
	}

	return 0;
}