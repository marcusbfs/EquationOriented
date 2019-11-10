#include "Shunting-yard_Parser.h"

std::shared_ptr<EqNode> ShuntingYardParser::parse(Lexer::Lexer & lex)
{
	m_lexer = &lex;
	return std::shared_ptr<EqNode>();
}
