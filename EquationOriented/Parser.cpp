#include "Parser.h"

std::vector<std::shared_ptr<EqNode>> Parser::parse(const std::string & str)
{
	m_lexer.tokenize(str);
	m_lexer.fetchNextToken();
	return program();
}

std::vector<std::shared_ptr<EqNode>> Parser::program()
{
	// retriver keywords
	std::string kw_vars = Lexer::Keywords["var"];
	std::string kw_pars = Lexer::Keywords["par"];
	std::string kw_eqns = Lexer::Keywords["eqns"];

	// VARIABLES
	this->match(kw_vars);

	while (m_lexer.getCurrentToken().name != kw_pars){
		switch (m_lexer.getCurrentToken().kind) {
		case Lexer::Kind::variable:
			this->assignment();
		case Lexer::Kind::endofline:
			this->match(";");
		}
	}

	// PARAMETERS
	this->match(kw_pars);

	while (m_lexer.getCurrentToken().name !=kw_eqns) {
		switch (m_lexer.getCurrentToken().kind) {
		case Lexer::Kind::parameter:
			this->assignment();
		case Lexer::Kind::endofline:
			this->match(";");
		}
	}

	// EQUATIONS
	this->match(kw_eqns);

	std::vector<std::shared_ptr<EqNode>> vec;

	while (m_lexer.getCurrentToken().kind != Lexer::Kind::end) {
		vec.push_back(expr_list());
		this->match(";");
	}

	return vec;
}

std::shared_ptr<EqNode> Parser::assignment()
{
	std::shared_ptr<EqNode> left = std::make_shared<EqNode>();

	switch (m_lexer.getCurrentToken().kind) {

	case Lexer::Kind::variable: {
		std::string var_name = m_lexer.getCurrentToken().name;
		m_variables[var_name] = left;
		m_lexer.fetchNextToken();
		this->match("=");
		m_variables[var_name]->v = m_lexer.getCurrentToken().value;
		m_lexer.fetchNextToken();
		return left;
	}
	case Lexer::Kind::parameter: {
		std::string var_name = m_lexer.getCurrentToken().name;
		m_parameters[var_name] = left;
		m_lexer.fetchNextToken();
		this->match("=");
		m_parameters[var_name]->v = m_lexer.getCurrentToken().value;
		m_lexer.fetchNextToken();
		return left;
	}
	}
}

std::shared_ptr<EqNode> Parser::expr_list()
{
	std::shared_ptr<EqNode> left = expr();
	std::shared_ptr<EqNode> right;
	std::shared_ptr<EqNode> tmp;

	if (m_lexer.getCurrentToken().kind == Lexer::Kind::plus) {
		m_lexer.fetchNextToken();
		right = expr_list();
		tmp = left;
		left = std::make_shared<EqNode>(tmp, right, EqNode::OperatorType::Add);
	}

	if (m_lexer.getCurrentToken().kind == Lexer::Kind::minus) {
		m_lexer.fetchNextToken();
		right = expr_list();
		tmp = left;
		left = std::make_shared<EqNode>(tmp, right, EqNode::OperatorType::Subtract);
	}

	return left;
}

std::shared_ptr<EqNode> Parser::expr()
{
	std::shared_ptr<EqNode> left = term();
	std::shared_ptr<EqNode> right;
	std::shared_ptr<EqNode> tmp;

	if (m_lexer.getCurrentToken().kind == Lexer::Kind::plus) {
		m_lexer.fetchNextToken();
		right = term();
		tmp = left;
		left = std::make_shared<EqNode>(tmp, right, EqNode::OperatorType::Add);
	}

	if (m_lexer.getCurrentToken().kind == Lexer::Kind::minus) {
		m_lexer.fetchNextToken();
		right = term();
		tmp = left;
		left = std::make_shared<EqNode>(tmp, right, EqNode::OperatorType::Subtract);
	}

	return left;
}

std::shared_ptr<EqNode> Parser::term()
{
	std::shared_ptr<EqNode> left = prim();
	std::shared_ptr<EqNode> right;
	std::shared_ptr<EqNode> tmp;

	if (m_lexer.getCurrentToken().kind == Lexer::Kind::mul) {
		m_lexer.fetchNextToken();
		right = prim();
		tmp = left;
		left = std::make_shared<EqNode>(tmp, right, EqNode::OperatorType::Multiply);
	}

	if (m_lexer.getCurrentToken().kind == Lexer::Kind::div) {
		m_lexer.fetchNextToken();
		right = prim();
		tmp = left;
		left = std::make_shared<EqNode>(tmp, right, EqNode::OperatorType::Divide);
	}

	return left;
}

std::shared_ptr<EqNode> Parser::prim()
{
	std::shared_ptr<EqNode> left;

	switch (m_lexer.getCurrentToken().kind) {
	case Lexer::Kind::number:
		left = std::make_shared<EqNode>(m_lexer.getCurrentToken().value);
		left->op = EqNode::OperatorType::Parameter;
		break;
	case Lexer::Kind::equation:
		// Checks if is a parameter
		if (m_variables.find(m_lexer.getCurrentToken().name ) == m_variables.end()) {
			left = m_parameters[m_lexer.getCurrentToken().name];
			left->op = EqNode::OperatorType::Parameter;
		}
		// Else, it's a variable
		else {
			left = m_variables[m_lexer.getCurrentToken().name];
			left->op = EqNode::OperatorType::Variable;
		}
		break;
	case Lexer::Kind::minus:
		left = prim();
		left->v = -left->v;
		break;
	case Lexer::Kind::p_open:
		// Eat '('
		m_lexer.fetchNextToken();
		left = expr();
		break;
	}

	m_lexer.fetchNextToken();
	return left;
}
