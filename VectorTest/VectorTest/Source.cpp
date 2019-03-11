#include "Vector.h"
#include "Timer.h"
#include <vector>
#include <iostream>

#include <string>
#include <DirectXMath.h>

int main()
{
	const uint LOOP_COUNT = 10000;
	const uint PUSHES = 100;

	Vector<int> myVec;
	std::vector<int> stdVec;

	Timer t, t1;

	double time = 0.0;

	std::cout << "Time to push " << PUSHES << " objects\n";

	
	t.Start();
	for (int s = 0; s < LOOP_COUNT; s++)
	{
		for (uint i = 0; i < PUSHES; i++)
			myVec.Push(rand());
		time += t.Stop(Timer::MILLISECONDS);
	}
	std::cout << "My vector:\t" << time / LOOP_COUNT << " ms" << std::endl;

	time = 0.0;

	t1.Start();
	for (int s = 0; s < LOOP_COUNT; s++)
	{
		for (uint i = 0; i < PUSHES; i++)
			stdVec.push_back(rand());
		time += t1.Stop(Timer::MILLISECONDS);
	}
	std::cout << "std vector:\t" << time / LOOP_COUNT << " ms" << std::endl;
	
	system("PAUSE");
	return 0;
}