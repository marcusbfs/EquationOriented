#pragma once

#include <memory>
#include "EqNode.h"
#include "Array.h"

class INumericESO {

	//virtual void Destroy() = 0;
	// Gets the value of all variables
	virtual Vector<double> GetAllVariables() = 0;
	// Sets the value of all variables of this ESO
	virtual void SetAllVariables(Vector<double>& VarValues) = 0;
	virtual void GetParameterList(Vector<std::shared_ptr<EqNode>>& TheListOfParameters) = 0;
	// Gets the number of equations of this ESO
	virtual unsigned long GetNumEqns() = 0;
	// Gets the number of variables of this ESO
	virtual unsigned long GetNumVars() = 0;
};


class INumericNLAESO : INumericESO {

	// Gets the value of all the residuals
	virtual void GetAllResiduals(Vector<double>& AllResiduals) = 0;
	virtual void GetAllJacobianValues(Matrix<double>& AllJacobianValues) = 0;
};
