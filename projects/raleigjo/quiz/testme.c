#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	int randomArray;
	char randomChar;
	char charArray[9] = { '[', '(', '{', ' ', 'a', 'x', '}', ')', ']' };

	//translate number to ASCII character, needs coverage of "[({ ax})]"
	//standard random generator to point to char array
	//rand seeded in main.

	randomArray = rand() % 10;
	randomChar = charArray[randomArray];

    return randomChar;
}

char *inputString()
{
	int i;
	int charSelector;
	char charArrayB[4] = { 'r', 'e', 's', 't' };
	static char stringReturn[6];

	//generate string of length 6
	//draw from array of chars specified in testme()
	//standard random generator to point to char array
  //array declared as static to safely return to testme function.

	for(i=0; i<5; i++)
	{
		charSelector = rand() % 4;
		stringReturn[i] = charArrayB[charSelector];
	}

	stringReturn[5] = '\0';

    return stringReturn;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
