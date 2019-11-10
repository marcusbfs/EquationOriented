#ifndef SHUNTING_YARD_PARSER_H
#define SHUNTING_YARD_PARSER_H

#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <cctype>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
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

	// Handles the algorihtm
	std::shared_ptr<EqNode> shunting_yard();

};

#endif // SHUNTING_YARD_PARSER_H

