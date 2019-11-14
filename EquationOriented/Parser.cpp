#include "Parser.h"

void Parser::parse(const std::string& str)
{
	m_equations.clear();
	m_parameters.clear();
	m_variables.clear();

	m_lexer.tokenize(str);
	m_lexer.fetchNextToken();

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

	while (m_lexer.getCurrentToken().kind != Lexer::Kind::end) {
		this->m_equations.push_back(shunting_yard());
		this->match(";");
	}
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
	default:
		return nullptr;
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

std::shared_ptr<EqNode> Parser::shunting_yard()
{
	// https://en.wikipedia.org/wiki/Shunting-yard_algorithm

	std::stack<Lexer::Kind> operator_stack;
	std::stack<std::shared_ptr<EqNode>> output_qeue;

	while (m_lexer.getCurrentToken().kind != Lexer::endofline) {

		switch (m_lexer.getCurrentToken().kind) {
		// If its a number, put it to the output queue
		case Lexer::number:
			output_qeue.push(std::make_shared<EqNode>(m_lexer.getCurrentToken().value));
			break;
		// Equations (variabnle or parameter
		case Lexer::equation:
			// if its a parameter
			if (m_variables.find(m_lexer.getCurrentToken().name ) == m_variables.end()) 
				output_qeue.push(m_parameters[m_lexer.getCurrentToken().name]);
			// Else, it's a variable
			else 
				output_qeue.push(m_variables[m_lexer.getCurrentToken().name]);
			break;
		// If ts function, push it to the operator stack
		case Lexer::exp:
		case Lexer::sin:
		case Lexer::cos:
			operator_stack.push(m_lexer.getCurrentToken().kind);
			break;
		case Lexer::plus: case Lexer::minus:
		case Lexer::mul: case Lexer::div:
		case Lexer::power:
			while (
				operator_stack.size() > 0 && 
				(Lexer::isFunction(operator_stack.top())
					|| Lexer::Precedence(operator_stack.top()) > Lexer::Precedence(m_lexer.getCurrentToken().kind)
					|| (Lexer::Precedence(operator_stack.top()) == Lexer::Precedence(m_lexer.getCurrentToken().kind)
						&& Lexer::isLeftAssociative(operator_stack.top()))
					)
				&& operator_stack.top() != Lexer::Kind::p_open
				) {
				// pop operators from the operator stack onto the output queue.
				this->_shunting_yard_helper(
					operator_stack, output_qeue);

			} // end of while
			operator_stack.push(m_lexer.getCurrentToken().kind);
			break;

		case Lexer::p_open:
			operator_stack.push(m_lexer.getCurrentToken().kind);
			break;

		case Lexer::p_close:
			while (operator_stack.top() != Lexer::p_open) {
					this->_shunting_yard_helper(
						operator_stack, output_qeue);
			}
			if (operator_stack.top() == Lexer::Kind::p_open)
				operator_stack.pop();
			break;

		} // end of switch

		// go to next token
		m_lexer.fetchNextToken();
	} // end of while

	while (!operator_stack.empty()) {
			this->_shunting_yard_helper(
				operator_stack, output_qeue);
		} // end of while

	return output_qeue.top();
}

void Parser::_shunting_yard_helper(std::stack<Lexer::Kind>& operator_stack, std::stack<std::shared_ptr<EqNode>>& output_qeue )
{
	Lexer::Kind op = operator_stack.top();
	operator_stack.pop();
	switch (op) {
		// Operators
	case Lexer::Kind::plus: {
		std::shared_ptr<EqNode> right_child = output_qeue.top();
		output_qeue.pop();
		std::shared_ptr<EqNode> left_child = output_qeue.top();
		output_qeue.pop();
		output_qeue.push(std::make_shared<EqNode>(left_child, right_child, EqNode::Add));
		break;
	}
	case Lexer::Kind::minus: {
		std::shared_ptr<EqNode> right_child = output_qeue.top();
		output_qeue.pop();
		std::shared_ptr<EqNode> left_child = output_qeue.top();
		output_qeue.pop();
		output_qeue.push(std::make_shared<EqNode>(left_child, right_child, EqNode::Subtract));
		break;
	}
	case Lexer::Kind::mul: {
		std::shared_ptr<EqNode> right_child = output_qeue.top();
		output_qeue.pop();
		std::shared_ptr<EqNode> left_child = output_qeue.top();
		output_qeue.pop();
		output_qeue.push(std::make_shared<EqNode>(left_child, right_child, EqNode::Multiply));
		break;
	}
	case Lexer::Kind::div: {
		std::shared_ptr<EqNode> right_child = output_qeue.top();
		output_qeue.pop();
		std::shared_ptr<EqNode> left_child = output_qeue.top();
		output_qeue.pop();
		output_qeue.push(std::make_shared<EqNode>(left_child, right_child, EqNode::Divide));
		break;
	}
	case Lexer::Kind::power: {
		std::shared_ptr<EqNode> right_child = output_qeue.top();
		output_qeue.pop();
		std::shared_ptr<EqNode> left_child = output_qeue.top();
		output_qeue.pop();
		output_qeue.push(std::make_shared<EqNode>(left_child, right_child, EqNode::Power));
		break;
	}
		// Functions
	case Lexer::Kind::exp: {
		std::shared_ptr<EqNode> left_child = output_qeue.top();
		output_qeue.pop();
		output_qeue.push(std::make_shared<EqNode>(left_child, EqNode::Exp));
		break;
	}
	case Lexer::Kind::cos: {
		std::shared_ptr<EqNode> left_child = output_qeue.top();
		output_qeue.pop();
		output_qeue.push(std::make_shared<EqNode>(left_child, EqNode::Cos));
		break;
	}
	case Lexer::Kind::sin: {
		std::shared_ptr<EqNode> left_child = output_qeue.top();
		output_qeue.pop();
		output_qeue.push(std::make_shared<EqNode>(left_child, EqNode::Sin));
		break;
	}
	} // end of switch(op)
}

variables_map Parser::getParameters()
{
	return this->m_parameters;
}

variables_map Parser::getVariables()
{
	return this->m_variables;
}

Vector<std::shared_ptr<EqNode>> Parser::getEquations()
{
	Vector<std::shared_ptr<EqNode>> ret(m_equations.size());

	for (size_t i = 0; i < m_equations.size(); i++)
		ret(i) = m_equations[i];

	return ret;
}
