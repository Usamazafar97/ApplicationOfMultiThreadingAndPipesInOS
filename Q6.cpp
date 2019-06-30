#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void * Countthread(void * temp)
{
		FILE * ptr1;
	ptr1 = fopen("example.txt", "r");
	if (ptr1 == NULL)
	{
		cout << "File not found!!!!";
		//return(1);
	}
	int count = 0;
	char ch;
	ch = fgetc(ptr1);
	while (!feof(ptr1))
	{
		//cout<<ch;
		ch = fgetc(ptr1);
		count++;
	}
	cout<<"count ="<<count<<endl;
	fclose(ptr1);
}

void * Displaythread(void * temp1)
{
	FILE * ptr2;
	ptr2 = fopen("example.txt", "r");
	if (ptr2 == NULL)
	{
		cout << "File not found!!!!";
		//return(1);
	}
	int count = 0;
	char ch;
	ch = fgetc(ptr2);
	while (!feof(ptr2))
	{
		cout<<ch;
		ch = fgetc(ptr2);
		count++;
	}
	//cout << "count =" << count << endl;
	fclose(ptr2);
}

int main() {

	string input;
	cout << "Please enter a line";
	getline(cin, input);
	
	if(strcmp(input.c_str,"EXIT") == 0 )
	{
		return 0;
	}

	ofstream myfile("example.txt");
	if (myfile.is_open())
	{
		myfile << input;
		myfile.close();
	}
	else cout << "Unable to open file";
	
	pthread_t thread;                                           //making new thread with thread label

    pthread_create(&thread, NULL, Countthread, NULL);              //creating thread with routine Countthread with no parameter 
    pthread_join(thread, NULL);	
	
	pthread_t thread1;                                         //making new thread with thread1 label

    pthread_create(&thread1, NULL, Displaythread, NULL);            //creating thread with routine Displaythread with no parameter 
    pthread_join(thread1, NULL);
	
	
	
	system("pause");
	return 0;
}