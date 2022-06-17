#include <iostream>
#include<string> 
#include<fstream>
#include <conio.h> 
#include <windows.h> // speed of the snake 
#include<cstdio>
using namespace std;

class Snake // class snake 
{
protected:
	const int width; // Box width 
	const int height; // Box height 
	int x, y;  
	int fruitX, fruitY, score;  // fruit location and score 
	int Tail = 0; // tail intialize  
	int tailX[100], tailY[100];  
	enum eDirecton{ STOP=0, LEFT, RIGHT, UP, DOWN }; // enumiration // dectect keyboard direaction (up,down,left,right)
	eDirecton d; // object of enumiration 
public:
	bool gameOver; // game over 
	Snake():width(20), height(20) // snake width and height, pre declaration 
	{
		
	}
};
class setup :public virtual Snake // box setup class 
{
public:
	void Setup() 
	{
		gameOver = false;
		d = STOP; // no key pressed so game stop, as you press key game starts
		x = width / 2;  // box width and height 
		y = height / 2;
		fruitX = rand() % width;  // this is to spawn the fruit at a random spot 
		fruitY = rand() % height; // this is to spawn the fruit at a random spot 
		score = 0; 
	}
};
class input :public virtual Snake //  keyboard input class 
{
public:
	void Input()
	{
		char t;
		if (_kbhit())  // _kbhit (keyboard hit), this is to directly register the keybaord input, without this functuon you have to manually press enter for each keyboard key 
		{
			t = _kbhit(); // stored kbhit into t 
			t = _getch(); // stored getch in t, keybaord input will be sotred in getch 
			switch (_getch())
			{
			case 75: // LEFT KEY (keyboard)
				d = LEFT;
				break;
			case 77: // RIGHT KEY
				d = RIGHT;
				break;
			case 72: // UP KEY
				d = UP;
				break;
			case 80: // DOWN KEY 
				d = DOWN;
				break;
			default:
				cout << "Wrong key entered gg!";
				gameOver = true;  // SYSTEM WILL END HERE 
				break;
			}
		}
	}
};

