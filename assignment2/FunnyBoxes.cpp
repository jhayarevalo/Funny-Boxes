#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

const int rows = 5;
const int columns = 5;

//Necessary Functions
void initializeBoard(char board[][columns]);
void displayBoard(char board[][columns]);
bool isInputValid(int i, int j);
bool isBoxFree(char b);
bool isGameOver(char board[][columns]);

//Added Functions
void Hcoordinates(char board[][columns]);
void Pcoordinates(char board[][columns]);
bool checkULChorizontal(char board[][columns],int& x, int& y);
bool checkULCvertical(char board[][columns],int& x, int& y);
void savetofile(char board[][columns]);

int main()
{
    char playagain;
    char board[rows][columns];
do
{
    cout << "Welcome to Funny Boxes!\n\nIn this game, you will be Player H (human) against Player P (computer).\n\nIn the following game board, you will enter coordinates by the corresponding \nrows (0 to 4) and columns (0 to 4).\n\nPress ENTER after row input, then again after column input.\n\nTo win, you must create a complete diagonal across the board or close 8 \nadjacent boxes, i.e. create a 2x4 or a 4x2 box.\n\n\Enjoy!\n\n";
    
	//Game start
    initializeBoard(board);
    displayBoard(board);

	//Game inputs
	while (!isGameOver(board)) 
	{	
		//Human plays
		Hcoordinates(board);
		displayBoard(board);

			if (!isGameOver(board))
			{	
				//Computer plays
				Pcoordinates(board);
				displayBoard(board);
			}

			else
				break;
	}

	cout << "\nGame over.\n\n";
	savetofile(board);
	cout << "Enter 'Y' to play again.\n";
	cin >> playagain;
	cout << endl;

} while (playagain=='y'||playagain=='Y');

	system("pause");
	return 0;
}

void initializeBoard(char board[][columns])
{
	for (int i=0; i<rows; i++)
		//initialize row

		for (int j=0; j<columns; j++) // in each column
		{
			// put a dash in row i and column j
			board[i][j] = '-';	
		}
}

void displayBoard(char board[][columns])
{
    for (int j=0; j<columns; j++)
	{	//Label columns
        cout << "   " << j ;
	}

	for (int i=0; i<rows; i++)
	{	//Label rows
		cout << endl << i ;

		for (int j=0; j<columns; j++)
		{
            cout << " | " << board[i][j];
			
		}
		//Add line at end to close grid/board
		cout << " | ";
		cout <<endl;
	}
}

//Function to enter human coordinates
void Hcoordinates(char board[][columns])
{
	int i,j;

	cout << "\nPlayer H, please enter the coordinates of your desired position.\n\n";

	do
	{
		cin >> i >> j;
	} while (!isInputValid(i, j)||!isBoxFree(board[i][j]));
	
	board[i][j]='H';
}

//Function to enter computer coordinates
void Pcoordinates(char board[][columns])
{
	srand((unsigned int) time(0));
	int i=(rand()%5);
	int j=(rand()%5);

	while(board[i][j]!='-')
	{
		i=(rand()%5);
		j=(rand()%5);
	}

	board[i][j]= 'P';
	cout << "\nPlayer P has entered these coordinates: " << i << ", " << j << "\n\n";
}

//Check if coordinate input is valid
bool isInputValid(int i, int j)
{
	if ( (i>=0&&i<=4) && (j>=0&&j<=4) ) 
		return true;

	else
		{
			cout <<"\nThese coordinates are invalid. Please try again.\n\n";
			cin.sync(); //discard unread characters in input buffer
			cin.clear(); //clear bad input flag
			return false;
		}
}

