#ifndef EQNODE_H
#define EQNODE_H

#include <math.h>
#include <memory>


class EqNode {
	// Class for a equation node
public:
	// Type of nodesn
	enum OperatorType {
		Variable, Parameter, Equal, 
		Add, Subtract,
		Multiply, Divide, Power, Sin, Cos, Exp
	};


public:
	// Left child of this node
	std::shared_ptr<EqNode> left = nullptr;
	// Right child of this node
	std::shared_ptr<EqNode> right = nullptr;
	// Numerical value assigned to this node
	double v = 0.0;
	// Type of this node operator
	OperatorType op = OperatorType::Parameter;

public:
	// Constructors
	EqNode(){};
	~EqNode(){};
	// Normal operator left OP right
	EqNode(const std::shared_ptr<EqNode>& l, OperatorType o);
	// Single operator OP(LEFT)
	EqNode(const std::shared_ptr<EqNode>& l, const std::shared_ptr<EqNode>& r, OperatorType o);
	// Double value
	EqNode(const double& val);

	// Returns true if current node is a leaf node (terminal node)
	bool isLeaf() const;
	// Get the current value from node
	double value() const ;
	// Update current value from node and returns it
	double getValue();
	// Get derivative of current node w.r. to var
	double getDerValue(const std::shared_ptr<EqNode>& var) const;
	// Return true if current node depends on var
	bool depends(const std::shared_ptr<EqNode>& var) const;
	// Return EqNode which represents the derivative of current EqNode
	 EqNode& derive(const std::shared_ptr<EqNode>& var);
};

#endif // EQNODE_H
