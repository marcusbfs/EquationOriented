#ifndef SHUNTING_YARD_PARSER_H
#define SHUNTING_YARD_PARSER_H

#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <cctype>
#include <memory>
#include <vector>
#include "EqNode.h"
#include "Lexer.h"


class ShuntingYardParser {

private:
	Lexer::Lexer* m_lexer;
	std::map<std::string, std::shared_ptr<EqNode>> m_parameters;
	std::map<std::string, std::shared_ptr<EqNode>> m_variables;

public:

	// Handles the parsing
	std::shared_ptr<EqNode> parse(Lexer::Lexer& lex);

	// Handles the entire program
	std::vector<std::shared_ptr<EqNode>> program();

	// Handles assignments
	std::shared_ptr<EqNode> assignment();

	// Handles lists of expressions
	std::shared_ptr<EqNode> expr_list();

	// Handles expressions
	std::shared_ptr<EqNode> expr();

	// Handles addition and subtraction
	std::shared_ptr<EqNode> term();
	
	// Handles assignments
	std::shared_ptr<EqNode> prim();

	void match(std::string str) {
		if (str == m_lexer.getCurrentToken().name)
			m_lexer.fetchNextToken();
		else
			std::cerr << "Error! Expected " << str <<
			", instead got "<< m_lexer.getCurrentToken().name<< std::endl;
	}
};

#endif // SHUNTING_YARD_PARSER_H

