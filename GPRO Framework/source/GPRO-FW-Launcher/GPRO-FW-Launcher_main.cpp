// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include "IntroGP_FW/header.h"
#include <iostream>

int main()
{
	int num = 10;
	num = foo(num);
	std::cout << num << std::endl;
	return 0;
}