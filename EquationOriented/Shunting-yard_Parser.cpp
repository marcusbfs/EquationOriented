#include "Shunting-yard_Parser.h"

std::shared_ptr<EqNode> ShuntingYardParser::parse(Lexer::Lexer & lex)
{
	m_lexer = &lex;
	return this->shunting_yard();
}

std::shared_ptr<EqNode> ShuntingYardParser::shunting_yard()
{
	// https://en.wikipedia.org/wiki/Shunting-yard_algorithm

	std::stack<std::shared_ptr<EqNode>> operator_stack;
	std::queue<std::shared_ptr<EqNode>> output_qeue;

	while (m_lexer->getCurrentToken().kind != Lexer::endofline) {

		switch (m_lexer->getCurrentToken().kind) {
		// If its a number, put it to the output queue
		case Lexer::number:
			output_qeue.push(std::make_shared<EqNode>(m_lexer->getCurrentToken().value));
		// Variable:
			output_qeue.push(std::make_shared<EqNode>(m_lexer->getCurrentToken().value));
		}


		// go to next token
		m_lexer->fetchNextToken();
	}
}

