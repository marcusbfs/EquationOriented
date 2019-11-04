#include "EqNode.h"

// Get the current value from node
double EqNode::value() const {
	return v;
}
// Update current value from node and returns it
double EqNode::getValue() {
	if (isLeaf())
		return value();
	else {
		// Updates current v val
		switch (op) {
			case OperatorType::Add:
				v = left->getValue() + right->getValue();
				break;
			case OperatorType::Subtract:
				v = left->getValue() - right->getValue();
				break;
			case OperatorType::Multiply:
				v = left->getValue() * right->getValue();
				break;
			case OperatorType::Divide:
				v = left->getValue() / right->getValue();
				break;
			case OperatorType::Power:
				v = std::pow(left->getValue(), right->getValue());
				break;
			case OperatorType::Exp:
				v = std::exp(left->getValue());
				break;
			case OperatorType::Sin:
				v = std::sin(left->getValue());
				break;
			case OperatorType::Cos:
				v = std::cos(left->getValue());
				break;
		}
		return value();
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
		double derVal;
		switch (op) {
			case OperatorType::Add:
				derVal = left->getDerValue(var) + right->getDerValue(var);
				break;
			case OperatorType::Subtract:
				derVal = left->getDerValue(var) - right->getDerValue(var);
				break;
			case OperatorType::Multiply:
				derVal = right->value()*left->getDerValue(var) + left->value()*right->getDerValue(var);
				break;
			case OperatorType::Divide:
				derVal = (right->value()*left->getDerValue(var) - left->value()*right->getDerValue(var))/(right->value()*right->value());
				break;
			case OperatorType::Power:
				derVal = right->value() * std::pow(left->value(), right->value() - 1.0) *left->getDerValue(var);
				break;
			case OperatorType::Exp:
				derVal = std::exp(left->value())*left->getDerValue(var);
				break;
			case OperatorType::Sin:
				derVal = std::cos(left->value())*left->getDerValue(var);
				break;
			case OperatorType::Cos:
				derVal = -std::sin(left->value())*left->getDerValue(var);
				break;
		}
		return derVal;
	}
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

// Returns true if current node is a leaf node (terminal node)
bool EqNode::isLeaf() const {
	return left == nullptr && right == nullptr;
}

// Return EqNode which represents the derivative of current EqNode
 EqNode EqNode::derive(const std::shared_ptr<EqNode>& var) {

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
