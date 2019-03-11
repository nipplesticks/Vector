#include "Vector.h"
#include "Timer.h"
#include <vector>
#include <iostream>

#include <string>
#include <DirectXMath.h>

int main()
{
	Vector<int> myVec;

	int counter = 0;

	for (int i = 0; i < 10; i++)
		myVec.PushBack(counter++);

	counter = 0;

	for (int i = 0; i < 10; i++)
		myVec.PushFront(counter--);

	for (int i = 0; i < myVec.Size(); i++)
		std::cout << myVec[i] << ", ";


	std::cout << std::endl;
	system("PAUSE");
	return 0;
}