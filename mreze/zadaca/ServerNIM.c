#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "ProtokolNIM.h"
#define N 10
typedef struct
{
	int commSocket;
	char *dekadskiIP;

	int commSocket2;
	char *dekadskiIP2;

	int indexDretve;
	int redIgraca;
	int jeli_prvi_potez;
} obradiKlijenta__parametar;
obradiKlijenta__parametar parametarDretve[N];
int aktivneDretve[N] = { 0 };
int zasebneHrpe[N][3];
int aktivniIgraci[N*2]={0};
int brojIgraca=0;
pthread_mutex_t lokot_aktivneDretve = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lokot_2=PTHREAD_MUTEX_INITIALIZER;

int sibice[3]={0,0,0};

char* int_to_string(int n)
{
	if(n==0)
	{
		char *str=malloc(2*sizeof(char));
		str[0]='0';
		str[1]='\0';
		return str;
	}
	char pom[100];
	int nn,rem,len=0;
	nn = n;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	n = nn;
	char *str=malloc((len+1)*sizeof(char));
	for (int i = 0; i < len; i++)
	{
		rem = n % 10;
		n = n / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
	return str;
}

void obradi( int sock, int broj_hrpe, char *poruka, int *red, int indexDretve,int *gotovo);
void svakopotezni_izvjestaj(int commSocket,int indexDretve)
{
	char pom[100];

		strcpy(pom,"Hrpa A:");
		strcat(pom,int_to_string(zasebneHrpe[indexDretve][0]));
		strcat(pom,"  Hrpa B:");
		strcat(pom,int_to_string(zasebneHrpe[indexDretve][1]));
		strcat(pom,"  Hrpa C:");
		strcat(pom,int_to_string(zasebneHrpe[indexDretve][2]));

		posaljiPoruku( commSocket, ODGOVOR, pom );
}
void* komunicirajSaKlijentom( void* parametar )
{
	int vrstaPoruke,vrstaPoruke2, gotovo = 0;
	char *poruka,*poruka2;
	obradiKlijenta__parametar *param = (obradiKlijenta__parametar *) parametar;
	int commSocket  = param->commSocket;
	int commSocket2 = param->commSocket2;
	int indexDretve = param->indexDretve;

	
	while( !gotovo )
	{
		if(param->redIgraca==0)
		{	
			if(param->jeli_prvi_potez==1)
			{
				posaljiPoruku( commSocket, ODGOVOR, "" );
				param->jeli_prvi_potez=0;
			}
			else
			{
				svakopotezni_izvjestaj(commSocket,indexDretve);
			}
			if( primiPoruku( commSocket, &vrstaPoruke, &poruka ) != OK )
			{
				if(vrstaPoruke==0)continue;
				printf( "Greska u komunikaciji sa klijentom [socket=%d]...\n", commSocket );
				gotovo = 1;
				continue;
			}
			
			switch( vrstaPoruke )
			{
				case A: obradi( commSocket,0, poruka, &param->redIgraca, indexDretve,&gotovo); break; 
				case B: obradi( commSocket,1, poruka, &param->redIgraca, indexDretve,&gotovo); break;
				case C: obradi( commSocket,2, poruka, &param->redIgraca, indexDretve,&gotovo); break;
				case BOK: posaljiPoruku( commSocket, ODGOVOR, "OK" ); gotovo = 1; break;
				default: posaljiPoruku( commSocket, ODGOVOR, "Nepostojeci kod poruke!\n" );
			}
				
			free( poruka );
			if(gotovo==1)break;
		}
		if(param->redIgraca==1)
		{	
			svakopotezni_izvjestaj(commSocket2,indexDretve);
			if( primiPoruku( commSocket2, &vrstaPoruke2, &poruka2 ) != OK )
			{
				if(vrstaPoruke2==0)continue;
				printf( "Greska u komunikaciji sa klijentom [socket=%d]...\n", commSocket2 );
				gotovo = 1;
				continue;
			}
				
			switch( vrstaPoruke2 )
			{
				case A: obradi( commSocket2,0, poruka2, &param->redIgraca, indexDretve,&gotovo); break; 
				case B: obradi( commSocket2,1, poruka2, &param->redIgraca, indexDretve,&gotovo); break;
				case C: obradi( commSocket2,2, poruka2, &param->redIgraca, indexDretve,&gotovo); break;
				case BOK: posaljiPoruku( commSocket2, ODGOVOR, "OK" ); gotovo = 1; break;
				default: posaljiPoruku( commSocket2, ODGOVOR, "Nepostojeci kod poruke!\n" );
			}
						
			free( poruka2 );
		}
	}
	pthread_mutex_lock( &lokot_2 );
	aktivneDretve[ indexDretve ] = 2;
	pthread_mutex_unlock( &lokot_2 );
	
	aktivniIgraci[indexDretve*2]=0;
	aktivniIgraci[indexDretve*2+1]=0;

	printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", param->dekadskiIP, commSocket );
	close(commSocket);
	brojIgraca--;

	printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", param->dekadskiIP2, commSocket2 );
	close(commSocket2);
	brojIgraca--;
}
void stanjeHrpaSibica(char* pom,int indexDretve)
{
	strcpy(pom,"Na hrpi ");
	char opcija[2];
	opcija[0]='A';
	opcija[1]='\0';
	strcat(pom,opcija);
	strcat(pom," je ostalo jos ");
	strcat(pom,int_to_string(zasebneHrpe[indexDretve][0]));

	strcat(pom,"\nNa hrpi ");
	opcija[0]='B';
	opcija[1]='\0';
	strcat(pom,opcija);
	strcat(pom," je ostalo jos ");
	strcat(pom,int_to_string(zasebneHrpe[indexDretve][1]));

	strcat(pom,"\nNa hrpi ");
	opcija[0]='C';
	opcija[1]='\0';
	strcat(pom,opcija);
	strcat(pom," je ostalo jos ");
	strcat(pom,int_to_string(zasebneHrpe[indexDretve][2]));
}
void izvjestajIgracu(int commSocket)
{
	char pom[100];
		strcpy(pom,int_to_string(brojIgraca));
		strcat(pom,". spojen na server\n");
		strcat(pom,"Hrpa A:");
		strcat(pom,int_to_string(sibice[0]));
		strcat(pom,"  Hrpa B:");
		strcat(pom,int_to_string(sibice[1]));
		strcat(pom,"  Hrpa C:");
		strcat(pom,int_to_string(sibice[2]));

		posaljiPoruku( commSocket, ODGOVOR, pom );
}
int main( int argc, char **argv )
{
	if( argc != 5 )
		error2( "Upotreba: %s port hrpaA hrpaB hrpaC\n", argv[0] );
		
	int port; sscanf( argv[1], "%d", &port );
	sscanf(argv[2],"%d",&sibice[0]);
	sscanf(argv[3],"%d",&sibice[1]);
	sscanf(argv[4],"%d",&sibice[2]);

	// socket...
    int listenerSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( listenerSocket == -1 )
		myperror( "socket" );
		
	// bind...
	struct sockaddr_in mojaAdresa;

	mojaAdresa.sin_family = AF_INET;
	mojaAdresa.sin_port = htons( port );
	mojaAdresa.sin_addr.s_addr = INADDR_ANY;
	memset( mojaAdresa.sin_zero, '\0', 8 );
	
	if( bind( listenerSocket,
		      (struct sockaddr *) &mojaAdresa,
		      sizeof( mojaAdresa ) ) == -1 )
		myperror( "bind" );
		
	// listen
	if( listen( listenerSocket, N*2 ) == -1 )
		myperror( "listen" );
		
	pthread_t dretve[N];
	// accept
	while( 1 )
	{
        struct sockaddr_in klijentAdresa;
		int lenAddr = sizeof( klijentAdresa );

		int commSocket = accept( listenerSocket,
			                     (struct sockaddr *) &klijentAdresa,
			                     &lenAddr );

		if( commSocket == -1 )
			myperror( "accept" );
		brojIgraca++;
		izvjestajIgracu(commSocket);

		char *dekadskiIP = inet_ntoa( klijentAdresa.sin_addr );
		printf( "Prihvatio konekciju od %s [socket=%d]\n", dekadskiIP, commSocket );

		struct sockaddr_in klijentAdresa2;
		int lenAddr2 = sizeof( klijentAdresa2 );

		int commSocket2 = accept( listenerSocket,
			                     (struct sockaddr *) &klijentAdresa2,
			                     &lenAddr2 );

		if( commSocket2 == -1 )
			myperror( "accept" );
		brojIgraca++;
		izvjestajIgracu(commSocket2);

		char *dekadskiIP2 = inet_ntoa( klijentAdresa2.sin_addr );
		printf( "Prihvatio konekciju od %s [socket=%d]\n", dekadskiIP2, commSocket2 );


		pthread_mutex_lock( &lokot_aktivneDretve );
		int i, indexNeaktivne = -1;
		for( i = 0; i < N; ++i )
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
			close( commSocket2 );
			printf( "--> ipak odbijam konekciju jer nemam vise dretvi.\n" );
		}
		else
		{
			aktivniIgraci[indexNeaktivne*2]=commSocket;
			aktivniIgraci[indexNeaktivne*2+1]=commSocket2;

		    aktivneDretve[indexNeaktivne] = 1;
			parametarDretve[indexNeaktivne].commSocket = commSocket;
			parametarDretve[indexNeaktivne].commSocket2 = commSocket2;
			parametarDretve[indexNeaktivne].jeli_prvi_potez=1;
			parametarDretve[indexNeaktivne].indexDretve = indexNeaktivne;
			parametarDretve[indexNeaktivne].dekadskiIP = malloc((sizeof(dekadskiIP)+1)*sizeof(char));			
			parametarDretve[indexNeaktivne].dekadskiIP2 = malloc((sizeof(dekadskiIP2)+1)*sizeof(char));
			strcpy(parametarDretve[indexNeaktivne].dekadskiIP,dekadskiIP);
			strcpy(parametarDretve[indexNeaktivne].dekadskiIP2,dekadskiIP2);
			parametarDretve[indexNeaktivne].redIgraca=0;
			printf( "--> koristim dretvu broj %d.\n", indexNeaktivne );
			
			zasebneHrpe[indexNeaktivne][0]=sibice[0];
			zasebneHrpe[indexNeaktivne][1]=sibice[1];
			zasebneHrpe[indexNeaktivne][2]=sibice[2];

			pthread_create(
				&dretve[indexNeaktivne], NULL,
				komunicirajSaKlijentom, &parametarDretve[indexNeaktivne] );
		}
		pthread_mutex_unlock( &lokot_aktivneDretve );				
	}
	
	return 0;
}



