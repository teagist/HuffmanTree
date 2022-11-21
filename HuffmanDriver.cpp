//****************************************************************************
//	Driver File for Huffman Tree Project
//	Programmed by: Houston Brown
//	Last Compiled Date: 11/21/2022
//
//
//	Copyright (c) 2022 Houston Brown
//
//	Permission is hereby granted to any person that obtains a copy of this
//	software and associated documentation files (the "Software"), to deal
//	within the Software for free and without restriction.  Including the
//	rights to use, copy, modify, merge, publish, redistribute, sublicense,
//	and/or sell copies of the Software.  Furthermore, to the people who the
//	Software is furnished to do so, subject to the following:
//
//	The above copyright notice and this permission notice shall be included
//	in all copies or substantial portions of the Software.
//
//	The Software is provided "as is", without any warranty of any kind,
//	express or implied, including but not limited to the warranties of 
//	merchantability, fitness for a particular purpose and noninfringement.
//	In not event shall the liability, whether in action of contract, tort or
//	otherwise, arising from, out of or in connection with the Software or the
//	use or other dealings in the Software.
//
//
//	DISCLAIMER: This program uses system calls that will only work on 
//				Windows operating system.
//****************************************************************************

#include "HuffmanTree.h"
#include <limits>
#include <sstream>



void printMenu();

void choose(HuffmanTree& HTree, BinaryHeap& BHeap);

int validateInput(int &value);

void encodeMessage(HuffmanTree& HTree, BinaryHeap& BHeap);

void fillHeap(string message, int occur[], BinaryHeap& BHeap);

void initArray(int array[], int size);

void displayCodes(HuffmanTree& HTree, BinaryHeap& BHeap);





int main()
{
	BinaryHeap myHeap;
	HuffmanTree myTree;
	
	printMenu();
	choose(myTree, myHeap);

	return 0;	
}





//****************************************************************************
//		Function to display the available options to the user.  
//
//	Parameters:
//		N/A.
//****************************************************************************

void printMenu()
{
	cout << "      ________________________" << endl;
	cout << "     | 1 | Encode String      |" << endl;
	cout << "     | 2 | Show Huffman Tree  |" << endl;
	cout << "     | 3 | Quit               |" << endl;	
	cout << "     |___|____________________|" << endl << endl;
    cout << "Please choose an operation to perform." << endl;
    cout << "Enter 3 to quit." << endl;	
}




//****************************************************************************
//		This function will prompt and accept the user's choice.  If the
//	choice is invalid, a message will be displayed.  Otherwise, the action
//	will be executed and the menu will continue to be displayed.  The user
//  will continue to be prompted until they enter the stopping condition.
//
//	Parameters:
//		HTree: Tree of nodes from the priority queue.
//		BHeap: Priority queue for characters and frequencies.
//****************************************************************************

void choose(HuffmanTree& HTree, BinaryHeap& BHeap)
{
	bool hasInserted = false;
	int  option      = 0;
	
	cout << "\n>> ";
	option = validateInput(option);
	
	while (option != 3)
	{
		switch(option)
		{
			case 1:
				encodeMessage(HTree, BHeap);
				hasInserted = true;
				break;

			case 2:
				if (hasInserted)
					HTree.PrintTree();
				else
					cerr << "Please enter a string first with option 1.\n";
				system("pause");

				break;

			case 3:
				exit(1);

			default:
				cerr << "Please enter a valid option from the menu." << endl;				
				system("pause");		
				break;
		}
		system("cls");
		printMenu();
			
		cout << "\n>> ";
		option = validateInput(option);
	}	
}




//***************************************************************************
//		This function will validate the input from the user.  If the user
//	enters an invalid option for the value, then a message will be displayed
//	and the user will be asked to try again.  Otherwise, the function will
//	return the value to the caller.
//
//	Parameters:
//		value: the value entered by the user.
//***************************************************************************
int validateInput(int &value)
{
	while ( !(cin >> value) )
	{
		cout << "\nPlease enter a valid option from the menu." << endl;
		system("pause");
		system("cls");
		
		printMenu();
		cout << "\n>> ";
						
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	return value;	
}




//****************************************************************************
//		First the user will be prompted to enter the message that will be 
//	encoded.  Next the characters used in the message and the number of 
//	times they occur will be tallied.  The priority queue will be filled,
//	the tree filled, then the Huffman codes displayed to the user. 
//
//	Parameters:
//		HTree: Tree of nodes from the priority queue.
//		BHeap: Priority queue for characters and frequencies.
//****************************************************************************

void encodeMessage(HuffmanTree& HTree, BinaryHeap& BHeap)
{
	string message = "";
	
	int occurrences[26];
	initArray(occurrences, 26);
	
	cout << "\nPlease enter a message to encode with at least 2 characters.";
	cout << endl;
	cin >> message;
				
	fillHeap(message, occurrences, BHeap);
	displayCodes(HTree, BHeap);
	system("pause");	
}




//****************************************************************************
//		This function will fill the priority queue with the characters
//	and frequenicies from the message.  
//
//	Parameters:
//		message: string of characters to encode.
//		occur: integer array of frequencies of characters from message.
//		BHeap: Priority queue for characters and frequencies.			
//****************************************************************************

void fillHeap(string message, int occur[], BinaryHeap& BHeap)
{
	char letter = 'z';
	int  freq   = -1;
	int  ctr    = 0;

	for (int i = 0; i < message.size(); i++)
	{
            occur[message[i] - 'a']++;
        }
	
	while (ctr < message.size())			 
	{
		if (occur[message[ctr] - 'a'] != 0)	
		{
			letter = message[ctr];
			freq = occur[message[ctr] - 'a'];
			
			BHeap.Insert(letter, freq);
			occur[message[ctr] - 'a'] = 0;
		}
		ctr = ctr + 1;
	}
}




//****************************************************************************
//		Function to initialize an integer array to all zeros.
//
//	Parameters:
//		array: integer array.
//		size: size of the array.
//****************************************************************************

void initArray(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		array[i] = 0;
	}
}




//****************************************************************************
//		First the Huffman Tree will be filled with the nodes from the 
//	priority queue.  Next, the array that will store that Huffman codes 
//	will be initialized before the codes are found and displayed to the 
//	user.
//
//	Parameters:
//		HTree: Tree of nodes from the priority queue.
//		BHeap: Priority queue for characters and frequencies.
//****************************************************************************

void displayCodes(HuffmanTree& HTree, BinaryHeap& BHeap)
{
	HTree.FillTree(BHeap);	
	
	int codes[100];
	initArray(codes, 100);
	
	cout << endl << endl;
	cout << "  Character  | Huffman Code" << endl;
	cout << "_____________|_______________" << endl;
	
	HTree.PrintCodes(codes, 0);
	cout << endl;
}
