#pragma once

#include <vector>
#include "FunctionPtr.h"

class ActionPacked
{
public:
	ActionPacked();
	ActionPacked(int aNumOfStates, int aNumOfActions);
	~ActionPacked(void);

	void registerAction(int aStateOut, int anAction, int aStateIn, FunctionPtr<double>* response);
	FunctionPtr<double>& getResponse(int aState, int anAction);
	void callResponse(int anAction, double dt);

private:
	int numOfStates;
	int numOfActions;

	int actualState;

	std::vector<std::vector<FunctionPtr<double>*>> states;
	std::vector<std::vector<int>> links;

};
