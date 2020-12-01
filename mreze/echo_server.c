/*
	Vjezbe 4 -- Zadatak 3
	echo-server
	(radi na portu 31416)
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


void obradiKlijenta( int sock )
{
	// obratnim redoslijedom nego client: prvo recv, pa onda send
	// problem: ne znam koliko podataka trebam primati...
	// rjesenje: cim nesto primis, to i posalji, koliko god to podataka bilo
	
	char buffer[5]; // namjerno je mali broj da se vidi kako stvar funkcionira :)
	int primljeno;

	while( 1 ) // petlja sve dok klijent ne prekine konekciju
	{
		primljeno = recv(
			sock,
			buffer, // mogu gaziti preko onog sto sam ranije primio
			sizeof( buffer ),
			0 );

		if( primljeno == -1 ) { perror( "recv" ); break; }
		else if( primljeno == 0 ) { printf( "Klijent je prekinuo komunikaciju...\n" ); break; }
		else posalji( sock, buffer, primljeno );
	}
}


int main ( void ) // skroz isto kao za daytime_server, samo je drugi port
{
	// socket...
	int listenerSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( listenerSocket == -1 )
	    perror( "socket" );

	// bind...
	struct sockaddr_in mojaAdresa;

	mojaAdresa.sin_family      = AF_INET;
	mojaAdresa.sin_port        = htons( 31416 );
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
