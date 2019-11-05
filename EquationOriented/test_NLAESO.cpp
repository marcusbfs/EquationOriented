#include <iostream>
#include <memory>
#include <vector>
#include "EqNode.h"
#include "ESO.h"

#define log(x) std::cout << x << std::endl

class Concrete2dExample : INumericNLAESO {

public:

	std::shared_ptr<EqNode> eq1, eq2, x, y;
	unsigned long numberEqns = 2;
	unsigned long numberVars = 2;
	std::vector<std::shared_ptr<EqNode>> EqnSystem;

	Concrete2dExample() {

		// Construct equations:
		// eq1 = 2 * x + 3 * y - 6
		// eq2 = 4 * x + 9 * y - 15


		// Create eq1 and eq1
		eq1 = std::make_shared<EqNode>();
		eq2 = std::make_shared<EqNode>();

		EqnSystem.resize(numberEqns);
		EqnSystem[0] = eq1;
		EqnSystem[1] = eq2;

		// Declare vars
		x = std::make_shared<EqNode>();
		x->op = EqNode::OperatorType::Variable;
		x->v = 0.0;

		y = std::make_shared<EqNode>();
		y->op = EqNode::OperatorType::Variable;
		y->v = 0.0;
		
		// Declare constants
		std::shared_ptr<EqNode> a1, b1, c1, a2, b2, c2;

		a1 = std::make_shared<EqNode>();
		a1->op = EqNode::OperatorType::Parameter;
		a1->v = 2.0;

		b1 = std::make_shared<EqNode>();
		b1->op = EqNode::OperatorType::Parameter;
		b1->v = 3.0;

		c1 = std::make_shared<EqNode>();
		c1->op = EqNode::OperatorType::Parameter;
		c1->v = -6.0;

		a2 = std::make_shared<EqNode>();
		a2->op = EqNode::OperatorType::Parameter;
		a2->v = 4.0;

		b2 = std::make_shared<EqNode>();
		b2->op = EqNode::OperatorType::Parameter;
		b2->v = 9.0;

		c2 = std::make_shared<EqNode>();
		c2->op = EqNode::OperatorType::Parameter;
		c2->v = -15.0;

		// term_a1 = 2 * x
		// term_b1 = 3 * y 
		// term_c1 = term_a1 + term_b1
		// eq1 = term_c1 + c1

		std::shared_ptr<EqNode> term_a1, term_b1, term_c1;
		std::shared_ptr<EqNode> term_a2, term_b2, term_c2;

		term_a1 = std::make_shared<EqNode>();
		term_b1 = std::make_shared<EqNode>();
		term_c1 = std::make_shared<EqNode>();
		term_a2 = std::make_shared<EqNode>();
		term_b2 = std::make_shared<EqNode>();
		term_c2 = std::make_shared<EqNode>();

		term_a1->op = EqNode::OperatorType::Multiply;
		term_a1->left = a1;
		term_a1->right = x;

		term_b1->op = EqNode::OperatorType::Multiply;
		term_b1->left = b1;
		term_b1->right = y;

		term_c1->op = EqNode::OperatorType::Add;
		term_c1->left = term_a1;
		term_c1->right = term_b1;

		eq1->op = EqNode::OperatorType::Add;
		eq1->left = term_c1;
		eq1->right = c1;

		// term_a2 = 4 * x
		// term_b2 = 9 * y 
		// term_c2 = term_a2 + term_b2
		// eq2 = term_c2 + c2

		term_a2 = std::make_shared<EqNode>();
		term_b2 = std::make_shared<EqNode>();
		term_c2 = std::make_shared<EqNode>();
		term_a2 = std::make_shared<EqNode>();
		term_b2 = std::make_shared<EqNode>();
		term_c2 = std::make_shared<EqNode>();

		term_a2->op = EqNode::OperatorType::Multiply;
		term_a2->left = a2;
		term_a2->right = x;

		term_b2->op = EqNode::OperatorType::Multiply;
		term_b2->left = b2;
		term_b2->right = y;

		term_c2->op = EqNode::OperatorType::Add;
		term_c2->left = term_a2;
		term_c2->right = term_b2;

		eq2->op = EqNode::OperatorType::Add;
		eq2->left = term_c2;
		eq2->right = c2;
	}

