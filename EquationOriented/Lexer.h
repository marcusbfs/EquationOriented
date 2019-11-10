#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <cctype>

/*
program = "Variables" 
				assignment ";" 
		  "Parameters"
				assignment ";"
		  "Equations"
				expr_list

assignment = name "=" number

expr_list = expr ";" | expr_list expr ";"

expr = term | expr '+' term | expr '-' term

term = prim | term '*' prim | term '/' prim

prim = number | variable | parameter | '-' prime | '(' epxr ')'
*/
namespace Lexer {

	static std::map<std::string, std::string> Keywords = {{ "var", "VARIABLES" },
	{ "par", "PARAMETERS" }, { "eqns", "EQUATIONS" }
	};

	// Kind is for token type
	enum Kind : char {
		newline ,
		end , endofline ,
		// Basic operators
		plus, minus , mul, div, power,
		// functions
		exp , sin, cos ,
		equals,
		// Parenthesis
		p_open, p_close,
		// NUmber, variable, parameter
		number, variable , parameter ,
		equation ,
		// Keyword
		keyword 
	};

	struct Token {
		Kind  kind;
		double value;
		std::string name;
		unsigned long pos;
	};


	// Return precedence of operator
	static int Precedence(Kind op) {
		switch (op) {
		case Kind::power:
			return 4;
		case Kind::mul:
		case Kind::div:
			return 3;
		case Kind::plus:
		case Kind::minus:
			return 2;
		}
	}

	// Check if operator is left assiciative
	static bool isLeftAssociative(Kind op) {
		switch (op) {
		case Kind::power:
			return false;
		default:
			return true;
		}
	}

	// Check if operator is function
	static bool isFunction(Kind op) {
		switch (op) {
		case Kind::exp:
		case Kind::cos:
		case Kind::sin:
			return true;
		default:
			return false;
		}
	}

	class Lexer {
	private:
		std::stringstream m_stream;
		Token m_current_token;
		bool is_var = false;
		bool is_par = false;
		bool is_eq = false;

	public:
		Lexer() {}
		Lexer(std::string str);

		Token& getCurrentToken();
		Token fetchNextToken();
		void tokenize(const std::string& str);
		std::istream& getNextChar(char& chr);
	};
}

#endif // LEXER_H
