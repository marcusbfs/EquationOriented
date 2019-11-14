#include "EqNode.h"

// Get the current value from node
double EqNode::value() const {
	return v;
}
// Update current value from node and returns it
double EqNode::getValue() {
	if (isLeaf())
		return this->v;
	else {
		// Updates current this->v val
		switch (op) {
			case OperatorType::Add:
				this->v = left->getValue() + right->getValue();
				break;
			case OperatorType::Subtract:
				this->v = left->getValue() - right->getValue();
				break;
			case OperatorType::Multiply:
				this->v = left->getValue() * right->getValue();
				break;
			case OperatorType::Divide:
				this->v = left->getValue() / right->getValue();
				break;
			case OperatorType::Power:
				this->v = std::pow(left->getValue(), right->getValue());
				break;
			case OperatorType::Exp:
				this->v = std::exp(left->getValue());
				break;
			case OperatorType::Sin:
				this->v = std::sin(left->getValue());
				break;
			case OperatorType::Cos:
				this->v = std::cos(left->getValue());
				break;
		}
		return this->v;
	}
}

// Get derivative of current node w.r. to var
double EqNode::getDerValue(const std::shared_ptr<EqNode>& var) const {
	if (isLeaf()) {
		if (this == var.get())
			return 1.0;
		else
			return 0.0;
	}
	else {
		switch (op) {
			case OperatorType::Add:
				return left->getDerValue(var) + right->getDerValue(var);
				break;
			case OperatorType::Subtract:
				return left->getDerValue(var) - right->getDerValue(var);
				break;
			case OperatorType::Multiply:
				return right->value()*left->getDerValue(var) + left->value()*right->getDerValue(var);
				break;
			case OperatorType::Divide:
				return (right->value()*left->getDerValue(var) - left->value()*right->getDerValue(var))/(right->value()*right->value());
				break;
			case OperatorType::Power:
				return right->value() * std::pow(left->value(), right->value() - 1.0) *left->getDerValue(var);
				break;
			case OperatorType::Exp:
				return std::exp(left->value())*left->getDerValue(var);
				break;
			case OperatorType::Sin:
				return std::cos(left->value())*left->getDerValue(var);
				break;
			case OperatorType::Cos:
				return -std::sin(left->value())*left->getDerValue(var);
				break;
		} // end of switch
	} // end of else
}
// Return true if current node depends on var
bool EqNode::depends(const std::shared_ptr<EqNode>& var) const {
	if (this->isLeaf()) {
		return this == var.get();
	}
	else {
		// If right is null, check only left
		if (right == nullptr)
			return left->depends(var);
		// Else, check if at least one of them is
		else
			return (left->depends(var) || right->depends(var));
	}
}

// Single operator OP(LEFT)
EqNode::EqNode(const std::shared_ptr<EqNode>& l, OperatorType o)
	: left(l), op(o)
{
}


// Normal operator left OP right
EqNode::EqNode(const std::shared_ptr<EqNode>& l, const std::shared_ptr<EqNode>& r, OperatorType o)
	: left(l), right(r), op(o)
{
}

// Double value
EqNode::EqNode(const double & val)
	: v(val)
{
}

// Returns true if current node is a leaf node (terminal node)
bool EqNode::isLeaf() const {
	return left == nullptr && right == nullptr;
}

// Return EqNode which represents the derivative of current EqNode
 EqNode& EqNode::derive(const std::shared_ptr<EqNode>& var) {

	 EqNode derivRoot;

	if (isLeaf()) {
		derivRoot.op = OperatorType::Parameter;
		if (depends(var)) 
			derivRoot.v = 1.0;
		else
			derivRoot.v = 0.0;
		return derivRoot;
	}
	else {
		switch (op) {
			case OperatorType::Add:
				derivRoot.op = op;
				derivRoot.left = std::make_shared<EqNode>();
				derivRoot.right = std::make_shared<EqNode>();
				*derivRoot.left = this->left->derive(var);
				*derivRoot.right = this->right->derive(var);
				break;
			case OperatorType::Subtract:
				derivRoot.op = op;
				derivRoot.left = std::make_shared<EqNode>();
				derivRoot.right = std::make_shared<EqNode>();
				*derivRoot.left = this->left->derive(var);
				*derivRoot.right = this->right->derive(var);
				break;
			case OperatorType::Multiply: // todo NEDDS TO BE FIXED
				// First part of summation: right * left'
				//std::shared_ptr<EqNode> firstPartNode = std::make_shared<EqNode>();
				EqNode firstPartNode;
				firstPartNode.op = OperatorType::Multiply;
				firstPartNode.left = std::make_shared<EqNode>();
				firstPartNode.right = std::make_shared<EqNode>();
				firstPartNode.left = this->right;
				*firstPartNode.right = this->left->derive(var);

				// Second part of summation: right' * left
				//std::shared_ptr<EqNode> secondPartNode = std::make_shared<EqNode>();
				EqNode secondPartNode;
				secondPartNode.op = OperatorType::Multiply;
				secondPartNode.left = std::make_shared<EqNode>();
				secondPartNode.right = std::make_shared<EqNode>();
				*secondPartNode.left = this->right->derive(var);
				secondPartNode.right = this->left;

				// Join
				derivRoot.op = OperatorType::Add;
				derivRoot.left = std::make_shared<EqNode>();
				derivRoot.right = std::make_shared<EqNode>();
				*derivRoot.left = firstPartNode;
				*derivRoot.right = secondPartNode;
				break;
		}
		return derivRoot;
	}
}
