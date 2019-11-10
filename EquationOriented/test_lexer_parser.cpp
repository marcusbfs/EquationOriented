#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "EqNode.h"
#include "Lexer.h"
#include "Parser.h"
#include "Array.h"

void test_lexer();
void test_parser();

int main() {

	//test_lexer();
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
						" 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3;"
						"exp(3);";

	Parser par;

	par.parse(input);

	Vector<std::shared_ptr<EqNode>> eqns = par.getEquations();
	int n = eqns.size();

	std::cout << "Number of equations: " << n << "\n";

	for (int i = 0; i < n; i++) {
		std::cout << "Equation " << i << " val: " <<
			eqns(i)->getValue() << std::endl;
	}

}

void test_lexer() {

	Lexer::Lexer lex;

	std::string input = "VARIABLES x = 1.0; y= 2.0; "
						"PARAMETERS A = 3.14; "
						"EQUATIONS x - y = A;";
	input = "sin(x+2^3);";

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