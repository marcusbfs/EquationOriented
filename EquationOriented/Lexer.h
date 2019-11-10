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
		end = '0', endofline = ';', plus = '+',
		newline = '\n',
		minus = '-', mul = '*', div = '/',
		equals = '=',
		p_open = '(', p_close = ')',
		number = 'n', variable = 'v', parameter = 'p',
		equation = 'e',
		keyword = 'k'
	};

	struct Token {
		Kind  kind;
		double value;
		std::string name;
		unsigned long pos;
	};

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
