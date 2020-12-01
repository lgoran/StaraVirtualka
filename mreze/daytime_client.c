/*
	Vjezbe 4 -- Zadatak 1
	daytime-klijent
	Spaja se na IP-adresu proslijedjenu kao prvi argument komandne linije.
	Koristi port proslijedjen kao drugi argument komandne linije.
	
	Npr. za spajanje na daytime server na studentu treba pozvati program sa:
	./daytime-client 161.53.8.14 13
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main( int argc, char **argv )
{
	if( argc != 3 )
	{
		printf( "Upotreba: %s ip-adresa port\n", argv[0] );
		exit( 0 );
	}

	// socket...
	int mojSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( mojSocket == -1 )
   		perror( "socket" );

	// dohvati IP-adresu iz 1. argumenta komandne linije
	char dekadskiIP[ 20 ];
	strcpy( dekadskiIP, argv[1] );

	// dohvati port iz 2. argumenta komandne linije
	int port;
	sscanf( argv[2], "%d", &port );

	// connect...
	struct sockaddr_in adresaServera;

	adresaServera.sin_family = AF_INET;
	adresaServera.sin_port = htons( port );

	if( inet_aton( dekadskiIP, &adresaServera.sin_addr ) == 0 )
		printf( "%s nije dobra adresa!\n", dekadskiIP );

	memset( adresaServera.sin_zero, '\0', 8 );

	if( connect( mojSocket,
	             (struct sockaddr *) &adresaServera,
	             sizeof( adresaServera ) ) == -1 )
		perror( "connect" );
	   
	// recv...
	char buffer[1000];
	int primljeno = 0; // koliko smo byte-ova ukupno primili
	int novoprimljeno; // koliko je primljeno u zadnjem recv

	while( 1 )
	{
		novoprimljeno = recv(
			mojSocket,
			buffer + primljeno,
			sizeof( buffer ) - primljeno - 1,
			0 );

		if( novoprimljeno == -1 ) { perror( "recv" ); exit(0); }
		else if( novoprimljeno == 0 ) break;
		else primljeno += novoprimljeno;
	}
	buffer[primljeno] = '\0';

	printf( "Poruka od servera:\n" );
	printf( "%s", buffer );
	printf( "------------------\n" );

	// close...
 	if( close( mojSocket ) == -1 )
		perror( "close" );

	return 0;
}
