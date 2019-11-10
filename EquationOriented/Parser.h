#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <cctype>
#include <memory>
#include "EqNode.h"
#include "Lexer.h"
#include <vector>

/*
program = "Variables" 
				; | assignment ";" 
		  "Parameters"
				; | assignment ";"
		  "Equations"
				expr_list ";"

assignment = name "=" number

expr_list = expr | expr_list + expr  | expr_list - expr

expr = (term | expr '+' term | expr '-' term )

term = prim | term '*' prim | term '/' prim

prim = number | variable | parameter | '-' prime | '(' epxr ')'
*/

class Parser {

private:
	Lexer::Lexer m_lexer;
	std::map<std::string, std::shared_ptr<EqNode>> m_parameters;
	std::map<std::string, std::shared_ptr<EqNode>> m_variables;

public:

	// Handles the parsing
	std::vector<std::shared_ptr<EqNode>> parse(const std::string& str);

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

	// 

	void match(std::string str) {
		if (str == m_lexer.getCurrentToken().name)
			m_lexer.fetchNextToken();
		else
			std::cerr << "Error! Expected " << str <<
			", instead got "<< m_lexer.getCurrentToken().name<< std::endl;
	}
};

#endif // PARSER_h