#pragma once

//#include "PolygonPhysicsEngine.hpp"
//#include "InputReg.h"
//#include "ColorLineEngine.hpp"
#include "FunctionPtr.h"

class BaseScreen
{
public:
	
	int ret;
	//Main loop flag
	bool quit = false;


	template<typename T>
	FunctionPtr<T>* getFunctionPtr()
	{
		return new FunctionPtr<T>();
	}

	template<typename T, typename ...Args>
	T* gameInstance(Args... params)
	{
		return new T(params...);
	}
	
	BaseScreen()
	{}

	virtual bool init() = 0;
	virtual bool loadMedia() = 0;
	virtual void update(double dt) = 0;
	virtual void postUpdate() = 0;
	virtual void render() = 0;
	virtual void close() = 0;
	virtual int run() = 0;

	//PolygonPhysicsEngine physics;
	//CircleColouredEngine circleRenderer;
	//InputReg mouseInput;
	//Coupler coupler;

};