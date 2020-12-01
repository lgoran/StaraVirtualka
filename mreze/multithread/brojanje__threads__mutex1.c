/*
	Vjezbe 06 -- Zadatak 2
	brojanje__threads__mutex.c: koristi vise dretvi i 1 mutex.
	
	Koristi zajednicki mutex za pristup ekranu i varijabli j.
	Ispis varijable j je ok.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define error( s ) { printf( s ); exit( 0 ); }

int j = 0;
pthread_mutex_t lokot_j_ekran = PTHREAD_MUTEX_INITIALIZER;

void *ispisuj( void *parametar )
{
	int index = *((int *) parametar);
	int i;

	for( i = 1; i <= 20; ++i )
	{
		pthread_mutex_lock( &lokot_j_ekran );
		++j;

	    printf( "Funkcija sa parametrom: " );
		printf( "%d ispisuje ", index );
		printf( "%d; j = %d.\n", i, j );

		pthread_mutex_unlock( &lokot_j_ekran );
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

	pthread_join( dretva[0], NULL );
	pthread_join( dretva[1], NULL );

	return 0;
}