	std::vector<double> GetAllVariables() {
		std::vector<double> AllVariables(2);
		AllVariables[0] = x->value();
		AllVariables[1] = y->value();
		return AllVariables;
	}

	void SetAllVariables(const std::vector<double>& VarValues) {
		x->v = VarValues[0];
		y->v = VarValues[1];
	}

	void GetParameterList(std::vector<std::shared_ptr<EqNode>>& TheListOfParameters) {
		TheListOfParameters.resize(numberVars);
		TheListOfParameters[0] = x;
		TheListOfParameters[1] = y;
	}

	unsigned long GetNumEqns() {
		return numberEqns;
	}

	unsigned long GetNumVars() {
		return numberVars;
	}

	void GetAllResiduals(std::vector<double>& AllResiduals) {
		AllResiduals[0] = eq1->getValue();
		AllResiduals[1] = eq2->getValue();
	}

	void GetAllJacobianValues(std::vector<std::vector<double>>& AllJacobianValues) {
		/* The Jacobian has the followin strucutre:
			| df1/x1	df1/x2	... dfn/xn |
			| df2/x1	df2/x2	... df2/xn |
			| .......................      |
			| dfn/x1	dfn/x2	... dfn/xn |
		*/

		unsigned int i, j;

		std::vector<std::shared_ptr<EqNode>> parametersList(numberVars);
		GetParameterList(parametersList);

		for (i = 0; i < numberEqns; i++) {
			for (j = 0; j < numberVars; j++) {
				AllJacobianValues[i][j] = EqnSystem[i]->getDerValue(parametersList[j]);
			}
		}
	}

};


#define printVec(x) std::cout << x[0] << ", " << x[1] <<"\n";
#define printJac(x) std::cout << x[0][0] << ", " << x[0][1] <<"\n" << x[1][0] << ", " << x[1][1] <<"\n" ;


int main() {

	std::shared_ptr<Concrete2dExample> eso = std::make_shared<Concrete2dExample>();

	std::vector<double> AllResiduals, AllVariables;
	std::vector<std::vector<double>> AllJacobians;
	std::vector<std::shared_ptr<EqNode>> ParametersList;
	
	std::shared_ptr<EqNode> x = std::make_shared<EqNode>();
	std::shared_ptr<EqNode> y = std::make_shared<EqNode>();

	// Resize vectors
	AllResiduals.resize(eso->GetNumEqns());
	AllVariables.resize(eso->GetNumVars());
	AllJacobians.resize(eso->GetNumEqns());
	ParametersList.resize(eso->GetNumVars());
	for (int i = 0; i < eso->GetNumVars(); i++) {
		AllJacobians[i].resize(eso->GetNumVars());
	}

	AllVariables[0] = 1.0; AllVariables[1] = 1.0;
	eso->SetAllVariables(AllVariables);

	eso->GetParameterList(ParametersList);

	log("Initial Var values: ");
	printVec(eso->GetAllVariables());


	eso->GetAllResiduals(AllResiduals);
	log("Initial res values: ");
	printVec(AllResiduals);

	eso->GetAllJacobianValues(AllJacobians);
	log("Initial Jac values: ");
	printJac(AllJacobians);

	AllVariables[0] = 1.5; AllVariables[1] = 1.;
	eso->SetAllVariables(AllVariables);
	log("Solution Var values: ");
	printVec(eso->GetAllVariables());
	eso->GetAllResiduals(AllResiduals);
	log("Solution res values: ");
	printVec(AllResiduals);


	std::getchar();
}
