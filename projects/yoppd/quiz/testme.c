#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int randnum = (rand() % 94) + 32; //0-93 -> 32-125
	//32-125 for ascii values
	char newchar = (char)randnum;
    return newchar;
}

char *inputString(char *array)
{
    //97 to 122 = a to z
    int count;
    for(count =0; count < 3; count++)
    {
    	array[count] = (char)(rand() % 26 + 97);
    }
    array[3] = (char)(rand() %	3 + 100 );
    array[4] = 't';	
    array[5] = '\0';

    return array;
}

void testme()
{
  char array[6];
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString(array);
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
