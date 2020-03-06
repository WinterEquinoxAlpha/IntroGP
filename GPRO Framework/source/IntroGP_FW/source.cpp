#include "IntroGP_FW/header.h"

int checkGuess(int age, int guess)
{
	if (guess < age)
	{
		return -1;
	}
	else if (guess > age)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}