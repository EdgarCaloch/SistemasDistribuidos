#include <Socket_Servidor.h>
#include <Socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int contadorDigitos(int numero)
{
  int cociente, divisor, contador;
  cociente = 0;
  divisor = 1;
  contador = 0;

  if(numero<1)
  {
  	 printf("\nNumero invalido.");
  	 return 0;
  }
  else
  {
  	 while (cociente !=1)
	  {
	    contador++;
	    divisor = divisor * 10;
	    cociente = numero / divisor;
	
	    if (cociente == 1)
	      return contador+1;
	    
	    if (cociente < 1)
		    return contador;
	
	    if (numero < 10)
	        return 1;
	  }
  }

return 0;
}


int main ()
{
	int Socket_Servidor;
	int Socket_Cliente;
    int Aux,numero=1;
    int Longitud_Cadena=0;
	char Cadena[100];

	Socket_Servidor = Abre_Socket_Inet ("cpp_java");
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket servidor\n");
		exit (-1);
	}

	Socket_Cliente = Acepta_Conexion_Cliente (Socket_Servidor);
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket de cliente\n");
		exit (-1);
	}

	
	while(numero!=0)
	{

	    //Inicio proceso lectura de mensaje.
	    Lee_Socket (Socket_Cliente, (char *)&Aux, sizeof(Longitud_Cadena));

	    Longitud_Cadena = ntohl(Aux);

		Lee_Socket (Socket_Cliente, Cadena, Longitud_Cadena);
	    printf ("\nServidor C: Recibido %s\n", Cadena);

		numero=atoi(Cadena);
		char numeroCadena[100];
		sprintf(numeroCadena,"%d",++numero);

		//Inicio preparacion de mensaje.
	    Longitud_Cadena = contadorDigitos(numero)+1;

		//Inicio proceso escritura de mensaje.
	    Aux = htonl (Longitud_Cadena);

	    Escribe_Socket (Socket_Cliente, (char *)&Aux, sizeof(Longitud_Cadena));

	    Escribe_Socket (Socket_Cliente, numeroCadena, Longitud_Cadena);
	    printf ("Servidor C: Enviado %d\n", numero);
	}


	close (Socket_Cliente);
	close (Socket_Servidor);
}

