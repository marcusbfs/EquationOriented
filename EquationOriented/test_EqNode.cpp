#include <iostream>
#include <memory>
#include <vector>
#include "EqNode.h"

#define log(x) std::cout << x << std::endl

//int main() {
//
//	std::shared_ptr<EqNode> x, y, z, eq, s1, ds1;
//
//	x = std::make_shared<EqNode>();
//	y = std::make_shared<EqNode>();
//	z = std::make_shared<EqNode>();
//	eq = std::make_shared<EqNode>();
//	s1 = std::make_shared<EqNode>();
//	ds1 = std::make_shared<EqNode>();
//
//	std::shared_ptr<EqNode> vars[3];
//
//	vars[0] = x;
//	vars[1] = y;
//	vars[2] = z;
//
//	s1->op = EqNode::OperatorType::Multiply;
//	s1->left = x;
//	s1->right = y;
//
//	x->op = EqNode::OperatorType::Parameter;
//	x->v = 2.0;
//
//	y->op = EqNode::OperatorType::Parameter;
//	y->v = 2.0;
//
//	z->op = EqNode::OperatorType::Parameter;
//	z->v = 2.0;
//	
//	eq->left = y;
//	eq->right = s1;
//	eq->op = EqNode::OperatorType::Multiply;
//
//	std::cout << "x address\: ";
//	log(x);
//
//	*ds1 = s1->derive(x);
//	eq = ds1;
//
//	std::cout << "x value: ";
//	log(x->value());
//	std::cout << "y value: ";
//	log(y->value());
//	std::cout << "z value: ";
//	log(z->value());
//
//	std::cout << "Eq depends on x? ";
//	log(eq->depends(x));
//
//	std::cout << "Eq depends on y? ";
//	log(eq->depends(y));
//
//	std::cout << "Eq depends on z? ";
//	log(eq->depends(z));
//	
//	std::cout << "Value: ";
//	log(eq->getValue());
//
//	std::cout << "Jacobian: \n";
//
//	for (int i = 0; i < 3; i++) {
//		std::cout << eq->getDerValue(vars[i]) << "\t";
//	}
//	std::cout << "\n";
//
//	std::getchar();
//}