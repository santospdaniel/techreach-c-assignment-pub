#pragma once

namespace cassign 
{
	/*
	Provides the opportunity for an object to initialize its resources. Example: initialize I/O resources.
	*/
	class Initializer
	{
	public:
		virtual void initialize() = 0;
	};
}