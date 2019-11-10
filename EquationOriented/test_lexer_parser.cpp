#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "EqNode.h"
#include "Lexer.h"
#include "Parser.h"

void test_lexer();
void test_parser();

int main() {

  test_parser();

  std::getchar();
}

void test_parser() {

	std::string input = "VARIABLES "
							"x = 1;"
							"y = 3;"
						"PARAMETERS "
							"A = 20;"
							"B = 14;"
						"EQUATIONS "
							"x - y + 1 + 1 + 1 + 1 - A;"
							"x + y + 1*2*3*4- B;";

	Parser par;

	std::vector<std::shared_ptr<EqNode>> eqns = par.parse(input);

	int n = eqns.size();

	std::cout << "Number of equations: " << n << "\n";

	for (int i = 0; i < n; i++) {
		std::cout << "Equation " << i << " val: " <<
			eqns[i]->getValue() << std::endl;
	}

}

void test_lexer() {

	Lexer::Lexer lex;

	std::string input = "VARIABLES x = 1.0; y= 2.0; "
						"PARAMETERS A = 3.14; "
						"EQUATIONS x - y = A;";

	lex.tokenize(input);

	while (lex.fetchNextToken().kind != Lexer::Kind::end) {
		switch (lex.getCurrentToken().kind) {
		case Lexer::Kind::keyword:
			std::cout << "Keyword: " << lex.getCurrentToken().name<< std::endl;
			break;
		case Lexer::Kind::variable:
			std::cout << "Variable: " << lex.getCurrentToken().name<< std::endl;
			break;
		case Lexer::Kind::parameter:
			std::cout << "Parameter: " << lex.getCurrentToken().name<< std::endl;
			break;
		case Lexer::Kind::equation:
			std::cout << "Equation var: " << lex.getCurrentToken().name<< std::endl;
			break;
		case Lexer::Kind::number:
			std::cout << "Number: " << lex.getCurrentToken().value << std::endl;
			break;
		default:
			std::cout << "Operator: " << (char)lex.getCurrentToken().kind << std::endl;
		}
	}
}