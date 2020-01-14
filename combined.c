#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a,b,c,d;

	a=10; b=20; c=30; d=4;

	// these lines ...
	a=a+2;
	b=b-12;
	c=c*(d-2);
	printf( "a=%d, b=%d, c=%d\n", a, b, c);

	a=10; b=20; c=30; d=4;

	// could have been written this way
	a += 2;
	b -= 12;
	c *= d-2;
	printf( "a=%d, b=%d, c=%d\n", a, b, c);

	exit (0);
}
