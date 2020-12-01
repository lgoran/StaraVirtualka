/*
	Vjezbe 06 -- Zadatak 1
	brojanje__threads.c: koristi vise dretvi, ali ne i mutex-e
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define error( s ) { printf( s ); exit( 0 ); }

int j = 0;

void *ispisuj( void *parametar )
{
	int index = *((int *) parametar);
	int i;
	
	for( i = 1; i <= 20; ++i )
	{
		++j;
		while(rand()%10000!=0){}
	    printf( "Funkcija sa parametrom: " );
		printf( "%d ispisuje ", index );
		printf( "%d; j = %d.\n", i, j );
	}
	    
	return NULL;
}

int main( void )
{
	int index1, index2, bad;
	pthread_t dretva[2];
	
	index1 = 1;
	bad = pthread_create( &dretva[0], NULL, ispisuj, (void *)&index1 );
	if( bad )
	    error( "Greska prilikom kreiranja dretve 1!\n" );
	
	index2 = 2;
	bad = pthread_create( &dretva[1], NULL, ispisuj, (void *)&index2 );
	if( bad )
	    error( "Greska prilikom kreiranja dretve 2!\n" );

	printf("gotov\n");
	pthread_join( dretva[0], NULL );
	pthread_join( dretva[1], NULL );

	return 0;
}
