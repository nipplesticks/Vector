#include "Vector.h"
#include "Timer.h"
#include <vector>
#include <iostream>

#include <string>
#include <DirectXMath.h>

void PrintVector(const Vector<int> & vec, int newLine = 5)
{
	for (unsigned int i = 0; i < vec.Size(); i++)
	{
		if (i != 0 && i % newLine == 0)
			std::cout << std::endl;

		std::cout << vec[i];

		if (i != vec.Size() - 1)
			std::cout << "\t";

	}

	std::cout << std::endl;

}



int main()
{
	Vector<int> vec1;
	Vector<int> vec2;
	Vector<int> vec3;

	int counter = 0;
	
	for (int i = 0; i < 15; i++)
		vec1.PushBack(1);

	std::cout << "Vec1:\n";
	PrintVector(vec1);

	for (int i = 0; i < 15; i++)
		vec2.PushBack(counter++);

	std::cout << "\nVec2:\n";
	PrintVector(vec2);

	for (int i = 0; i < 15; i++)
		vec3.PushBack(-1);

	std::cout << "\nVec3:\n";
	PrintVector(vec3);

	std::cout << "\nVec2.PushBack(vec1):\n";
	vec2.PushBack(vec1);

	PrintVector(vec2);

	std::cout << "\nVec3.PushFront(vec2):\n";
	vec3.PushFront(vec2);

	PrintVector(vec3);
	
	std::cout << std::endl;
	system("PAUSE");
	return 0;
}