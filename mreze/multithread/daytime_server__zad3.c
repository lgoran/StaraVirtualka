/*
	Vjezbe 6 -- Zadatak 3
	daytime-server -- spava 20 sekundi prije slanja vremena klijentu
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

void obradiKlijenta( int commSocket )
{
	// jedina promjena u odnosu na vjezbe 04:
	sleep( 20 );
	// kraj promjene

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
		printf( "Prihvatio konekciju od %s\n", dekadskiIP );
		
		obradiKlijenta( commSocket );
		close( commSocket );
	}

	return 0;
}
