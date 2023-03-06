#include <stdio.h>
#include <Socket_Cliente.h>
#include <Socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	int Socket_Con_Servidor;
    int Longitud_Cadena = 0;
    int Aux;
	char Cadena[100];

	Socket_Con_Servidor = Abre_Conexion_Inet ("localhost", "cpp_java");
	if (Socket_Con_Servidor == 1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		exit (-1);
	}

	//Inicio proceso para mandar mensaje. 
   strcpy (Cadena, "Hello Peter");
   Longitud_Cadena = 12;

   Aux = htonl (Longitud_Cadena);
   Escribe_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(Longitud_Cadena));

   Escribe_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
   printf ("Cliente C: Enviado %s\n", Cadena);

   
   //Inicio proceso para leer mensaje. 
   Lee_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(int));
   Longitud_Cadena = ntohl (Aux);

   Lee_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
   printf ("Cliente C: Recibido %s\n", Cadena);
   
   close (Socket_Con_Servidor);
}

