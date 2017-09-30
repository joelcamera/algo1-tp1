#include "ActionPacked.h"
#include <iostream>

ActionPacked::ActionPacked()
{}

ActionPacked::ActionPacked(int aNumOfStates, int aNumOfActions)
{
	numOfStates = aNumOfStates;
	numOfActions = aNumOfActions;

	states = *new std::vector<std::vector<FunctionPtr<double>*>>(aNumOfStates);
	links = *new std::vector<std::vector<int>>(aNumOfStates);
	for(int i = 0; i < numOfStates; i++)
	{
		states[i] = *new std::vector<FunctionPtr<double>*>(numOfActions);
		links[i] = *new std::vector<int>(numOfActions);
		for (int j = 0; j < numOfActions; j++)
		{
			states[i][j] = nullptr;
			links[i][j] = -1;
		}
	}

	actualState = 0;
}


ActionPacked::~ActionPacked(void)
{
}


void ActionPacked::registerAction(int aStateOut, int anAction, int aStateIn, FunctionPtr<double>* response)
{
	states[aStateOut][anAction] = response;
	links[aStateOut][anAction] = aStateIn;
}


FunctionPtr<double>& ActionPacked::getResponse(int aState, int anAction)
{
	return *states[aState][anAction];
}

void ActionPacked::callResponse(int anAction, double dt)
{
	if (states[actualState][anAction] != nullptr)
	{
		states[actualState][anAction]->Invoke(dt);
	}
	if (-1 != links[actualState][anAction])
	{
		actualState = links[actualState][anAction];
		//std::cout << actualState << std::endl;
	}
}