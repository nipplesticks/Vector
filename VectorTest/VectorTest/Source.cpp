#include "Vector.h"
#include "Timer.h"
#include <vector>
#include <iostream>

#include <string>
#include <DirectXMath.h>

int main()
{
	Vector<int> myVec;
	Vector<int> myVec2;
	Vector<int> myVec3;

	int counter = 0;

	for (int i = 0; i < 15; i++)
		myVec.PushBack(1);

	for (int i = 0; i < 15; i++)
		myVec2.PushBack(counter++);

	for (int i = 0; i < 15; i++)
		myVec3.PushBack(-1);

	myVec2.PushBack(myVec);

	myVec3.PushFront(myVec2);

	for (int i = 0; i < myVec3.Size(); i++)
	{
		if (i != 0 && i % 10 == 0)
			std::cout << std::endl;

		std::cout << myVec3[i] << "\t";
	}

	std::cout << std::endl;
	system("PAUSE");
	return 0;
}