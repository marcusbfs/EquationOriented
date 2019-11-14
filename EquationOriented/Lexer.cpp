#include "Lexer.h"

namespace Lexer {

	// Constructor with a string
	Lexer::Lexer(std::string str)
	{
		this->tokenize(str);
	}

	// Return the current token
	Token & Lexer::getCurrentToken()
	{
		return this->m_current_token;
	}

	// Go to next token
	Token Lexer::fetchNextToken()
	{
		// Lookahead char
		char lac = 0;

		// Read nonblank char from stream
		this->getNextChar(lac);

		switch (lac) {
			case 0: //end of file, stream 
				this->m_current_token.kind = Kind::end;
				return this->m_current_token;

			case '.':
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9': {
				this->m_current_token.kind = Kind::number;
				// Push back to stream and read the full number
				this->m_stream.putback(lac);
				this->m_stream >> this->m_current_token.value;
				return this->m_current_token;
			}

			case ';': 
				this->m_current_token.kind = Kind::endofline;
				this->m_current_token.name = ";";
				return this->m_current_token;
			case '+':
				this->m_current_token.kind = Kind::plus;
				this->m_current_token.name = "+";
				return this->m_current_token;
			case '-': 
				this->m_current_token.kind = Kind::minus;
				this->m_current_token.name = "-";
				return this->m_current_token;
			case '*':
				this->m_current_token.kind = Kind::mul;
				this->m_current_token.name = "*";
				return this->m_current_token;
			case '=':
				this->m_current_token.kind = Kind::equals;
				this->m_current_token.name = "=";
				return this->m_current_token;
			case '^':
				this->m_current_token.kind = Kind::power;
				this->m_current_token.name =  "^";
				return this->m_current_token;
			case '/':
				this->m_current_token.kind = Kind::div;
				this->m_current_token.name =  "/";
				return this->m_current_token;
			case '(':
				this->m_current_token.kind = Kind::p_open;
				this->m_current_token.name =  "(";
				return this->m_current_token;
			case ')':
				this->m_current_token.kind = Kind::p_close;
				this->m_current_token.name =  ")";
				return this->m_current_token;

			default: {
				// If is a alpha char, its a name
				if (std::isalpha(lac)) {
					this->m_current_token.name = lac;
					// Adds letters to name 
					while (m_stream.get(lac) && std::isalnum(lac))
						this->m_current_token.name += lac;

					// After this, lac is either a alpha or num
					// So we have to push back
					m_stream.putback(lac);

					// Check if name is a keyword
					if (m_current_token.name == Keywords["var"]) {
						is_var = true;
						is_par = is_eq = false;
						this->m_current_token.kind = Kind::keyword;
					}
					else if (m_current_token.name == Keywords["par"]) {
						is_par = true;
						is_var = is_eq = false;
						this->m_current_token.kind = Kind::keyword;
					}
					else if (m_current_token.name == Keywords["eqns"]) {
						is_eq = true;
						is_var = is_par = false;
						this->m_current_token.kind = Kind::keyword;
					}
					// Check if as function
					else if (m_current_token.name == "exp") {
						this->m_current_token.kind = Kind::exp;
					}
					else if (m_current_token.name == "cos") {
						this->m_current_token.kind = Kind::cos;
					}
					else if (m_current_token.name == "sin") {
						this->m_current_token.kind = Kind::sin;
					}
					// Else (not a keyword), it's a variable/parameter name
					else {
						if (is_var) {
							this->m_current_token.kind = Kind::variable;
						}
						else if (is_par)
							this->m_current_token.kind = Kind::parameter;
						else if (is_eq) {
							this->m_current_token.kind = Kind::equation;
						}
					}

					return this->m_current_token;
				}
				else { // Error
					std::cerr << "Syntax error: " << lac << std::endl;
					this->m_current_token.kind = Kind::endofline;
					return this->m_current_token;
				}
			}
		} // end of switch statement
	} // end of function fetchNextToken

	// Sent str to stringstream
	void Lexer::tokenize(const std::string & str)
	{
		m_stream.clear();
		m_stream << str;
	}

	// Get next nonblank char
	std::istream & Lexer::getNextChar(char & chr)
	{
		while (this->m_stream.get(chr) && std::isblank(chr));
		return this->m_stream;
	}
}
