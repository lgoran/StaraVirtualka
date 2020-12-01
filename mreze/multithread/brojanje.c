/*
	Vjezbe 06 -- Zadatak 1
	brojanje.c: koristi samo jednu dretvu
*/

#include <stdio.h>

int j = 0;

void *ispisuj( void *parametar )
{
	int index = *((int *) parametar);
	int i;
	
	for( i = 1; i <= 20; ++i )
	{
		++j;
	    printf( "Funkcija sa parametrom: " );
		printf( "%d ispisuje ", index );
		printf( "%d; j = %d.\n", i, j );
	}

	return NULL;
}

int main( void )
{
	int index1, index2;
	
	index1 = 1;
	ispisuj( &index1 );
	
	index2 = 2;
	ispisuj( &index2 );

	return 0;
}
