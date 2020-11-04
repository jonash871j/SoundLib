#include "simple_file_handler.h"
#include <iostream>

struct Type
{
	int val = 0;
	int test = 2;
};

int main()
{
	int length = 1000;
	//Type* types = new Type[length];


	//sfh::ReadFile inFile("test.dat");
	//Type* types = inFile.ReadArrayHeap<Type>(&length);
	//inFile.Close();

	//for (int i = 0; i < length; i++)
	//{
	//	std::cout << types[i].test << '\n';
	//}

	int test[8];

	sfh::ReadFile inFile("test.dat");
	inFile.ReadArray<int>(test, 8);
	inFile.Close();

	for (int i = 0; i < 8; i++)
	{
		std::cout << test[i] << '\n';
	}

	//std::cout << "Length of array = " << (sizeof(test) / sizeof(*test)) << std::endl;

	//sfh::WriteFile outFile("test.dat");
	//outFile.WriteArray<int>(test, 8);
	//outFile.Close();
}