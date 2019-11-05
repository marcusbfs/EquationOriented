#pragma once

#include <memory>
#include <vector>
#include "EqNode.h"

class INumericESO {

	//virtual void Destroy() = 0;
	// Gets the value of all variables
	virtual std::vector<double> GetAllVariables() = 0;
	// Sets the value of all variables of this ESO
	virtual void SetAllVariables(const std::vector<double>& VarValues) = 0;
	virtual void GetParameterList(std::vector<std::shared_ptr<EqNode>>& TheListOfParameters) = 0;
	// Gets the number of equations of this ESO
	virtual unsigned long GetNumEqns() = 0;
	// Gets the number of variables of this ESO
	virtual unsigned long GetNumVars() = 0;
};


class INumericNLAESO : INumericESO {

	// Gets the value of all the residuals
	virtual void GetAllResiduals(std::vector<double>& AllResiduals) = 0;
	virtual void GetAllJacobianValues(std::vector<std::vector<double>>& AllJacobianValues) = 0;

};
