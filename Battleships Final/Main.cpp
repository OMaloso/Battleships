/***********************************************************************

File Name : Main.cpp
Description : Main game cpp file

**************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Ship.h"

using namespace std;

//Main Menu Enum
enum EMainMenu
{
	Menu,
	Play,
	Debug,
	Instructions,
	Exit,
};

//Board initialise
const int g_BoardSize = 10; //Board Size  // TF: Constant

char PlayerBoard[g_BoardSize][g_BoardSize];          //Player 10x10 board          // TF: Array
char EnemyBoard[g_BoardSize][g_BoardSize];           //Computer AI 10x10 board
char PlayerBoardDuplicate[g_BoardSize][g_BoardSize]; //Duplicate to show player attack board
char EnemyBoardDuplicate[g_BoardSize][g_BoardSize];  //Duplicate to show enemy attack board

//Heading function "BATTLESHIPS"
void Heading();

//Clear input function
void ClearInput();

//Random number function
int RandIndex(int _iSize);

//Convert char to int function
int ConvertChar(char _cCharacter);

//Convert int to char function
char ConvertInt(int _cInteger);

//Convert char to uppercase if lowercase function
char CharConverChar(char _cCharacter);

//Show game boards
void ShowGameBoard(); //Player Boards
void ShowGameBoardDebug(); //AI Boards (debug)



int main()
{
	//........ Initialise Variables ...........

	//Main menu choice
	int iMenuInput = Menu; // TF: Variable Type (int)

	//Gameplay input
	char cPlayerPlacementRandom; //Input for player decision in placing ships Automatically or not (not being Manually)

	//variables for placing player ships
	int iPlayerDirection; //Used for randomly selecting direction of player
	char cShipDirection = 'H'; //Input for player to decide if they want to manually place ship horizontally or vertically
	char cPlayerInputCharacter = 'A';  //Input for vertical grid A-J     // TF: Variable Type (char)
	int iPlayerInputHorizontal = 0;  //Input for horizontal grid 0-9     // TF: Variable Type (int)
	int iPlayerInputVertical = 0;  //Used for function for converting cPlayerInputCharacter into an integer for easier calculations
	bool bPlacementComplete = false;
	bool bCanPlaceSize = true; //Used for manual player ship placement. Used tp check if Player ship will fit in grid (ie placed in 9 grid horizontally)   // TF: Variable Type (bool)
	bool bCanPlace = true; //Used for working out if Player ship will overlap another. If false, will re-run loop

	//variables for placing AI ships randomly. 
	char cEnemyCharacter; //Used only for cout after putting iEnemyInputVertical through function (int to char)
	int iEnemyInputHorizontal; //Grid Horisontal choice 0-9
	int iEnemyInputVertical; //Grid Vertical choice A-J
	int iEnemyDirection; //variable for randomly choosing Horizontal or Vertical
	bool bEnemyCanPlace = true; //Used for working out if AI ship will overlap another. If false, will re-run loop

	//bools for checking player and AI turns have completed
	bool bPlayerTurnComplete = true;
	bool bEnemyTurnComplete = true;

	//Gameover bool
	bool bGameOver = false; //Will keep game running until either player or AI ships = 0, then switch to true

	//Debug initialise variables
	char cDebugModeInput = 'N'; //Player inputs for deciding if they want to turn debug mode on or off.
	bool bDebugMode = false; //bool holding value if debug is on or off

	//Ship creation
	CShip Acraft("Aircraft Carrier", 'A', 5, 5, 5), Bship("Battleship", 'B', 4, 4, 4), Dest("Destroyer", 'D', 3, 3, 3), Sub("Submarine", 'S', 3, 3, 3), Pboat("Patrol Boat", 'P', 2, 2, 2); // TF: Class Instance

	//Board symbol for empty part of board
	const char cBoardSymbol = '-';

	//Board symbols for hits or misses
	const char cShipHit = 'X';   //Hit symbol
	const char cShipMiss = '/';  //Miss symbol

	//Statistic variables
	int iNumberOfTurns = 0;
	int iNumberOfPlayerShips = 5;
	int iNumberOfEnemyShips = 5;

	//Seed random
	srand((unsigned int)(time(NULL)));

	//............ Start Game .............
	do
	{

		system("CLS");
		Heading(); //Show Heading 'Battleships'
		cout << endl << endl;

		//Reset gameboard arrays for new game
		for (int i = 0; i < 10; i++) // TF: Iteration Structure
		{
			for (int j = 0; j < 10; j++)
			{
				PlayerBoard[i][j] = cBoardSymbol;
				EnemyBoard[i][j] = PlayerBoard[i][j];
				PlayerBoardDuplicate[i][j] = PlayerBoard[i][j];
				EnemyBoardDuplicate[i][j] = EnemyBoard[i][j];
			}
		}

		//Reset Object Health
		Acraft.SetPlayerHealth(5);
		Acraft.SetEnemyHealth(5);
		Bship.SetPlayerHealth(4);
		Bship.SetEnemyHealth(4);
		Dest.SetPlayerHealth(3);
		Dest.SetEnemyHealth(3);
		Sub.SetPlayerHealth(3);
		Sub.SetEnemyHealth(3);
		Pboat.SetPlayerHealth(2);
		Pboat.SetEnemyHealth(2);

		//Rest Object Placement
		Acraft.SetPlacement(false);
		Bship.SetPlacement(false);
		Dest.SetPlacement(false);
		Sub.SetPlacement(false);
		Pboat.SetPlacement(false);

		//reset number of turns
		iNumberOfTurns = 0;
		iNumberOfPlayerShips = 5;
		iNumberOfEnemyShips = 5;

		bGameOver = false;

		if (cin.fail() || (iMenuInput != Play && iMenuInput != Debug && iMenuInput != Exit && iMenuInput != Menu)) // TF: Logical Operator // TF: Conditional Statement
		{
			ClearInput();
			cout << "                Please enter one of the below choices" << endl;
			cout << endl;
		}

		cout << "                1) Start" << endl;
		cout << "                2) Debug Mode" << endl;
		cout << "                3) Instructions" << endl;
		cout << "                4) Exit" << endl << endl;
		cout << "                ";
		cin >> iMenuInput;
		system("CLS");

		switch (iMenuInput)
		{
			// ............... Gameplay Loop ...............
		case Play:
		{
			// ..........    Placing ships at game start .............

			//ENEMY PLACEMENT - randomised placement to EnemyBoard
			//Random enemy Aircraft Carrier placement
			do
			{
				bEnemyCanPlace = true;
				iEnemyDirection = RandIndex(2);  //0 = horizontal  1=vertical
				if (iEnemyDirection == 0)
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize - Acraft.GetSize() + 1);
					iEnemyInputVertical = RandIndex(g_BoardSize);
					for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Acraft.GetSize(); i++)
					{
						if (EnemyBoard[iEnemyInputVertical][i] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Acraft.GetSize(); i++)
						{
							EnemyBoard[iEnemyInputVertical][i] = Acraft.GetLetterId();
						}
					}
				}
				else
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize);
					iEnemyInputVertical = RandIndex(g_BoardSize - Acraft.GetSize() + 1);
					for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Acraft.GetSize(); i++)
					{
						if (EnemyBoard[i][iEnemyInputHorizontal] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Acraft.GetSize(); i++)
						{
							EnemyBoard[i][iEnemyInputHorizontal] = Acraft.GetLetterId();
						}
					}
				}
			} while (bEnemyCanPlace == false);

			//Random enemy Battleship placement
			do
			{
				bEnemyCanPlace = true;
				iEnemyDirection = RandIndex(2);  //0 = horizontal  1=vertical
				if (iEnemyDirection == 0)
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize - Bship.GetSize() + 1);
					iEnemyInputVertical = RandIndex(g_BoardSize);
					for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Bship.GetSize(); i++)
					{
						if (EnemyBoard[iEnemyInputVertical][i] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Bship.GetSize(); i++)
						{
							EnemyBoard[iEnemyInputVertical][i] = Bship.GetLetterId();
						}
					}
				}
				else
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize);
					iEnemyInputVertical = RandIndex(g_BoardSize - Bship.GetSize() + 1);
					for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Bship.GetSize(); i++)
					{
						if (EnemyBoard[i][iEnemyInputHorizontal] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Bship.GetSize(); i++)
						{
							EnemyBoard[i][iEnemyInputHorizontal] = Bship.GetLetterId();
						}
					}
				}
			} while (bEnemyCanPlace == false);

			//Random enemy Destroyer placement
			do
			{
				bEnemyCanPlace = true;
				iEnemyDirection = RandIndex(2);  //0 = horizontal  1=vertical
				if (iEnemyDirection == 0)
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize - Dest.GetSize() + 1);
					iEnemyInputVertical = RandIndex(g_BoardSize);
					for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Dest.GetSize(); i++)
					{
						if (EnemyBoard[iEnemyInputVertical][i] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Dest.GetSize(); i++)
						{
							EnemyBoard[iEnemyInputVertical][i] = Dest.GetLetterId();
						}
					}
				}
				else
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize);
					iEnemyInputVertical = RandIndex(g_BoardSize - Dest.GetSize() + 1);
					for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Dest.GetSize(); i++)
					{
						if (EnemyBoard[i][iEnemyInputHorizontal] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Dest.GetSize(); i++)
						{
							EnemyBoard[i][iEnemyInputHorizontal] = Dest.GetLetterId();
						}
					}
				}
			} while (bEnemyCanPlace == false);

			//Random enemy Submarine placement
			do
			{
				bEnemyCanPlace = true;
				iEnemyDirection = RandIndex(2);  //0 = horizontal  1=vertical
				if (iEnemyDirection == 0)
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize - Sub.GetSize() + 1);
					iEnemyInputVertical = RandIndex(g_BoardSize);
					for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Sub.GetSize(); i++)
					{
						if (EnemyBoard[iEnemyInputVertical][i] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Sub.GetSize(); i++)
						{
							EnemyBoard[iEnemyInputVertical][i] = Sub.GetLetterId();
						}
					}
				}
				else
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize);
					iEnemyInputVertical = RandIndex(g_BoardSize - Sub.GetSize() + 1);
					for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Sub.GetSize(); i++)
					{
						if (EnemyBoard[i][iEnemyInputHorizontal] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Sub.GetSize(); i++)
						{
							EnemyBoard[i][iEnemyInputHorizontal] = Sub.GetLetterId();
						}
					}
				}
			} while (bEnemyCanPlace == false);

			//Random enemy Patrol boat placement
			do
			{
				bEnemyCanPlace = true;
				iEnemyDirection = RandIndex(2);  //0 = horizontal  1=vertical
				if (iEnemyDirection == 0)
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize - Pboat.GetSize() + 1);
					iEnemyInputVertical = RandIndex(g_BoardSize);
					for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Pboat.GetSize(); i++)
					{
						if (EnemyBoard[iEnemyInputVertical][i] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputHorizontal; i < iEnemyInputHorizontal + Pboat.GetSize(); i++)
						{
							EnemyBoard[iEnemyInputVertical][i] = Pboat.GetLetterId();
						}
					}
				}
				else
				{
					iEnemyInputHorizontal = RandIndex(g_BoardSize);
					iEnemyInputVertical = RandIndex(g_BoardSize - Pboat.GetSize() + 1);
					for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Pboat.GetSize(); i++)
					{
						if (EnemyBoard[i][iEnemyInputHorizontal] != cBoardSymbol)
						{
							bEnemyCanPlace = false;
							break;
						}
					}
					if (bEnemyCanPlace == true)
					{
						for (int i = iEnemyInputVertical; i < iEnemyInputVertical + Pboat.GetSize(); i++)
						{
							EnemyBoard[i][iEnemyInputHorizontal] = Pboat.GetLetterId();
						}
					}
				}
			} while (bEnemyCanPlace == false);

			//PLAYER PLACEMENT
			ShowGameBoard();
			if (bDebugMode == true)
			{
				ShowGameBoardDebug();
			}
			// Check if player wants ships placed randomly or if they want to do it themselves manually
			cout << "             Do you want your ships placed automatically?" << endl;
			cout << "             Type 'Y' for yes, or type anything else to place manually: ";
			cin >> cPlayerPlacementRandom;
			ClearInput();

			// Place player ships randomly
			if (cPlayerPlacementRandom == 'Y' || cPlayerPlacementRandom == 'y')
			{
				//Random player Aircraft Carrier placement
				do
				{
					bCanPlace = true;
					iPlayerDirection = RandIndex(2);  //0 = horizontal  1=vertical
					if (iPlayerDirection == 0)
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize - Acraft.GetSize() + 1);
						iPlayerInputVertical = RandIndex(g_BoardSize);
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Acraft.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Acraft.GetSize(); i++)
							{
								PlayerBoard[iPlayerInputVertical][i] = Acraft.GetLetterId();
							}
						}
					}
					else
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize);
						iPlayerInputVertical = RandIndex(g_BoardSize - Acraft.GetSize() + 1);
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Acraft.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Acraft.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Acraft.GetLetterId();
							}
						}
					}
				} while (bCanPlace == false);

				//Random player Battleship placement
				do
				{
					bCanPlace = true;
					iPlayerDirection = RandIndex(2);  //0 = horizontal  1=vertical
					if (iPlayerDirection == 0)
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize - Bship.GetSize() + 1);
						iPlayerInputVertical = RandIndex(g_BoardSize);
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Bship.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Bship.GetSize(); i++)
							{
								PlayerBoard[iPlayerInputVertical][i] = Bship.GetLetterId();
							}
						}
					}
					else
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize);
						iPlayerInputVertical = RandIndex(g_BoardSize - Bship.GetSize() + 1);
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Bship.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Bship.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Bship.GetLetterId();
							}
						}
					}
				} while (bCanPlace == false);

				//Random player Destroyer placement
				do
				{
					bCanPlace = true;
					iPlayerDirection = RandIndex(2);  //0 = horizontal  1=vertical
					if (iPlayerDirection == 0)
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize - Dest.GetSize() + 1);
						iPlayerInputVertical = RandIndex(g_BoardSize);
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Dest.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Dest.GetSize(); i++)
							{
								PlayerBoard[iPlayerInputVertical][i] = Dest.GetLetterId();
							}
						}
					}
					else
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize);
						iPlayerInputVertical = RandIndex(g_BoardSize - Dest.GetSize() + 1);
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Dest.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Dest.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Dest.GetLetterId();
							}
						}
					}
				} while (bCanPlace == false);

				//Random player Submarine placement
				do
				{
					bCanPlace = true;
					iPlayerDirection = RandIndex(2);  //0 = horizontal  1=vertical
					if (iPlayerDirection == 0)
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize - Sub.GetSize() + 1);
						iPlayerInputVertical = RandIndex(g_BoardSize);
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Sub.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Sub.GetSize(); i++)
							{
								PlayerBoard[iPlayerInputVertical][i] = Sub.GetLetterId();
							}
						}
					}
					else
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize);
						iPlayerInputVertical = RandIndex(g_BoardSize - Sub.GetSize() + 1);
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Sub.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Sub.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Sub.GetLetterId();
							}
						}
					}
				} while (bCanPlace == false);

				//Random player Patrol Boat placement
				do
				{
					bCanPlace = true;
					iPlayerDirection = RandIndex(2);  //0 = horizontal  1=vertical
					if (iPlayerDirection == 0)
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize - Pboat.GetSize() + 1);
						iPlayerInputVertical = RandIndex(g_BoardSize);
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Pboat.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Pboat.GetSize(); i++)
							{
								PlayerBoard[iPlayerInputVertical][i] = Pboat.GetLetterId();
							}
						}
					}
					else
					{
						iPlayerInputHorizontal = RandIndex(g_BoardSize);
						iPlayerInputVertical = RandIndex(g_BoardSize - Pboat.GetSize() + 1);
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Pboat.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Pboat.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Pboat.GetLetterId();
							}
						}
					}
				} while (bCanPlace == false);
			}
			// Placing player ships manually
			else
			{
				system("CLS");
				//Aircraft Carrier
				while (Acraft.GetPlacement() == false)
				{
					ShowGameBoard();
					if (bDebugMode == true)
					{
						ShowGameBoardDebug();
					}
					if (bCanPlaceSize == false) //Output if ship doesnt fit to grid, ie any horizontal ship in the 9 column
					{
						cout << "             Not enough space to fit the " << Acraft.GetName() << " there." << endl;
						cout << "             Please try a different location." << endl << endl;
						bCanPlaceSize = true;
					}
					if (bCanPlace == false) //Output if another ship in the selected grid
					{
						cout << "             Cannot place there. " << endl;
						cout << "             Please try a different location." << endl << endl;
						bCanPlace = true;
					}

					do // Direction Input
					{
						if (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v')
						{
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}

							cout << "             Please enter one of the below options." << endl << endl; //Output if player doesnt enter an H or V
						}
						cout << "             " << Acraft.GetName() << " placement: Size:" << Acraft.GetSize() << endl;
						cout << "             Do you want to place it Horizontally ('H') or Vertically ('V'): ";
						cin >> cShipDirection;
						ClearInput();
					} while (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v');

					do // Grid Input (letter followed by number)
					{
						if (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9)
						{
							system("CLS");
							ShowGameBoard();
							cout << "             Please enter a character between A-J, followed by a number between 0-9. " << endl; //Output if player doesnt input correct order of input, or outside grid bounds
						}
						cout << "             Please enter grid coordinate for placement (eg. 'A1'): ";
						cin >> cPlayerInputCharacter >> iPlayerInputHorizontal;
						ClearInput();
						iPlayerInputVertical = ConvertChar(cPlayerInputCharacter);
					} while (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9);


					if ((cShipDirection == 'H' || cShipDirection == 'h') && (iPlayerInputHorizontal > (g_BoardSize - Acraft.GetSize()))) // TF: Relational Operator 
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'H' || cShipDirection == 'h')
					{
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Acraft.GetSize(); i++) // TF: Arithmetic Operator
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Acraft.GetSize(); i++)
							{

								PlayerBoard[iPlayerInputVertical][i] = Acraft.GetLetterId();
							}
							Acraft.SetPlacement(true);
							system("CLS");
						}
					}
					else if ((cShipDirection == 'V' || cShipDirection == 'v') && (iPlayerInputVertical > (g_BoardSize - Acraft.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'V' || cShipDirection == 'v')
					{
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Acraft.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Acraft.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Acraft.GetLetterId();
							}
							Acraft.SetPlacement(true);
							system("CLS");
						}
					}
				}
				bCanPlaceSize = true;
				bCanPlace = true;

				//Battleship
				while (Bship.GetPlacement() == false)
				{
					ShowGameBoard();
					if (bDebugMode == true)
					{
						ShowGameBoardDebug();
					}

					if (bCanPlaceSize == false)
					{
						cout << "             Not enough space to fit the " << Bship.GetName() << " there." << endl;
						cout << "             Please try a different location" << endl << endl;
						bCanPlaceSize = true;
					}
					if (bCanPlace == false)
					{
						cout << "             Cannot place there. Another Ship is in the way" << endl;
						cout << "             Please try a different location" << endl << endl;
						bCanPlace = true;
					}

					do
					{
						if (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v')
						{
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}

							cout << "             Please enter one of the below options." << endl << endl;
						}
						cout << "             " << Bship.GetName() << " placement: Size:" << Bship.GetSize() << endl;
						cout << "             " << "Do you want to place it Horizontally ('H') or Vertically ('V'): ";
						cin >> cShipDirection;
						ClearInput();
					} while (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v');

					do // Grid Input (letter followed by number)
					{
						if (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9)
						{
							system("CLS");
							ShowGameBoard();
							cout << "             Please enter a character between A-J, followed by a number between 0-9. " << endl; //Output if player doesnt input correct order of input, or outside grid bounds
						}
						cout << "             Please enter grid coordinate for placement (eg. 'A1'): ";
						cin >> cPlayerInputCharacter >> iPlayerInputHorizontal;
						ClearInput();
						iPlayerInputVertical = ConvertChar(cPlayerInputCharacter);
					} while (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9);

					if ((cShipDirection == 'H' || cShipDirection == 'h') && (iPlayerInputHorizontal > (g_BoardSize - Bship.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'H' || cShipDirection == 'h')
					{
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Bship.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Bship.GetSize(); i++)
							{

								PlayerBoard[iPlayerInputVertical][i] = Bship.GetLetterId();
							}
							Bship.SetPlacement(true);
							system("CLS");
						}
					}
					else if ((cShipDirection == 'V' || cShipDirection == 'v') && (iPlayerInputVertical > (g_BoardSize - Bship.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'V' || cShipDirection == 'v')
					{
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Bship.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Bship.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Bship.GetLetterId();
							}
							Bship.SetPlacement(true);
							system("CLS");
						}
					}
				}
				bCanPlaceSize = true;
				bCanPlace = true;

				//Destroyer
				while (Dest.GetPlacement() == false)
				{
					ShowGameBoard();
					if (bDebugMode == true)
					{
						ShowGameBoardDebug();
					}

					if (bCanPlaceSize == false)
					{
						cout << "             Not enough space to fit the " << Dest.GetName() << " there." << endl;
						cout << "             Please try a different location" << endl << endl;
						bCanPlaceSize = true;
					}
					if (bCanPlace == false)
					{
						cout << "             Cannot place there. Another Ship is in the way" << endl;
						cout << "             Please try a different location" << endl << endl;
						bCanPlace = true;
					}

					do
					{
						if (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v')
						{
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}

							cout << "             Please enter one of the below options." << endl << endl;
						}
						cout << "             " << Dest.GetName() << " placement: Size:" << Dest.GetSize() << endl;
						cout << "             " << "Do you want to place it Horizontally ('H') or Vertically ('V'): ";
						cin >> cShipDirection;
						ClearInput();
					} while (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v');

					do // Grid Input (letter followed by number)
					{
						if (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9)
						{
							system("CLS");
							ShowGameBoard();
							cout << "             Please enter a character between A-J, followed by a number between 0-9. " << endl; //Output if player doesnt input correct order of input, or outside grid bounds
						}
						cout << "             Please enter grid coordinate for placement (eg. 'A1'): ";
						cin >> cPlayerInputCharacter >> iPlayerInputHorizontal;
						ClearInput();
						iPlayerInputVertical = ConvertChar(cPlayerInputCharacter);
					} while (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9);

					if ((cShipDirection == 'H' || cShipDirection == 'h') && (iPlayerInputHorizontal > (g_BoardSize - Dest.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'H' || cShipDirection == 'h')
					{
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Dest.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Dest.GetSize(); i++)
							{

								PlayerBoard[iPlayerInputVertical][i] = Dest.GetLetterId();
							}
							Dest.SetPlacement(true);
							system("CLS");
						}
					}
					else if ((cShipDirection == 'V' || cShipDirection == 'v') && (iPlayerInputVertical > (g_BoardSize - Dest.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'V' || cShipDirection == 'v')
					{
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Dest.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Dest.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Dest.GetLetterId();
							}
							Dest.SetPlacement(true);
							system("CLS");
						}
					}
				}
				bCanPlaceSize = true;
				bCanPlace = true;

				//Submarine
				while (Sub.GetPlacement() == false)
				{
					ShowGameBoard();
					if (bDebugMode == true)
					{
						ShowGameBoardDebug();
					}

					if (bCanPlaceSize == false)
					{
						cout << "             Not enough space to fit the " << Sub.GetName() << " there." << endl;
						cout << "             Please try a different location" << endl << endl;
						bCanPlaceSize = true;
					}
					if (bCanPlace == false)
					{
						cout << "             Cannot place there. Another Ship is in the way" << endl;
						cout << "             Please try a different location" << endl << endl;
						bCanPlace = true;
					}

					do
					{
						if (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v')
						{
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}

							cout << "             Please enter one of the below options." << endl << endl;
						}
						cout << "             " << Sub.GetName() << " placement: Size:" << Sub.GetSize() << endl;
						cout << "             " << "Do you want to place it Horizontally ('H') or Vertically ('V'): ";
						cin >> cShipDirection;
						ClearInput();
					} while (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v');

					do // Grid Input (letter followed by number)
					{
						if (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9)
						{
							system("CLS");
							ShowGameBoard();
							cout << "             Please enter a character between A-J, followed by a number between 0-9. " << endl; //Output if player doesnt input correct order of input, or outside grid bounds
						}
						cout << "             Please enter grid coordinate for placement (eg. 'A1'): ";
						cin >> cPlayerInputCharacter >> iPlayerInputHorizontal;
						ClearInput();
						iPlayerInputVertical = ConvertChar(cPlayerInputCharacter);
					} while (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9);

					if ((cShipDirection == 'H' || cShipDirection == 'h') && (iPlayerInputHorizontal > (g_BoardSize - Sub.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'H' || cShipDirection == 'h')
					{
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Sub.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Sub.GetSize(); i++)
							{

								PlayerBoard[iPlayerInputVertical][i] = Sub.GetLetterId();
							}
							Sub.SetPlacement(true);
							system("CLS");
						}
					}
					else if ((cShipDirection == 'V' || cShipDirection == 'v') && (iPlayerInputVertical > (g_BoardSize - Sub.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'V' || cShipDirection == 'v')
					{
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Sub.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Sub.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Sub.GetLetterId();
							}
							Sub.SetPlacement(true);
							system("CLS");
						}
					}
				}
				bCanPlaceSize = true;
				bCanPlace = true;

				//Patrol Boat
				while (Pboat.GetPlacement() == false)
				{
					ShowGameBoard();
					if (bDebugMode == true)
					{
						ShowGameBoardDebug();
					}

					if (bCanPlaceSize == false)
					{
						cout << "             Not enough space to fit the " << Pboat.GetName() << " there." << endl;
						cout << "             Please try a different location" << endl << endl;
						bCanPlaceSize = true;
					}
					if (bCanPlace == false)
					{
						cout << "             Cannot place there. Another Ship is in the way" << endl;
						cout << "             Please try a different location" << endl << endl;
						bCanPlace = true;
					}
					do
					{
						if (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v')
						{
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}

							cout << "             Please enter one of the below options." << endl << endl;
						}
						cout << "             " << Pboat.GetName() << " placement: Size:" << Pboat.GetSize() << endl;
						cout << "             " << "Do you want to place it Horizontally ('H') or Vertically ('V'): ";
						cin >> cShipDirection;
						ClearInput();
					} while (cShipDirection != 'H' && cShipDirection != 'h' && cShipDirection != 'V' && cShipDirection != 'v');

					do // Grid Input (letter followed by number)
					{
						if (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9)
						{
							system("CLS");
							ShowGameBoard();
							cout << "             Please enter a character between A-J, followed by a number between 0-9. " << endl; //Output if player doesnt input correct order of input, or outside grid bounds
						}
						cout << "             Please enter grid coordinate for placement (eg. 'A1'): ";
						cin >> cPlayerInputCharacter >> iPlayerInputHorizontal;
						ClearInput();
						iPlayerInputVertical = ConvertChar(cPlayerInputCharacter);
					} while (iPlayerInputHorizontal < 0 || iPlayerInputHorizontal > 9 || iPlayerInputVertical < 0 || iPlayerInputVertical > 9);

					if ((cShipDirection == 'H' || cShipDirection == 'h') && (iPlayerInputHorizontal > (g_BoardSize - Pboat.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'H' || cShipDirection == 'h')
					{
						for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Pboat.GetSize(); i++)
						{
							if (PlayerBoard[iPlayerInputVertical][i] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputHorizontal; i < iPlayerInputHorizontal + Pboat.GetSize(); i++)
							{

								PlayerBoard[iPlayerInputVertical][i] = Pboat.GetLetterId();
							}
							Pboat.SetPlacement(true);
							system("CLS");
						}
					}
					else if ((cShipDirection == 'V' || cShipDirection == 'v') && (iPlayerInputVertical > (g_BoardSize - Pboat.GetSize())))
					{
						bCanPlaceSize = false;
						system("CLS");
					}
					else if (cShipDirection == 'V' || cShipDirection == 'v')
					{
						for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Pboat.GetSize(); i++)
						{
							if (PlayerBoard[i][iPlayerInputHorizontal] != cBoardSymbol)
							{
								bCanPlace = false;
								system("CLS");
								break;
							}
						}
						if (bCanPlace == true)
						{
							for (int i = iPlayerInputVertical; i < iPlayerInputVertical + Pboat.GetSize(); i++)
							{
								PlayerBoard[i][iPlayerInputHorizontal] = Pboat.GetLetterId();
							}
							Pboat.SetPlacement(true);
							system("CLS");
						}
					}
				}
			}

			// ........... Gameplay ..........
			do
			{
				system("CLS");
				ShowGameBoard();
				if (bDebugMode == true)
				{
					ShowGameBoardDebug();
				}
				iPlayerInputVertical = 0;
				iPlayerInputHorizontal = 0;

				//... player turn ...
				do
				{
					do
					{
						
						if ((iPlayerInputVertical > 9 || iPlayerInputVertical < 0 || iPlayerInputHorizontal > 9 || iPlayerInputHorizontal < 0))
						{
							cout << "             Not an available grid option. Try again." << endl << endl;
						}
						else if (bPlayerTurnComplete == false)
						{
							cout << "             You already attacked that location. Try again." << endl << endl;
						}
						cout << "             Player Turn: "<< endl;
						cout << "             Enter the grid coordinate for attacking (eg. 'A1'): ";
						cin >> cPlayerInputCharacter;
						cin >> iPlayerInputHorizontal;
						iPlayerInputVertical = ConvertChar(cPlayerInputCharacter);
						cPlayerInputCharacter = CharConverChar(cPlayerInputCharacter);
						ClearInput();
					} while (iPlayerInputVertical > 9 || iPlayerInputVertical < 0 || iPlayerInputHorizontal > 9 || iPlayerInputHorizontal < 0);


					if (EnemyBoardDuplicate[iPlayerInputVertical][iPlayerInputHorizontal] == cShipHit || EnemyBoardDuplicate[iPlayerInputVertical][iPlayerInputHorizontal] == cShipMiss)
					{
						bPlayerTurnComplete = false;
					}
					//Check hits on Aircraft Carrier
					else if (EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] == Acraft.GetLetterId())
					{
						EnemyBoardDuplicate[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						Acraft.SetEnemyHealth(Acraft.GetEnemyHealth() - 1);
						system("CLS");
						ShowGameBoard();
						if (bDebugMode == true)
						{
							ShowGameBoardDebug();
						}
						cout << "             Your attack at " << cPlayerInputCharacter << iPlayerInputHorizontal << " hit an enemy ship." << endl;
						if (Acraft.GetEnemyHealth() <= 0)
						{
							cout << "             You destroyed the enemy " << Acraft.GetName() << "." << endl;
						}
						cout << endl;
						bPlayerTurnComplete = true;
					}
					//Check hits on Battleship
					else if (EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] == Bship.GetLetterId())
					{
						EnemyBoardDuplicate[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						Bship.SetEnemyHealth(Bship.GetEnemyHealth() - 1);
						system("CLS");
						ShowGameBoard();
						if (bDebugMode == true)
						{
							ShowGameBoardDebug();
						}
						cout << "             Your attack at " << cPlayerInputCharacter << iPlayerInputHorizontal << " hit an enemy ship." << endl;
						if (Bship.GetEnemyHealth() <= 0)
						{
							cout << "             You destroyed the enemy " << Bship.GetName() << "." << endl;
						}
						cout << endl;
						bPlayerTurnComplete = true;
					}
					//Check hits on Destroyer
					else if (EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] == Dest.GetLetterId())
					{
						EnemyBoardDuplicate[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						Dest.SetEnemyHealth(Dest.GetEnemyHealth() - 1);
						system("CLS");
						ShowGameBoard();
						if (bDebugMode == true)
						{
							ShowGameBoardDebug();
						}
						cout << "             Your attack at " << cPlayerInputCharacter << iPlayerInputHorizontal << " hit an enemy ship." << endl;
						if (Dest.GetEnemyHealth() <= 0)
						{
							cout << "             You destroyed the enemy " << Dest.GetName() << "." << endl;
						}
						cout << endl;
						bPlayerTurnComplete = true;
					}
					//Check hits on Submarine
					else if (EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] == Sub.GetLetterId())
					{
						EnemyBoardDuplicate[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						Sub.SetEnemyHealth(Sub.GetEnemyHealth() - 1);
						system("CLS");
						ShowGameBoard();
						if (bDebugMode == true)
						{
							ShowGameBoardDebug();
						}
						cout << "             Your attack at " << cPlayerInputCharacter << iPlayerInputHorizontal << " hit an enemy ship." << endl;
						if (Sub.GetEnemyHealth() <= 0)
						{
							cout << "             You destroyed the enemy " << Sub.GetName() << "." << endl;
						}
						cout << endl;
						bPlayerTurnComplete = true;
					}
					//Check hits on Patrol Boat
					else if (EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] == Pboat.GetLetterId())
					{
						EnemyBoardDuplicate[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] = cShipHit;
						Pboat.SetEnemyHealth(Pboat.GetEnemyHealth() - 1);
						system("CLS");
						ShowGameBoard();
						if (bDebugMode == true)
						{
							ShowGameBoardDebug();
						}
						cout << "             Your attack at " << cPlayerInputCharacter << iPlayerInputHorizontal << " hit an enemy ship." << endl;
						if (Pboat.GetEnemyHealth() <= 0)
						{
							cout << "             You destroyed the enemy " << Pboat.GetName() << "." << endl;
						}
						cout << endl;
						bPlayerTurnComplete = true;
					}
					else
					{
						EnemyBoardDuplicate[iPlayerInputVertical][iPlayerInputHorizontal] = cShipMiss;
						EnemyBoard[iPlayerInputVertical][iPlayerInputHorizontal] = cShipMiss;
						system("CLS");
						ShowGameBoard();
						if (bDebugMode == true)
						{
							ShowGameBoardDebug();
						}
						cout << "             Your attack at " << cPlayerInputCharacter << iPlayerInputHorizontal << " missed." << endl << endl;
						bPlayerTurnComplete = true;
					}
				} while (bPlayerTurnComplete == false);

				cout << "             Press enter to continue." << endl;
				cin.ignore();

				iNumberOfTurns ++; //count how many turns there have been for Statistics

				//Output if Player destroys all AI ships and wins
				if ((Acraft.GetEnemyHealth() + Bship.GetEnemyHealth() + Dest.GetEnemyHealth() + Sub.GetEnemyHealth() + Pboat.GetEnemyHealth()) <= 0)
				{
					cout << "             You have destroyed all of the enemy ships." << endl;
					cout << "             Congratulations, you win." << endl << endl;
					cout << "             Statistics: "<< endl;
					cout << "             Number of turns: " << iNumberOfTurns << endl;
					if (Acraft.GetPlayerHealth() <= 0)
					{
						iNumberOfPlayerShips--;
					}
					if (Bship.GetPlayerHealth() <= 0)
					{
						iNumberOfPlayerShips--;
					}
					if (Dest.GetPlayerHealth() <= 0)
					{
						iNumberOfPlayerShips--;
					}
					if (Sub.GetPlayerHealth() <= 0)
					{
						iNumberOfPlayerShips--;
					}
					if (Pboat.GetPlayerHealth() <= 0)
					{
						iNumberOfPlayerShips--;
					}
					cout << "             Your ships remaining: " << iNumberOfPlayerShips << endl << endl;
					bGameOver = true;
				}

				// ... AI turn ...
				if (bGameOver == false) //Check so that if player wins as above, then below code doesn't play
				{
					do
					{
						iEnemyInputHorizontal = RandIndex(g_BoardSize); //Pick random x value
						iEnemyInputVertical = RandIndex(g_BoardSize); //Pick random y value
						cEnemyCharacter = ConvertInt(iEnemyInputVertical); //Convert Vertical integer to character for cout

						if (PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] == cShipHit || PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] == cShipMiss)
						{
							bEnemyTurnComplete = false;
						}
						else if (PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] == Acraft.GetLetterId())
						{
							PlayerBoardDuplicate[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							Acraft.SetPlayerHealth(Acraft.GetPlayerHealth() - 1);
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}
							cout << "             Enemy Turn: " << endl;
							cout << "             The enemy attacked " << cEnemyCharacter << iEnemyInputHorizontal << " and hit your " << Acraft.GetName() << "." << endl << endl;
							if (Acraft.GetPlayerHealth() <= 0)
							{
								cout << "             The enemy destroyed your " << Acraft.GetName() << "." << endl << endl;
							}
							bEnemyTurnComplete = true;
						}
						else if (PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] == Bship.GetLetterId())
						{
							PlayerBoardDuplicate[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							Bship.SetPlayerHealth(Bship.GetPlayerHealth() - 1);
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}
							cout << "             Enemy Turn: " << endl;
							cout << "             The enemy attacked " << cEnemyCharacter << iEnemyInputHorizontal << " and hit your " << Bship.GetName() << "." << endl << endl;
							if (Bship.GetPlayerHealth() <= 0)
							{
								cout << "             The enemy destroyed your " << Bship.GetName() << "." << endl << endl;
							}
							bEnemyTurnComplete = true;
						}
						else if (PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] == Dest.GetLetterId())
						{
							PlayerBoardDuplicate[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							Dest.SetPlayerHealth(Dest.GetPlayerHealth() - 1);
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}
							cout << "             Enemy Turn: " << endl;
							cout << "             The enemy attacked " << cEnemyCharacter << iEnemyInputHorizontal << " and hit your " << Dest.GetName() << "." << endl << endl;
							if (Dest.GetPlayerHealth() <= 0)
							{
								cout << "             The enemy destroyed your " << Dest.GetName() << "." << endl << endl;
							}
							bEnemyTurnComplete = true;
						}
						else if (PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] == Sub.GetLetterId())
						{
							PlayerBoardDuplicate[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							Sub.SetPlayerHealth(Sub.GetPlayerHealth() - 1);
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}
							cout << "             Enemy Turn: " << endl;
							cout << "             The enemy attacked " << cEnemyCharacter << iEnemyInputHorizontal << " and hit your " << Sub.GetName() << "." << endl << endl;
							if (Sub.GetPlayerHealth() <= 0)
							{
								cout << "             The enemy destroyed your " << Sub.GetName() << "." << endl << endl;
							}
							bEnemyTurnComplete = true;
						}
						else if (PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] == Pboat.GetLetterId())
						{
							PlayerBoardDuplicate[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] = cShipHit;
							Pboat.SetPlayerHealth(Pboat.GetPlayerHealth() - 1);
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}
							cout << "             Enemy Turn: " << endl;
							cout << "             The enemy attacked " << cEnemyCharacter << iEnemyInputHorizontal << " and hit your " << Pboat.GetName() << "." << endl << endl;
							if (Pboat.GetPlayerHealth() <= 0)
							{
								cout << "             The enemy destroyed your " << Pboat.GetName() << "." << endl << endl;
							}
							bEnemyTurnComplete = true;
						}
						else
						{
							PlayerBoardDuplicate[iEnemyInputVertical][iEnemyInputHorizontal] = cShipMiss;
							PlayerBoard[iEnemyInputVertical][iEnemyInputHorizontal] = cShipMiss;
							system("CLS");
							ShowGameBoard();
							if (bDebugMode == true)
							{
								ShowGameBoardDebug();
							}
							cout << "             Enemy Turn: " << endl;
							cout << "             The enemy attacked " << cEnemyCharacter << iEnemyInputHorizontal << " and missed." << endl << endl;
							bEnemyTurnComplete = true;
						}
					} while (bEnemyTurnComplete == false);
				}

				//Output if AI destroys all Player ships and wins
				if ((Acraft.GetPlayerHealth() + Bship.GetPlayerHealth() + Dest.GetPlayerHealth() + Sub.GetPlayerHealth() + Pboat.GetPlayerHealth()) <= 0)
				{
					cout << "             The enemy has destroyed all of your ships" << endl;
					cout << "             Unfortunately, you have lost." << endl << endl;
					cout << "             Statistics: " << endl;
					cout << "             Number of turns: " << iNumberOfTurns << endl;
					if (Acraft.GetEnemyHealth() <= 0)
					{
						iNumberOfEnemyShips--;
					}
					if (Bship.GetEnemyHealth() <= 0)
					{
						iNumberOfEnemyShips--;
					}
					if (Dest.GetEnemyHealth() <= 0)
					{
						iNumberOfEnemyShips--;
					}
					if (Sub.GetEnemyHealth() <= 0)
					{
						iNumberOfEnemyShips--;
					}
					if (Pboat.GetEnemyHealth() <= 0)
					{
						iNumberOfEnemyShips--;
					}
					cout << "             Enemy ships remaining: " << iNumberOfEnemyShips << endl << endl;
					bGameOver = true;
				}

				cout << "             Press enter to continue." << endl;
				cin.ignore();



			} while (bGameOver == false);

			break;
		}
		// ......... Debug Mode ........
		// This will ask player if they want to turn on/off debug mode, before returning to Main Menu
		case Debug:
		{
			Heading(); //Show Heading 'Battleships'
			cout << endl;
			if (bDebugMode == false)
			{
				cout << "        Debug mode is turned off." << endl << endl;
				cout << "        Do you want to turn on Debug Mode?" << endl;
			}
			else
			{
				cout << "        Debug mode is turned on." << endl << endl;
				cout << "        Do you want to turn off Debug Mode?" << endl;
			}
			cout << "        This mode shows grids from the AI perspective." << endl << endl;
			cout << "        Press Y for yes, or any other key to return to Main Menu: ";
			cin >> cDebugModeInput;
			ClearInput();
			if ((cDebugModeInput == 'Y' || cDebugModeInput == 'y') && (bDebugMode == false))
			{
				cout << endl;
				cout << "        Debug mode is now turned on. " << endl;
				cout << "        Press enter to return to Main Menu. ";
				bDebugMode = true;
				cin.ignore();
				system("CLS");
				iMenuInput = Menu;
			}
			else if ((cDebugModeInput == 'Y' || cDebugModeInput == 'y') && (bDebugMode == true))
			{
				cout << endl;
				cout << "        Debug mode is now turned off. " << endl;
				cout << "        Press enter to return to Main Menu. ";
				bDebugMode = false;
				cin.ignore();
				system("CLS");
				iMenuInput = Menu;
			}
			else
			{
				iMenuInput = Menu;
				system("CLS");
			}
			break;
		}
		case Instructions:
		{
			Heading(); //Show Heading 'Battleships'
			cout << endl << endl;
			cout << "         --------------------------------------------------------------------------" << endl;
			cout << "                                        INTRODUCTION" << endl;
			cout << "         --------------------------------------------------------------------------" << endl;
			cout << "         Battleships is a strategy guessing game where you and the computer take" << endl;
			cout << "         turns attempting to destroy each others ships." << endl << endl;
			cout << "         --------------------------------------------------------------------------" << endl;
			cout << "                                          CONTROLS" << endl;
			cout << "         --------------------------------------------------------------------------" << endl;
			cout << "         The game begins with you placing your ships within the boundaries of the" << endl;
			cout << "         10x10 game board." << endl;
			cout << "         Each ship has a designated size, can be placed either horizontally" << endl;
			cout << "         or vertically, and cannot overlap one another." << endl;
			cout << "         When placing the ships, you specify a grid location beginning with a letter," << endl;
			cout << "         followed by a number (for example, 'A1')." << endl;
			cout << "         The specified grid location refers to the left-most position of the ship" << endl;
			cout << "         if placing horizontally, or the top-most position if placing vertically," << endl;
			cout << "         with the remaining grids being filled in their respective directions" << endl;
			cout << "         (assuming there is enough space on the board)." << endl;
			cout << "         If necessary, ships can be placed automatically for your ease." << endl << endl;
			cout << "         Below is a list of your ship types along with their sizes." << endl << endl;
			cout << "                             Name                  Size" << endl;
			cout << "                             Aircraft Carrier        5" << endl;
			cout << "                             Battleship              4" << endl;
			cout << "                             Destroyer               3" << endl;
			cout << "                             Submarine               3" << endl;
			cout << "                             Patrol Boat             2" << endl << endl;
			cout << "         Once placed on the game board, they are shown with a letter designation" << endl;
			cout << "         based on the first letter of the ship name, for example, your Battleship" << endl;
			cout << "         will be shown on the game board with a 'B'." << endl << endl;;
			cout << "         Once all ships have been placed, you and the computer will take turns guessing" << endl;
			cout << "         grid locations in an attempt to destroy each others ships. Again, when choosing" << endl;
			cout << "         a location to attack, specify a grid location beginning with a letter," << endl;
			cout << "         followed by a number." << endl << endl;
			cout << "         Hits on ships will be shown on the board with an 'X', misses will be "<< endl;
			cout << "         shown with a '/'." << endl << endl;
			cout << "         If you manage to hit all positions of the enemy ship, you will be notified" << endl;
			cout << "         which ship you have destroyed." << endl << endl;
			cout << "         To win, you must destroy all of the computers ships before it destroys yours." << endl << endl;
			cout << "         --------------------------------------------------------------------------" << endl;
			cout << "                                           DEBUG" << endl;
			cout << "         --------------------------------------------------------------------------" << endl;
			cout << "         Debug mode can be accessed from the main menu. When selected, press 'Y' to" << endl;
			cout << "         turn debug mode on (or off), at which point you will be promted to return " << endl;
			cout << "         to the main menu to start your game." << endl << endl;
			cout << "         Debug mode will show the AI game boards, including where the AI ships have" << endl;
			cout << "         been automatically placed." << endl << endl;
			cout << "         --------------------------------------------------------------------------" << endl;
			cout << "                                         REFERENCES" << endl;
			cout << "         --------------------------------------------------------------------------" << endl;
			cout << "         'Battleships' header text created using the text generator at Patorjk.com" << endl;
			cout << "         https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20" << endl << endl;
			cout << "         Press enter to return to Main Menu. ";
			cin.ignore();
			cin.ignore();
			system("CLS");
			iMenuInput = Menu;

			break;
		}

		default:
		{

		}
		}

	} while (iMenuInput != Exit);

	// ..........  Game Exit ..............
	if (iMenuInput == Exit)
	{
		system("CLS");
		Heading(); //Show Heading 'Battleships'
		cout << endl << endl;
		cout << "                Thank you for playing" << endl;
		cout << endl;
		cout << "                Press Enter to Exit";
		cin.ignore();
		cin.ignore(); //these ignores required otherwise game will exit without showing above text
	}
}

//............. Functions ..................

//Show heading
void Heading()
{
	cout << R"(
	 ____       _______ _______ _      ______  _____ _    _ _____ _____   _____ 
	|  _ \   /\|__   __|__   __| |    |  ____|/ ____| |  | |_   _|  __ \ / ____|
	| |_) | /  \  | |     | |  | |    | |__  | (___ | |__| | | | | |__) | (___  
	|  _ < / /\ \ | |     | |  | |    |  __|  \___ \|  __  | | | |  ___/ \___ \ 
	| |_) / ____ \| |     | |  | |____| |____ ____) | |  | |_| |_| |     ____) | 
	|____/_/    \_\_|     |_|  |______|______|_____/|_|  |_|_____|_|    |_____/  )" << endl;
}

void ClearInput()
{
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

//random number function
int RandIndex(int _iSize)
{
	int a = rand() % _iSize;
	return a;
}

//convert a character value to an integer
int ConvertChar(char _cCharacter)
{
	int num;
	if (_cCharacter <= 74 && _cCharacter >= 65)
	{
		num = _cCharacter - 65;
	}
	else if (_cCharacter >= 97 && _cCharacter <= 106)
	{
		num = _cCharacter - 97;
	}
	else
	{
		num = -1;
	}
	return num;
}

//convert an integer to a character
char ConvertInt(int _cInteger)
{
	char letter;

	letter = _cInteger + 65;

	return letter;
}

//Convert player character value to a capital
char CharConverChar(char _cCharacter)
{
	char letter;
	if (_cCharacter > 96)
	{
		letter = _cCharacter - 32;
	}
	else
	{
		letter = _cCharacter;
	}
	return letter;
}

//Show heading and gameboard for player
void ShowGameBoard()
{
	Heading(); //Show Heading 'Battleships'
	cout << endl << endl;
	cout << "                          Player                         Player" << endl;
	cout << "                        Ship Board                    Attack Board" << endl << endl;
	cout << "                    0 1 2 3 4 5 6 7 8 9            0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "                 A| " << PlayerBoard[0][0] << " " << PlayerBoard[0][1] << " " << PlayerBoard[0][2] << " " << PlayerBoard[0][3] << " " << PlayerBoard[0][4] << " " << PlayerBoard[0][5] << " " << PlayerBoard[0][6] << " " << PlayerBoard[0][7] << " " << PlayerBoard[0][8] << " " << PlayerBoard[0][9] << "         A| " << EnemyBoardDuplicate[0][0] << " " << EnemyBoardDuplicate[0][1] << " " << EnemyBoardDuplicate[0][2] << " " << EnemyBoardDuplicate[0][3] << " " << EnemyBoardDuplicate[0][4] << " " << EnemyBoardDuplicate[0][5] << " " << EnemyBoardDuplicate[0][6] << " " << EnemyBoardDuplicate[0][7] << " " << EnemyBoardDuplicate[0][8] << " " << EnemyBoardDuplicate[0][9] << endl;
	cout << "                 B| " << PlayerBoard[1][0] << " " << PlayerBoard[1][1] << " " << PlayerBoard[1][2] << " " << PlayerBoard[1][3] << " " << PlayerBoard[1][4] << " " << PlayerBoard[1][5] << " " << PlayerBoard[1][6] << " " << PlayerBoard[1][7] << " " << PlayerBoard[1][8] << " " << PlayerBoard[1][9] << "         B| " << EnemyBoardDuplicate[1][0] << " " << EnemyBoardDuplicate[1][1] << " " << EnemyBoardDuplicate[1][2] << " " << EnemyBoardDuplicate[1][3] << " " << EnemyBoardDuplicate[1][4] << " " << EnemyBoardDuplicate[1][5] << " " << EnemyBoardDuplicate[1][6] << " " << EnemyBoardDuplicate[1][7] << " " << EnemyBoardDuplicate[1][8] << " " << EnemyBoardDuplicate[1][9] << "      A -  Aircraft Carrier" << endl;
	cout << "                 C| " << PlayerBoard[2][0] << " " << PlayerBoard[2][1] << " " << PlayerBoard[2][2] << " " << PlayerBoard[2][3] << " " << PlayerBoard[2][4] << " " << PlayerBoard[2][5] << " " << PlayerBoard[2][6] << " " << PlayerBoard[2][7] << " " << PlayerBoard[2][8] << " " << PlayerBoard[2][9] << "         C| " << EnemyBoardDuplicate[2][0] << " " << EnemyBoardDuplicate[2][1] << " " << EnemyBoardDuplicate[2][2] << " " << EnemyBoardDuplicate[2][3] << " " << EnemyBoardDuplicate[2][4] << " " << EnemyBoardDuplicate[2][5] << " " << EnemyBoardDuplicate[2][6] << " " << EnemyBoardDuplicate[2][7] << " " << EnemyBoardDuplicate[2][8] << " " << EnemyBoardDuplicate[2][9] << "      B -  Battleship" << endl;
	cout << "                 D| " << PlayerBoard[3][0] << " " << PlayerBoard[3][1] << " " << PlayerBoard[3][2] << " " << PlayerBoard[3][3] << " " << PlayerBoard[3][4] << " " << PlayerBoard[3][5] << " " << PlayerBoard[3][6] << " " << PlayerBoard[3][7] << " " << PlayerBoard[3][8] << " " << PlayerBoard[3][9] << "         D| " << EnemyBoardDuplicate[3][0] << " " << EnemyBoardDuplicate[3][1] << " " << EnemyBoardDuplicate[3][2] << " " << EnemyBoardDuplicate[3][3] << " " << EnemyBoardDuplicate[3][4] << " " << EnemyBoardDuplicate[3][5] << " " << EnemyBoardDuplicate[3][6] << " " << EnemyBoardDuplicate[3][7] << " " << EnemyBoardDuplicate[3][8] << " " << EnemyBoardDuplicate[3][9] << "      D -  Destroyer" << endl;
	cout << "                 E| " << PlayerBoard[4][0] << " " << PlayerBoard[4][1] << " " << PlayerBoard[4][2] << " " << PlayerBoard[4][3] << " " << PlayerBoard[4][4] << " " << PlayerBoard[4][5] << " " << PlayerBoard[4][6] << " " << PlayerBoard[4][7] << " " << PlayerBoard[4][8] << " " << PlayerBoard[4][9] << "         E| " << EnemyBoardDuplicate[4][0] << " " << EnemyBoardDuplicate[4][1] << " " << EnemyBoardDuplicate[4][2] << " " << EnemyBoardDuplicate[4][3] << " " << EnemyBoardDuplicate[4][4] << " " << EnemyBoardDuplicate[4][5] << " " << EnemyBoardDuplicate[4][6] << " " << EnemyBoardDuplicate[4][7] << " " << EnemyBoardDuplicate[4][8] << " " << EnemyBoardDuplicate[4][9] << "      S -  Submarine" << endl;
	cout << "                 F| " << PlayerBoard[5][0] << " " << PlayerBoard[5][1] << " " << PlayerBoard[5][2] << " " << PlayerBoard[5][3] << " " << PlayerBoard[5][4] << " " << PlayerBoard[5][5] << " " << PlayerBoard[5][6] << " " << PlayerBoard[5][7] << " " << PlayerBoard[5][8] << " " << PlayerBoard[5][9] << "         F| " << EnemyBoardDuplicate[5][0] << " " << EnemyBoardDuplicate[5][1] << " " << EnemyBoardDuplicate[5][2] << " " << EnemyBoardDuplicate[5][3] << " " << EnemyBoardDuplicate[5][4] << " " << EnemyBoardDuplicate[5][5] << " " << EnemyBoardDuplicate[5][6] << " " << EnemyBoardDuplicate[5][7] << " " << EnemyBoardDuplicate[5][8] << " " << EnemyBoardDuplicate[5][9] << "      P -  Patrol Boat" << endl;
	cout << "                 G| " << PlayerBoard[6][0] << " " << PlayerBoard[6][1] << " " << PlayerBoard[6][2] << " " << PlayerBoard[6][3] << " " << PlayerBoard[6][4] << " " << PlayerBoard[6][5] << " " << PlayerBoard[6][6] << " " << PlayerBoard[6][7] << " " << PlayerBoard[6][8] << " " << PlayerBoard[6][9] << "         G| " << EnemyBoardDuplicate[6][0] << " " << EnemyBoardDuplicate[6][1] << " " << EnemyBoardDuplicate[6][2] << " " << EnemyBoardDuplicate[6][3] << " " << EnemyBoardDuplicate[6][4] << " " << EnemyBoardDuplicate[6][5] << " " << EnemyBoardDuplicate[6][6] << " " << EnemyBoardDuplicate[6][7] << " " << EnemyBoardDuplicate[6][8] << " " << EnemyBoardDuplicate[6][9] << endl;
	cout << "                 H| " << PlayerBoard[7][0] << " " << PlayerBoard[7][1] << " " << PlayerBoard[7][2] << " " << PlayerBoard[7][3] << " " << PlayerBoard[7][4] << " " << PlayerBoard[7][5] << " " << PlayerBoard[7][6] << " " << PlayerBoard[7][7] << " " << PlayerBoard[7][8] << " " << PlayerBoard[7][9] << "         H| " << EnemyBoardDuplicate[7][0] << " " << EnemyBoardDuplicate[7][1] << " " << EnemyBoardDuplicate[7][2] << " " << EnemyBoardDuplicate[7][3] << " " << EnemyBoardDuplicate[7][4] << " " << EnemyBoardDuplicate[7][5] << " " << EnemyBoardDuplicate[7][6] << " " << EnemyBoardDuplicate[7][7] << " " << EnemyBoardDuplicate[7][8] << " " << EnemyBoardDuplicate[7][9] << "      X -  Hit" << endl;
	cout << "                 I| " << PlayerBoard[8][0] << " " << PlayerBoard[8][1] << " " << PlayerBoard[8][2] << " " << PlayerBoard[8][3] << " " << PlayerBoard[8][4] << " " << PlayerBoard[8][5] << " " << PlayerBoard[8][6] << " " << PlayerBoard[8][7] << " " << PlayerBoard[8][8] << " " << PlayerBoard[8][9] << "         I| " << EnemyBoardDuplicate[8][0] << " " << EnemyBoardDuplicate[8][1] << " " << EnemyBoardDuplicate[8][2] << " " << EnemyBoardDuplicate[8][3] << " " << EnemyBoardDuplicate[8][4] << " " << EnemyBoardDuplicate[8][5] << " " << EnemyBoardDuplicate[8][6] << " " << EnemyBoardDuplicate[8][7] << " " << EnemyBoardDuplicate[8][8] << " " << EnemyBoardDuplicate[8][9] << "      / -  Miss" << endl;
	cout << "                 J| " << PlayerBoard[9][0] << " " << PlayerBoard[9][1] << " " << PlayerBoard[9][2] << " " << PlayerBoard[9][3] << " " << PlayerBoard[9][4] << " " << PlayerBoard[9][5] << " " << PlayerBoard[9][6] << " " << PlayerBoard[9][7] << " " << PlayerBoard[9][8] << " " << PlayerBoard[9][9] << "         J| " << EnemyBoardDuplicate[9][0] << " " << EnemyBoardDuplicate[9][1] << " " << EnemyBoardDuplicate[9][2] << " " << EnemyBoardDuplicate[9][3] << " " << EnemyBoardDuplicate[9][4] << " " << EnemyBoardDuplicate[9][5] << " " << EnemyBoardDuplicate[9][6] << " " << EnemyBoardDuplicate[9][7] << " " << EnemyBoardDuplicate[9][8] << " " << EnemyBoardDuplicate[9][9] << endl;
	cout << endl;
}

//Show AI gameboard in debug mode
void ShowGameBoardDebug()
{
	cout << endl << endl;
	cout << "                                       Debug mode" << endl << endl;
	cout << "                         Enemy AI                       Enemy AI " << endl;
	cout << "                        Ship Board                    Attack Board" << endl << endl;
	cout << "                    0 1 2 3 4 5 6 7 8 9            0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "                 A| " << EnemyBoard[0][0] << " " << EnemyBoard[0][1] << " " << EnemyBoard[0][2] << " " << EnemyBoard[0][3] << " " << EnemyBoard[0][4] << " " << EnemyBoard[0][5] << " " << EnemyBoard[0][6] << " " << EnemyBoard[0][7] << " " << EnemyBoard[0][8] << " " << EnemyBoard[0][9] << "         A| " << PlayerBoardDuplicate[0][0] << " " << PlayerBoardDuplicate[0][1] << " " << PlayerBoardDuplicate[0][2] << " " << PlayerBoardDuplicate[0][3] << " " << PlayerBoardDuplicate[0][4] << " " << PlayerBoardDuplicate[0][5] << " " << PlayerBoardDuplicate[0][6] << " " << PlayerBoardDuplicate[0][7] << " " << PlayerBoardDuplicate[0][8] << " " << PlayerBoardDuplicate[0][9] << endl;
	cout << "                 B| " << EnemyBoard[1][0] << " " << EnemyBoard[1][1] << " " << EnemyBoard[1][2] << " " << EnemyBoard[1][3] << " " << EnemyBoard[1][4] << " " << EnemyBoard[1][5] << " " << EnemyBoard[1][6] << " " << EnemyBoard[1][7] << " " << EnemyBoard[1][8] << " " << EnemyBoard[1][9] << "         B| " << PlayerBoardDuplicate[1][0] << " " << PlayerBoardDuplicate[1][1] << " " << PlayerBoardDuplicate[1][2] << " " << PlayerBoardDuplicate[1][3] << " " << PlayerBoardDuplicate[1][4] << " " << PlayerBoardDuplicate[1][5] << " " << PlayerBoardDuplicate[1][6] << " " << PlayerBoardDuplicate[1][7] << " " << PlayerBoardDuplicate[1][8] << " " << PlayerBoardDuplicate[1][9] << endl;
	cout << "                 C| " << EnemyBoard[2][0] << " " << EnemyBoard[2][1] << " " << EnemyBoard[2][2] << " " << EnemyBoard[2][3] << " " << EnemyBoard[2][4] << " " << EnemyBoard[2][5] << " " << EnemyBoard[2][6] << " " << EnemyBoard[2][7] << " " << EnemyBoard[2][8] << " " << EnemyBoard[2][9] << "         C| " << PlayerBoardDuplicate[2][0] << " " << PlayerBoardDuplicate[2][1] << " " << PlayerBoardDuplicate[2][2] << " " << PlayerBoardDuplicate[2][3] << " " << PlayerBoardDuplicate[2][4] << " " << PlayerBoardDuplicate[2][5] << " " << PlayerBoardDuplicate[2][6] << " " << PlayerBoardDuplicate[2][7] << " " << PlayerBoardDuplicate[2][8] << " " << PlayerBoardDuplicate[2][9] << endl;
	cout << "                 D| " << EnemyBoard[3][0] << " " << EnemyBoard[3][1] << " " << EnemyBoard[3][2] << " " << EnemyBoard[3][3] << " " << EnemyBoard[3][4] << " " << EnemyBoard[3][5] << " " << EnemyBoard[3][6] << " " << EnemyBoard[3][7] << " " << EnemyBoard[3][8] << " " << EnemyBoard[3][9] << "         D| " << PlayerBoardDuplicate[3][0] << " " << PlayerBoardDuplicate[3][1] << " " << PlayerBoardDuplicate[3][2] << " " << PlayerBoardDuplicate[3][3] << " " << PlayerBoardDuplicate[3][4] << " " << PlayerBoardDuplicate[3][5] << " " << PlayerBoardDuplicate[3][6] << " " << PlayerBoardDuplicate[3][7] << " " << PlayerBoardDuplicate[3][8] << " " << PlayerBoardDuplicate[3][9] << endl;
	cout << "                 E| " << EnemyBoard[4][0] << " " << EnemyBoard[4][1] << " " << EnemyBoard[4][2] << " " << EnemyBoard[4][3] << " " << EnemyBoard[4][4] << " " << EnemyBoard[4][5] << " " << EnemyBoard[4][6] << " " << EnemyBoard[4][7] << " " << EnemyBoard[4][8] << " " << EnemyBoard[4][9] << "         E| " << PlayerBoardDuplicate[4][0] << " " << PlayerBoardDuplicate[4][1] << " " << PlayerBoardDuplicate[4][2] << " " << PlayerBoardDuplicate[4][3] << " " << PlayerBoardDuplicate[4][4] << " " << PlayerBoardDuplicate[4][5] << " " << PlayerBoardDuplicate[4][6] << " " << PlayerBoardDuplicate[4][7] << " " << PlayerBoardDuplicate[4][8] << " " << PlayerBoardDuplicate[4][9] << endl;
	cout << "                 F| " << EnemyBoard[5][0] << " " << EnemyBoard[5][1] << " " << EnemyBoard[5][2] << " " << EnemyBoard[5][3] << " " << EnemyBoard[5][4] << " " << EnemyBoard[5][5] << " " << EnemyBoard[5][6] << " " << EnemyBoard[5][7] << " " << EnemyBoard[5][8] << " " << EnemyBoard[5][9] << "         F| " << PlayerBoardDuplicate[5][0] << " " << PlayerBoardDuplicate[5][1] << " " << PlayerBoardDuplicate[5][2] << " " << PlayerBoardDuplicate[5][3] << " " << PlayerBoardDuplicate[5][4] << " " << PlayerBoardDuplicate[5][5] << " " << PlayerBoardDuplicate[5][6] << " " << PlayerBoardDuplicate[5][7] << " " << PlayerBoardDuplicate[5][8] << " " << PlayerBoardDuplicate[5][9] << endl;
	cout << "                 G| " << EnemyBoard[6][0] << " " << EnemyBoard[6][1] << " " << EnemyBoard[6][2] << " " << EnemyBoard[6][3] << " " << EnemyBoard[6][4] << " " << EnemyBoard[6][5] << " " << EnemyBoard[6][6] << " " << EnemyBoard[6][7] << " " << EnemyBoard[6][8] << " " << EnemyBoard[6][9] << "         G| " << PlayerBoardDuplicate[6][0] << " " << PlayerBoardDuplicate[6][1] << " " << PlayerBoardDuplicate[6][2] << " " << PlayerBoardDuplicate[6][3] << " " << PlayerBoardDuplicate[6][4] << " " << PlayerBoardDuplicate[6][5] << " " << PlayerBoardDuplicate[6][6] << " " << PlayerBoardDuplicate[6][7] << " " << PlayerBoardDuplicate[6][8] << " " << PlayerBoardDuplicate[6][9] << endl;
	cout << "                 H| " << EnemyBoard[7][0] << " " << EnemyBoard[7][1] << " " << EnemyBoard[7][2] << " " << EnemyBoard[7][3] << " " << EnemyBoard[7][4] << " " << EnemyBoard[7][5] << " " << EnemyBoard[7][6] << " " << EnemyBoard[7][7] << " " << EnemyBoard[7][8] << " " << EnemyBoard[7][9] << "         H| " << PlayerBoardDuplicate[7][0] << " " << PlayerBoardDuplicate[7][1] << " " << PlayerBoardDuplicate[7][2] << " " << PlayerBoardDuplicate[7][3] << " " << PlayerBoardDuplicate[7][4] << " " << PlayerBoardDuplicate[7][5] << " " << PlayerBoardDuplicate[7][6] << " " << PlayerBoardDuplicate[7][7] << " " << PlayerBoardDuplicate[7][8] << " " << PlayerBoardDuplicate[7][9] << endl;
	cout << "                 I| " << EnemyBoard[8][0] << " " << EnemyBoard[8][1] << " " << EnemyBoard[8][2] << " " << EnemyBoard[8][3] << " " << EnemyBoard[8][4] << " " << EnemyBoard[8][5] << " " << EnemyBoard[8][6] << " " << EnemyBoard[8][7] << " " << EnemyBoard[8][8] << " " << EnemyBoard[8][9] << "         I| " << PlayerBoardDuplicate[8][0] << " " << PlayerBoardDuplicate[8][1] << " " << PlayerBoardDuplicate[8][2] << " " << PlayerBoardDuplicate[8][3] << " " << PlayerBoardDuplicate[8][4] << " " << PlayerBoardDuplicate[8][5] << " " << PlayerBoardDuplicate[8][6] << " " << PlayerBoardDuplicate[8][7] << " " << PlayerBoardDuplicate[8][8] << " " << PlayerBoardDuplicate[8][9] << endl;
	cout << "                 J| " << EnemyBoard[9][0] << " " << EnemyBoard[9][1] << " " << EnemyBoard[9][2] << " " << EnemyBoard[9][3] << " " << EnemyBoard[9][4] << " " << EnemyBoard[9][5] << " " << EnemyBoard[9][6] << " " << EnemyBoard[9][7] << " " << EnemyBoard[9][8] << " " << EnemyBoard[9][9] << "         J| " << PlayerBoardDuplicate[9][0] << " " << PlayerBoardDuplicate[9][1] << " " << PlayerBoardDuplicate[9][2] << " " << PlayerBoardDuplicate[9][3] << " " << PlayerBoardDuplicate[9][4] << " " << PlayerBoardDuplicate[9][5] << " " << PlayerBoardDuplicate[9][6] << " " << PlayerBoardDuplicate[9][7] << " " << PlayerBoardDuplicate[9][8] << " " << PlayerBoardDuplicate[9][9] << endl;
	cout << endl;
}

