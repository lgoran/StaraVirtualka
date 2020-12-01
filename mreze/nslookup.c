/*
	Vjezbe 3 -- Zadatak 3
	Program emulira ponasanje mreznog alata nslookup.
*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define error1(s1) { printf( s1 ); exit( 0 ); }
#define error2(s1, s2) { printf( s1, s2 ); exit( 0 ); }

int main( int argc, char **argv )
{
	// je li programu proslijedjen tocno 1 parametar?
	if( argc != 2 )
	    error2( "Upotreba: %s host-name\n", argv[0] );

    struct hostent *hostInfo;
	hostInfo = gethostbyname( argv[1] );
	if( hostInfo == NULL )
	{
		// herror( "gethostbyname: " ); // na nekim sustavima funkcija herror nije dostupna
		error1( "Programu nije proslijedjen ispravni host-name!\n " );
	}

	// ispis svih host-name-ova koje racunalo koristi
	printf( "Sluzbeni host-name: %s\n", hostInfo->h_name );

	int i;
	for( i = 0; hostInfo->h_aliases[i] != NULL; ++i )
	    printf( "Alternativni host-name: %s\n", hostInfo->h_aliases[i] );
	
	// ispis IP-adresa koje racunalo koristi
	printf( "\n" );
	for( i = 0; hostInfo->h_addr_list[i] != NULL; ++i )
	{
		struct in_addr binarniIP = *( (struct in_addr *) hostInfo->h_addr_list[i] );
		char *dekadskiIP = inet_ntoa( binarniIP );
		printf( "IP-adresa: %s\n", dekadskiIP );
	}
	
	return 0;
}
