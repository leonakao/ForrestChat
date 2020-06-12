/* Chat multusuários em grupo*/

#include <stdio.h>
#include <winsock.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
//porta que será usadaa do server precisa ser igual a do cliente
//Nao esqueça de alterar o ip do servidor, e se a conexão será feita dentro da rede ou atráves de um dns.
#define port 8088

u_long modo=1;
WSADATA data;
SOCKET c_c;
SOCKADDR_IN sock;
char cone[100];
int bytes;
DWORD id;
HANDLE receber;

void mostrar (char msg[1024])
{
	setlocale(LC_ALL,"Portuguese");
	printf ("\r                                                            \r");
	puts(msg);
	printf ("->%s",cone);
	setlocale(LC_ALL,"C");
}

DWORD WINAPI msg(LPVOID p)
{
	char buffer2[1024];
	while (1)
	{
		strcpy (buffer2,"");
		memset(buffer2,0,1024);
		fflush (stdin);
		bytes=recv(c_c,buffer2,1024,0);
		if(bytes==-1)
		{
			printf("Conexão perdida");
			CloseHandle (receber);
			TerminateThread (receber,1);
			break;
		}
		mostrar(buffer2);
		//puts(buffer2);
	}
}

void conectar_rede ()
{
	if(WSAStartup(MAKEWORD(1,1),&data)==SOCKET_ERROR)
	{
		printf("Erro ao inicializar o c_c");
		getch();
		exit(1);
	}
	if((c_c = socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR)
	{
		printf("Erro ao criar socket");
		getch();
		exit(1);
	}
	sock.sin_family=AF_INET;
	sock.sin_port=htons(port);
	sock.sin_addr.s_addr=inet_addr("192.168.43.97"); //Lembra de colocar seu ip
	while(connect(c_c,(SOCKADDR*)&sock,sizeof(sock))==SOCKET_ERROR)
		printf("Erro ao se conectar\n");
	system ("cls");
	printf("conectado\n\n");
}

void conectar_online ()
{	
	if(WSAStartup(MAKEWORD(1,1),&data)==SOCKET_ERROR)
	{
		printf("Erro ao inicializar o c_c");
		getch();
		exit(1);
	}
	if((c_c = socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR)
	{
		printf("Erro ao criar socket");
		getch();
		exit(1);
	}
	HOSTENT *host;
	host = gethostbyname("forrestchat.ddns.net");
	if(host!=0)
		memcpy(&sock.sin_addr.s_addr,host->h_addr,host->h_length);
	else
		exit(1);	
	sock.sin_family=AF_INET;
	sock.sin_port=htons(port);
	while(connect(c_c,(SOCKADDR*)&sock,sizeof(sock))==SOCKET_ERROR)
	{
		printf("Nome do Host: %s\n",inet_ntoa(*(in_addr*)host->h_addr));
		printf("Erro ao se conectar\n");
	}
	system ("cls");
	printf("\tConectado ao ForrestChat!\n\n");
}

main()
{
	system("mode con:cols=61 lines=20");
	char nome[30],mensagem1[100],mensagem[100];
	printf ("Digite seu nome:");
	fflush (stdin);
	gets(nome);
	strcpy (mensagem1,nome);
	strcat (mensagem1,":");
	strcpy (mensagem,mensagem1);
	//conectar_rede();
	conectar_online();
	receber = CreateThread (0,0,msg,0,0,&id);
	while(true)
	{
		char auxiliar[100];
		strcpy (mensagem,mensagem1);
		memset(cone,0,sizeof(cone));
		printf ("->");
		int x = 0;
		char letra;
		fflush(stdin);
		while ((letra = getche()) != '\r')
		{
			if ((letra == 8 || x > 60) && x>0)
			{
				fflush (stdin);
				auxiliar[x] = ' ';
				cone[x] = '\0';
				x--;
				printf (" \b");
			}
			if ((letra == 8 || x > 60) && x<=0)
				printf (" ");
			if (letra != 8)
			{
				fflush (stdin);
				auxiliar[x] = letra;
				cone[x] = letra;
				x++;
			}
		}
		auxiliar[x] = '\0';
		printf ("\r                                                            \r");
		strcat (mensagem, auxiliar);
		fflush (stdin);
		send(c_c,mensagem,strlen(mensagem),0);
	}
	getch();
	closesocket(c_c);
	WSACleanup();
	return 0;
}
