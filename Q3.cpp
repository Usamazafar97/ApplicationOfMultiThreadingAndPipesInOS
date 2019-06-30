
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using namespace std;

int main()
{
	string input;
	
	while (true)
	{
		cout << "Please enter a line : ";
		getline(cin, input);
	
		if (strcmp(input.c_str(),"exit") == 0)
		{
			return 0;
		}
	}

}