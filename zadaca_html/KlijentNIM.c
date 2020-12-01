
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "ProtokolNIM.h"

void obradi( int sock, int opcija);
void obradiBOK( int sock );

int main( int argc, char **argv )
{
	if( argc != 3 )
		error2( "Upotreba: %s IP-adresa port\n", argv[0] );

	char dekadskiIP[20]; strcpy( dekadskiIP, argv[1] );
	int port;          sscanf( argv[2], "%d", &port );

	// socket...
	int mojSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( mojSocket == -1 )
		myperror( "socket" );
		
	// connect...
	struct sockaddr_in adresaServera;
	
	adresaServera.sin_family = AF_INET;
	adresaServera.sin_port = htons( port );
	if( inet_aton( dekadskiIP, &adresaServera.sin_addr ) == 0 )
		error2( "%s nije dobra adresa!\n", dekadskiIP );
	memset( adresaServera.sin_zero, '\0', 8 );
	
	if( connect( mojSocket,
		        (struct sockaddr *) &adresaServera,
		        sizeof( adresaServera ) ) == -1 )
		myperror( "connect" );

	//poruka koji je po redu
	int vrstaPoruke; char *odgovor;
	if( primiPoruku( mojSocket, &vrstaPoruke, &odgovor ) != OK )
		error1( "Doslo je do pogreske u komunikaciji sa serverom...\n" );

	printf("%s\n",odgovor);
	
	// ispisi menu
	int gotovo = 0;
	while( !gotovo )
	{
		printf( "\n\nOdaberi opciju...\n"
				"   1. uklanjanje sa A-hrpe\n"
				"   2. uklanjanje sa B-hrpe\n"
				"   3. uklanjanje sa C-hrpe\n"
				"   4. izlaz iz programa\n"
				"   \n: " );
				
		int opcija;
		scanf( "%d", &opcija );
		
		switch( opcija )
		{
			case 1: obradi( mojSocket,A); break;
			case 2: obradi( mojSocket,B ); break;
			case 3: obradi( mojSocket,C ); break;
			case 4: obradiBOK( mojSocket ); gotovo = 1; break;
			default: printf( "Pogresna opcija...\n" ); break;
		}
	}

	close( mojSocket );

	return 0;
}

void obradi( int sock, int opcija)
{
	int kolicina;
	
	printf( "Koliko sibica zelite uzeti: " );
	scanf( "%d", &kolicina );
	
	char poruka[100];
	sprintf( poruka, "%d", kolicina );
	
	posaljiPoruku( sock, opcija, poruka );

	int vrstaPoruke; char *odgovor;
	if( primiPoruku( sock, &vrstaPoruke, &odgovor ) != OK )
		error1( "Doslo je do pogreske u komunikaciji sa serverom...\n" );
		
	if( vrstaPoruke != ODGOVOR )
		error1( "Doslo je do pogreske u komunikaciji sa serverom (nije poslao ODGOVOR)...\n" );
		
	if( strcmp( odgovor, "OK" ) != 0 )
		printf( "%s\n", odgovor );
	else
	    printf( "OK\n" );
	    
	free( odgovor );
}

void obradiBOK( int sock )
{
	posaljiPoruku( sock, BOK, "" );

	int vrstaPoruke;
	char *odgovor;
	if( primiPoruku( sock, &vrstaPoruke, &odgovor ) != OK )
		error1( "Doslo je do pogreske u komunikaciji sa serverom...\n" );

	if( vrstaPoruke != ODGOVOR )
		error1( "Doslo je do pogreske u komunikaciji sa serverom (nije poslao ODGOVOR)...\n" );

	if( strcmp( odgovor, "OK" ) != 0 )
		printf( "Greska: %s\n", odgovor );
	else
	    printf( "OK\n" );
}
