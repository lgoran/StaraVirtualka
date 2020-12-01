/*
	Vjezbe 4 -- Zadatak 3
	echo-klijent
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define error( s1, s2 ) { printf( s1, s2 ); exit( 0 ); }


void posalji( int sock, char *poruka, int duljinaPoruke )
{
	int poslano = 0; // broj do sada poslanih byte-ova
	int poslanoZadnje; // koliko je poslano u zadnjem send

	while( poslano != duljinaPoruke )
	{
		poslanoZadnje = send(
			sock,
			poruka + poslano,
			duljinaPoruke - poslano,
			0 );

		if( poslanoZadnje == -1 ) { perror( "send" ); break; }
		else poslano += poslanoZadnje;
	}
}


void primiOdgovor( int sock, char *buffer, int bufferSize, int duljinaOdgovora )
{
	// problem: nikako ne mozemo znati koliko je dugacak odgovor!
	// pretpostavimo da je jednako dug kao i poslana rijec :)

	// recv...
	int primljeno = 0; // koliko smo byte-ova ukupno primili
	int novoprimljeno; // koliko je primljeno u zadnjem recv

	while( primljeno != duljinaOdgovora )
	{
		novoprimljeno = recv(
			sock,
			buffer + primljeno,
			bufferSize-1 - primljeno,
			0 );

		if( novoprimljeno == -1 ) { perror( "recv" ); break; }
		else if( novoprimljeno == 0 ) { printf( "Server je prekinuo komunikaciju...\n" ); break; }
		else primljeno += novoprimljeno;
	}
	
	buffer[primljeno] = '\0';
}


int main ( int argc, char **argv )
{
	if( argc != 3 )
	    error( "Upotreba: %s ip-adresa port\n", argv[0] );

	// socket...
	int mojSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( mojSocket == -1 )
   		perror( "socket" );

	// connect...
	char *dekadskiIP = argv[1];
	int port;
	sscanf( argv[2], "%d", &port );
	
	struct sockaddr_in adresaServera;

	adresaServera.sin_family = AF_INET;
	adresaServera.sin_port = htons( port );

	if( inet_aton( dekadskiIP, &adresaServera.sin_addr ) == 0 )
		printf( "%s nije dobra adresa!\n", dekadskiIP );

	memset( adresaServera.sin_zero, '\0', 8 );

	if( connect(
			mojSocket,
			(struct sockaddr *) &adresaServera,
			sizeof( adresaServera ) ) == -1 )
	   perror( "connect" );
	   
	   
	while( 1 )
	{
		char rijec[100], odgovor[100];
		
		printf( "Unesi rijec koju cu poslati serveru: " );
		scanf( "%s", rijec );
		if( !strcmp( rijec, "kraj" ) )
		    break;
		
		posalji( mojSocket, rijec, strlen( rijec ) );
		primiOdgovor( mojSocket, odgovor, sizeof( odgovor ), strlen( rijec ) );
		
		printf( "Odgovor servera .................... %s\n\n", odgovor );
	}
	
	// close...
 	if( close( mojSocket ) == -1 )
		perror( "close" );

	return 0;
}
