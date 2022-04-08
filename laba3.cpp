#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Menu{
	private:
		vector <string> menu;
		HANDLE hStdOut;
		WORD background;
		WORD foreground;
		int position;
		
	public:
		Menu(vector <string> m, HANDLE hOut, WORD bg = BACKGROUND_BLUE, WORD fg=FOREGROUND_INTENSITY, int pos=0){
			menu = m;
			hStdOut = hOut;
			background = bg;
			foreground = fg;
			position = pos;
		}
		
		void print_menu();
		int catch_events();
		
};

void Menu::print_menu(){
	system("CLS");
	for (int i = 0; i < menu.size(); i++)
	{
		if (i == position)
		{
			SetConsoleTextAttribute(hStdOut, background);
			cout << i + 1 << ". " << menu[i] << endl;
			SetConsoleTextAttribute(hStdOut, 0x00 | foreground);
		}
	else { cout << i + 1 << ". " << menu[i] << endl; }
	}
}

int Menu::catch_events(){
	int z = int(_getch());
	if (z == 119 || z == 72) { position--; }
	else if (z == 115 || z == 80) { position++; }
	else if (z == 13) { return position; }
	if (position > menu.size()) { position = 0; }
	else if (position < 0) { position = menu.size() - 1;}
	
	return -1;
}

int main()
{
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	setlocale(LC_ALL, "Russian");
	
	vector <string> m;
	m.push_back("ADD");
	m.push_back("ADD1");
	m.push_back("Exit");
	
	Menu x = Menu(m, hStdOut);
	int f = 0;
	while (f < 2){
		x.print_menu();
		f = x.catch_events();
	}
	return 0;
}