class draw :public input, public setup  // class used to make the actual box 
{
public:
	void Draw()
	{
		COORD coord;                                                      //used as an alternate for system("cls")
		coord.X = 0;                                                      //
		coord.Y = 0;                                                      //
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //
		
		
		for (int i = 0; i < width + 2; i++) // +2 to fill the box 
		cout << "%";                          //topwall
		cout << endl;
		for (int i = 0; i < height; i++) 
		{
			for (int j = 0; j < width; j++) // for left and right 
			{
				if (j == 0)
					cout << "%";                     //leftwall
				if (i == y && j == x)
					cout << "O";                     //snakehead
				else if (i == fruitY && j == fruitX)
					cout << "*";                     //fruitdesign
				else
				{
					bool p = false; // bool to print empay space 
					for (int k = 0; k < Tail; k++)
					{
						if (tailX[k] == j && tailY[k] == i) // printing tail 
						{; 
							cout << "o";           //snaketail
							p = true;
						}
					}
					if (!p)
						cout << " ";                //empty space
				}


				if (j == width - 1)
					cout << "%";                    //rightwall
			}
			cout << endl;
		}
		for (int i = 0; i < width + 2; i++)
			cout << "%";                            //bottomwall
		cout << endl<<endl;
		cout << "Score:" << score << endl; // scaore updated because we keep calling function in loop
		
	}

};
class logic : public draw // logic class 
{
public:
	void Logic()
	{
		int pX = tailX[0]; // storing tail x intial position 
		int pY = tailY[0]; // storing tail y intail position 
		int p2X, p2Y;
		tailX[0] = x; // storing x value in tail 
		tailY[0] = y; // ....
		for (int i = 1; i < Tail; i++) 
		{
			p2X = tailX[i]; // when eats tail the value will be updated 
			p2Y = tailY[i]; // .....
			tailX[i] = pX;  // storing new value back 
			tailY[i] = pY;  // ........
			pX = p2X;    // To store the next new value and repeat the loop
			pY = p2Y;   // ......
		}
		switch (d) 
		{
		case LEFT:
			x--; // will move x position back by one 
			break;
		case RIGHT:
			x++;  // ....
			break;
		case UP:
			y--; // in c++ we use - to go up fo y cordinates 
			break;
		case DOWN:
			y++; // ....
			break;
		default:
			break;
		}
		if (x >= width)
		{
			x = 0; // this is to bring back x to 0 of that line once it hits the wall 
		}
		else if (x < 0)
		{
			x = width - 1; // this is for the left side, 
		}
		if (y >= height) 
		{
			y = 0;  // same stuff for hight now
		}
		else if (y < 0)
		{
			y = height - 1; // ..... 
		}
		for (int i = 0; i < Tail; i++)  
		{
			if (tailX[i] == x && tailY[i] == y)
				gameOver = true;  // tail meets other tail end, game over 
		}
		if (x == fruitX && y == fruitY) // if the snake eats fruit, tail will increase size 
		{
			score = score + 1; // scare will also increase once tail increases 
			fruitX = rand() % width; // this is to spawn the fruit randomly 
			fruitY = rand() % height; // ..... 
			Tail++; // incremnet the tail size 
		}
	}
	void Snake_board() // will put vlaue in txt file from score input 
	{
		ofstream of("abcd.txt", ios::app); // filing 
		of << score << endl;
	}
	void scoreboard() // taking vlaue from the txt file and putting onto the system 
	{
	
		int k = 0, i = 0, number, a[99], count = 0, desc, j, l = score;
		ifstream input_file("abcd.txt");

		while (input_file >> number) { // used to read file 
			a[i] = number; i++; count++; // keep reading next line ( IF 6 IN FILE, I++ used to point next array( used to read next line) 
		}
		for (i = 0; i < count; ++i)
		{
			for (j = i + 1; j < count; ++j)
			{
				if (a[i] < a[j])
				{
					desc = a[i]; // decending order loop for leaderboard 
					a[i] = a[j];
					a[j] = desc;
				}
			}
		}
		cout << "\n\n\t\tSCORE BOARD\n\n";
		int op = 1;
		for (i = 0; i < count; ++i)
		{
			cout << "\t\t"<<op++<<".     "; // 1,2,3,4 standings 
			cout << a[i];
			if (a[i] == l)
			{
				cout << "<---- Your position on score board"; // this is tp point out your live score in the leaderboard 
				k++;
				if (k >= 1)
					l = 90;
			}
			cout << "\n";

		}
		cout << endl;
		input_file.close();
	}
};
int main()
{
	int i;
	char choice;
	cout << "\n\n\n\t\tWELCOME TO MY SNAKE GAME" << endl;
	cout << "  \n\n\n\n\n\t\tpress spacebar to begin.........";
	cout << "\n\n\n\n\n\n\n\t\t\tMade by: Emad Qureshi";
	cout << "\n\t\t\t          K21-3418 ";
	choice = _getche(); // keybaord hit stored in choice 
	choice = toupper(choice);
	switch (choice)
	{
	case 32: // space bar 
	{
		system("cls"); // clear screen to show next menu 
		cout << "\n\tEnter difficulty" << endl;
		cout << "\n\t1-Recruit" << endl;
		cout << "\n\t2-Easy" << endl;
		cout << "\n\t3-Medium" << endl;
		cout << "\n\t4-Hard " << endl;
		cout << "\n\t5-Veteran" << endl;
		cin >> i;
		switch (i)
		{
			// setting diffrent speed levels for each difficulty 
		case 1:
			i = 140; 
			break;
		case 2:
			i = 120;
			break;
		case 3:
			i = 80;
			break;
		case 4:
			i = 60;
			break;
		case 5:
			i = 0;
			break;
		default:
			break;
		}
		system("cls");
		logic ob2;
		ob2.Setup();
		while (!ob2.gameOver)
		{
			ob2.Draw(); // board draw 
			ob2.Input(); // take input from user
			ob2.Logic(); // for making logic 
			Sleep(i); // sleep is the delay funtion( for exapmle o sleep it will be very fast, 20 it will be slower, basically delay (speed ms )
		}
		system("cls");
		ob2.Snake_board();
		ob2.scoreboard();
	}
	default:
		exit(0); 
		break;
	}
	return 0;
}
