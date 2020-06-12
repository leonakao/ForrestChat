/*Servidor para CLIENTE 0.0 */

#include <stdio.h> 
#include <conio.h> 
#include <errno.h>
#include <stdlib.h>
#include <winsock.h> 
#include <windows.h>
#include <sys/types.h>
//#include <sys/socket.h>

// Porta que vai aceitar a conexão
#define port 8088

// Limite de usuários conectados
#define LIMITE_MAX 100

void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   //vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   //vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

WSADATA data; 
int c_s[100]; 
SOCKADDR_IN sock; 
u_long modo=1;	
int bytes,n=1;
HANDLE cone,usuario;
DWORD id;
FILE *backup;

void cliente (int x)
{	
	char buffer2[1024];
	for (int a=1; a<n && a!= x; a++)
		send (c_s[a],"\n\tUm novo usuário se conectou ao chat\n",50,0);
	fprintf (backup,"Novo usuário se conectou\n");
	while (true)
	{
		strcpy(buffer2,"");
		memset(buffer2,0,1024);
		int byte = recv(c_s[x],buffer2,1024,0);
		if (byte > 0)
		{
			for (int a=1; a<n; a++)
				send (c_s[a],buffer2,strlen(buffer2),0);
			fprintf (backup,"%s\n",buffer2);
		}
		if (byte == -1)
		{
			for (int a=1; a<n; a++)
				send (c_s[a],"\n\tUm usuario deixou o chat\n",50,0); 
			fprintf(backup,"%s","Um usuario deixou o chat\n");
			printf ("\nUsuário %d se desconectou",c_s[x]);
			break;
		}
		byte = 0;
	}
}

DWORD WINAPI conectar(LPVOID p)
{
	for (int b=1;b < LIMITE_MAX ;b++)
	{
		printf ("\nAguardando...");
		int size = sizeof (sock);
		c_s[b] = accept(c_s[0],(struct sockaddr *) &sock,&size);
		n++;
		printf ("\nUsuario %d Conectado: %d ",b,c_s[b]);
		usuario = CreateThread (0,0,(LPTHREAD_START_ROUTINE)cliente,(LPVOID)b,0,&id);
	}
}

main()
{ 
	system("mode con:cols=20 lines=10");
	textcolor(15);
	backup = fopen ("Mensagens.txt","a");
	if(WSAStartup(MAKEWORD(1,1),&data)==SOCKET_ERROR){ 
		printf("Erro ao inicializar o c_s"); 
		return 0; 
	} 
	if((c_s[0] = socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR){ 
		printf("Erro ao criar socket"); 
		return 0; 
	}
	sock.sin_family=AF_INET; 
	sock.sin_port=htons(port); 
	if(bind(c_s[0],(SOCKADDR*)&sock,sizeof(sock))==SOCKET_ERROR)
	{ 	
		printf("Erro colocar utilizar a funcao BIND"); 
		getch();
		exit(1);
	} 
	listen(c_s[0],LIMITE_MAX);
	cone = CreateThread (0,0,conectar,0,0,&id);
	char sair[5] = "nao";
	while (strcmp (sair,"sair")!=0)
		gets(sair);
	fclose (backup);
	closesocket(c_s[0]);
	WSACleanup();
	return 0;
}