//Check if box is free for coordinates entered
bool isBoxFree(char b)
{	
	if (b=='-')
	return true;

	else if (b!='-')
	{	
		cout << "\nThis box is already occupied. Please try again.\n\n";
		return false;
	}

	else
		return false;
}
//Cases to end the game
bool isGameOver(char board[][columns])
{
	int total1 = 0, total2 = 0, total3 = 0, total4 = 0, totalboard = 0;
	for (int i=0; i<rows; i++)
	
	{//Diagonals for human
		if (board[i][i]=='H')
		{
			total1++;
			
				if (total1==5)
				{
					cout << "\nYou win!\n";
					return true;
				}
		}
			
		if (board[i][4-i]=='H')
		{
			total2++;
				
				if (total2==5)
				{
					cout << "\nYou win!\n";
					return true;
				}
		}
		//Diagonals for PC
		if (board[i][i]=='P')
		{
			total3++;
			
				if (total3==5)
				{
					cout << "\nComputer wins!\n";
					return true;
				}
		}
			
		if (board[i][4-i]=='P')
		{
			total4++;
				
				if (total4==5)
				{
					cout << "\nComputer wins!\n";
					return true;
				}
		}
		//Board Full
		for(int j=0; j<columns; j++)
			if (board[i][j]!='-')
			{
				totalboard++;

				if (totalboard==25)
				{
					cout << "\nThe board is full.\n";
					return true;
					break;
				}
			}
	}
		
		//8 adj boxes part
	int x=0,y=0;
		if (checkULCvertical(board,x,y))
			return true;
		 
		if (checkULChorizontal(board,x,y))
			return true;

	return false;
}
//check starting from upper left corner box (x,y) for vertical boxes 2x4
bool checkULChorizontal(char board[][columns],int&x, int&y)
{
	int total5,total6;

	for (x=0;x<4;x++)
{//Reset total each time x and y changes
			total5=0;
			total6=0;

		for (y=0;y<2;y++)
		{
			total5=0;
			total6=0;
	{
//Check boxes around point x,y making x,y the wholebox's upper left corner	
	for (int i=0; i<2; i++)
		
		for (int j=0; j<4; j++)
		{
			if (board[x+i][y+j]=='H')
			{
				total5++;

				if (total5==8)
				{
					cout << "\nYou win!\n";
					return true;
				} 
			}
			if (board[x+i][y+j]=='P')
			{
				total6++;

				if (total6==8)
				{
					cout << "\nComputer wins!\n";
					return true;
				} 
			}
		}
	}	
		}
}
			return false;
}
//check starting from upper left corner box (x,y) for horizontal boxes 4x2
bool checkULCvertical(char board[][columns],int& x, int& y)
{
	int total7,total8;
	
	for (x=0;x<2;x++)
{//Reset total each time x and y changes
			total7=0;
			total8=0;

		for (y=0;y<4;y++)
		{
			total7=0;
			total8=0;
	{
//Check boxes around point x,y making x,y the wholebox's upper left corner
	for (int i=0; i<4; i++)
		
		for (int j=0; j<2; j++)
		{
			if (board[x+i][y+j]=='H')
			{
				total7++;

				if (total7==8)
				{
					cout << "\nYou win!\n";
					return true;
				} 
			}
			if (board[x+i][y+j]=='P')
			{
				total8++;

				if (total8==8)
				{
					cout << "\nComputer wins!\n";
					return true;
				} 
			}
		}
	}
		}
}
			return false;
}
void savetofile(char board[][columns])
{	//-- Declare an output stream.
	ofstream finalboard;

	//-- Create a new file.
	finalboard.open("finalboard.txt");
	//-- Check if the new file has been created successfully.
	if(finalboard.fail())
	{
		cout << "Output file opening failed."<< endl;
		//-- If not, exit the program.
		exit(1);
	}
	//-- change output to file instead of cout, similar to displayboard function
	finalboard << "Final game board:\n\n";	
	    
	for (int j=0; j<columns; j++)
	{	//Label columns
        finalboard << "   " << j ;
	}

	for (int i=0; i<rows; i++)
	{	//Label rows
		finalboard << endl << i ;

		for (int j=0; j<columns; j++)
		{
            finalboard << " | " << board[i][j];
			
		}
		//Add line at end to close grid/board
		finalboard << " | ";
		finalboard <<endl;
	}
	//-- close the file handle/stream.
	finalboard.close();
}