void obradi( int sock,int broj_hrpe, char *poruka ,int *red,int indexDretve, int *gotovo)
{
	int koliko;
	if(zasebneHrpe[indexDretve][0]==0 && zasebneHrpe[indexDretve][1]==0 && zasebneHrpe[indexDretve][2]==0)
	{
		char pom[100];
		strcpy(pom,"Igrac broj ");
		strcat(pom,int_to_string((*red+1)%2+(N-indexDretve-1)*2+1));
		strcat(pom,". je pobijedio!");
		posaljiPoruku(aktivniIgraci[indexDretve*2],ODGOVOR,pom);
		posaljiPoruku( aktivniIgraci[indexDretve*2+1], ODGOVOR, pom);
		*gotovo=1;
		return;
	}
	if( sscanf( poruka, "%d\n", &koliko ) != 1 || koliko <= 0 )
	{
		posaljiPoruku( sock, ODGOVOR, "Pogresan oblik naredbe" );
		return;
	}
	if(zasebneHrpe[indexDretve][broj_hrpe]==0)posaljiPoruku( sock, ODGOVOR, "Hrpa je prazna.Ponovo!" );
	else if(zasebneHrpe[indexDretve][broj_hrpe]>=koliko)
	{
		zasebneHrpe[indexDretve][broj_hrpe]-=koliko;
		char pom[200];

		stanjeHrpaSibica(pom,indexDretve);

		posaljiPoruku(sock,ODGOVOR,pom);

		if(*red == 0)*red=1;
		else *red=0;
	}
	else posaljiPoruku( sock, ODGOVOR, "Nije moguce dignit toliko sibica.Ponovo!" );
}

