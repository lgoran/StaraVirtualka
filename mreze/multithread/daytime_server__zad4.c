/*
	Vjezbe 6 -- Zadatak 4
	daytime-server -- spava 20 sekundi prije slanja vremena klijentu
	Server je visenitni.
	(port se salje kao parametar komandne linije)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <pthread.h>

#define MAXDRETVI 3

typedef struct
{
	int commSocket;
	int indexDretve;
} obradiKlijenta__parametar;

int aktivneDretve[MAXDRETVI] = { 0 };
obradiKlijenta__parametar parametarDretve[MAXDRETVI];
pthread_mutex_t lokot_aktivneDretve = PTHREAD_MUTEX_INITIALIZER;

void *obradiKlijenta( void *parametar )
{
	sleep( 20 );
	
	obradiKlijenta__parametar *param = (obradiKlijenta__parametar *) parametar;
	int commSocket  = param->commSocket;
	int indexDretve = param->indexDretve;

    time_t trenutnoVrijeme;
	time( &trenutnoVrijeme );

	char buffer[100];
	sprintf( buffer, "%s", ctime( &trenutnoVrijeme ) );

	int trebaPoslati = strlen( buffer );
	int poslano = 0; // broj do sada poslanih byte-ova
	int poslanoZadnje; // koliko je poslano u zadnjem send

	while( poslano != trebaPoslati )
	{
		poslanoZadnje = send(
			commSocket,
			buffer + poslano,
			trebaPoslati - poslano,
			0 );

		if( poslanoZadnje == -1 ) { perror( "send" ); break; }
		else poslano += poslanoZadnje;
	}

	pthread_mutex_lock( &lokot_aktivneDretve );
	aktivneDretve[ indexDretve ] = 2;
	pthread_mutex_unlock( &lokot_aktivneDretve );
	
	close( commSocket );

	return NULL;
}

int main( int argc, char **argv )
{
	if( argc != 2 )
	{
		printf( "Upotreba: %s port\n", argv[0] );
		exit( 0 );
	}

	int port;
	sscanf( argv[1], "%d", &port );

	// socket...
	int listenerSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( listenerSocket == -1 )
	    perror( "socket" );

	// bind...
	struct sockaddr_in mojaAdresa;

	mojaAdresa.sin_family      = AF_INET;
	mojaAdresa.sin_port        = htons( port );
	mojaAdresa.sin_addr.s_addr = INADDR_ANY;
	memset( mojaAdresa.sin_zero, '\0', 8 );

	if( bind(
			listenerSocket,
			(struct sockaddr *) &mojaAdresa,
			sizeof( mojaAdresa ) ) == -1 )
		perror( "bind" );

	// listen...
	if( listen( listenerSocket, 10 ) == -1 )
		perror( "listen" );

	// ovo mozemo bolje rijesiti i pomocu liste dretvi, ali dobro...
	pthread_t dretve[10];
	
	while( 1 ) // vjecno cekamo nove klijente...
	{
		// accept...
		struct sockaddr_in klijentAdresa;
		int lenAddr = sizeof( klijentAdresa );
		int commSocket = accept( listenerSocket,
                         (struct sockaddr *) &klijentAdresa,
                         &lenAddr );
                         
		if( commSocket == -1 )
			perror( "accept" );

		char *dekadskiIP = inet_ntoa( klijentAdresa.sin_addr );
		printf( "Prihvatio konekciju od %s ", dekadskiIP );
		
		pthread_mutex_lock( &lokot_aktivneDretve );
		int i, indexNeaktivne = -1;
		for( i = 0; i < MAXDRETVI; ++i )
			if( aktivneDretve[i] == 0 )
				indexNeaktivne = i;
			else if( aktivneDretve[i] == 2 )
			{
				pthread_join( dretve[i], NULL );
				aktivneDretve[i] = 0;
				indexNeaktivne = i;
			}
			    
		if( indexNeaktivne == -1 )
		{
			close( commSocket ); // nemam vise dretvi...
			printf( "--> ipak odbijam konekciju jer nemam vise dretvi.\n" );
		}
		else
		{
		    aktivneDretve[indexNeaktivne] = 1;
			parametarDretve[indexNeaktivne].commSocket = commSocket;
			parametarDretve[indexNeaktivne].indexDretve = indexNeaktivne;
			printf( "--> koristim dretvu broj %d.\n", indexNeaktivne );
			
			pthread_create(
				&dretve[indexNeaktivne], NULL,
				obradiKlijenta, &parametarDretve[indexNeaktivne] );
		}
		pthread_mutex_unlock( &lokot_aktivneDretve );
	}

	return 0;
}
