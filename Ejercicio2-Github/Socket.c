
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <sys/un.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "Socket.h"


int Lee_Socket (int fd, char *Datos, int Longitud)
{
	int Leido = 0;
	int Aux = 0;


	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;


	while (Leido < Longitud)
	{
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0)
		{

			Leido = Leido + Aux;
		}
		else
		{

			if (Aux == 0) 
				return Leido;
			if (Aux == -1)
			{

				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}


	return Leido;
}


int Escribe_Socket (int fd, char *Datos, int Longitud)
{
	int Escrito = 0;
	int Aux = 0;


	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	while (Escrito < Longitud)
	{
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
		if (Aux > 0)
		{

			Escrito = Escrito + Aux;
		}
		else
		{
	
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}


	return Escrito;
}


int Lee_Socket_Udp (
	int fd, struct sockaddr *Remoto, socklen_t *Longitud_Remoto,
	char *Datos, int Longitud_Datos)
{
	int Leido = 0;
	int Aux = 0;


	if ((fd == -1) || (Datos == NULL) || (Longitud_Datos < 1)
			|| (Remoto == NULL) || (Longitud_Remoto == NULL))
	{
		return -1;
	}

	while (Leido < Longitud_Datos)
	{
		Aux = recvfrom (fd, Datos + Leido, Longitud_Datos - Leido, 0,
			Remoto, Longitud_Remoto);

		if (Aux > 0)
		{

			Leido = Leido + Aux;
		}
		else
		{

			if (Aux == 0) 
				return Leido;
			if (Aux == -1)
			{

				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}


	return Leido;
}


int Escribe_Socket_Udp (int fd, struct sockaddr *Remoto, 
	socklen_t Longitud_Remoto, char *Datos, int Longitud_Datos)
{
	int Escrito = 0;
	int Aux = 0;


	if ((fd == -1) || (Datos == NULL) || (Longitud_Datos < 1) 
			|| (Remoto == NULL) )
   {
		return -1;
   }

	while (Escrito < Longitud_Datos)
	{
		Aux = sendto (fd, Datos + Escrito, Longitud_Datos - Escrito, 0,
			Remoto, Longitud_Remoto);

		if (Aux > 0)
		{
			/*
			* Si hemos conseguido escribir caracteres, se actualiza la
			* variable Escrito
			*/
			Escrito = Escrito + Aux;
		}
		else
		{
			/*
			* Si se ha cerrado el socket, devolvemos el numero de caracteres
			* leidos.
			* Si ha habido error, devolvemos -1
			*/
			if (Aux == 0)
				return Escrito;
			else
         {
				return -1;
         }
		}
	}

	/*
	* Devolvemos el total de caracteres leidos
	*/
	return Escrito;
}


/**
 * Rellena una estructura sockaddr_in con los datos que se le pasan. Esta estrutura es
 * útil para el envio o recepción de mensajes por sockets Udp o para abrir conexiones.
 * Se le pasa el host. Puede ser NULL (para abrir socket servidor Udp o para recepción de
 * mensajes de cualquier host).
 * Se le pasa el servicio. Puede ser NULL (para abrir socket cliente Udp).
 * Se le pasa una estructura sockaddr_in que devolverá rellena.
 * Se le pasa una Longitud. Debe contener el tamaño de la estructura sockaddr_in y
 * devolverá el tamaño de la estructura una vez rellena.
 * Devuelve -1 en caso de error.
 */
int Dame_Direccion_Udp (char *Host, char *Servicio, struct sockaddr_in *Servidor,
   int *Longitud_Servidor)
{
   struct servent *Puerto;
   struct hostent *Maquina;
  
   /* Comprobación de parámetros */
   if (Servidor == NULL) return -1;

   /* Relleno del primer campo de la estructura */
   Servidor->sin_family = AF_INET;

   /* Si nos han pasado un host ... */
   if (Host != NULL)
   {
      /* ... obtenemos la dirección del host y la ponemos en la estructura */
      Maquina = gethostbyname (Host);
      if (Maquina == NULL)
         return -1;

      Servidor->sin_addr.s_addr = ((struct in_addr *)(Maquina->h_addr))->s_addr;
   }
   else
      /* Si no nos han pasado un host, ponemos cualquier host. */
      Servidor->sin_addr.s_addr = INADDR_ANY;

   /* Si servicio en NULL, hacemos que el puerto lo eliga el sistema operativo
    libremente.*/
   if (Servicio == NULL)
      Servidor->sin_port = 0;
   else
   {
      /* Si el servicio no es NULL, lo obtenemos. */
      Puerto = getservbyname (Servicio, "udp");
      if (Puerto == NULL)
         return -1;
      Servidor->sin_port = Puerto->s_port;
   }
}
