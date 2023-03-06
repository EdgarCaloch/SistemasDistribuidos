import java.net.*;
import java.io.*;


public class SocketCliente
 {

     public static void main (String [] args)
     {
         new SocketCliente();
     }
     
  
     public SocketCliente()
     {
         try
         {
             Socket socket = new Socket ("localhost", 4000);
             System.out.println ("conectado");


             socket.setSoLinger (true, 10);

             String numero="1";
             while(Integer.parseInt(numero)!=0)
             {
                 BufferedReader teclado = 
                    new BufferedReader( new InputStreamReader(System.in));
                 System.out.println("\nIngresa un numero: ");
                 numero=teclado.readLine();

                 
                 //Inicio proceso escritura de mensaje.
                 DataOutputStream bufferSalida =
                   new DataOutputStream (socket.getOutputStream());

         
                 DatoSocket aux = new DatoSocket (numero);
                 aux.writeObject (bufferSalida);

                 System.out.println ("Cliente Java: Enviado " + aux.toString());
               

                 //Inicio proceso lectura de mensaje.
                 DataInputStream bufferEntrada =
                    new DataInputStream (socket.getInputStream());
                 

                 DatoSocket dato = new DatoSocket("");
                 dato.readObject(bufferEntrada);
                 System.out.println ("Cliente Java: Recibido " + dato.toString());
             }    



             socket.close();
         }
         catch (Exception e)
         {
             e.printStackTrace();
         }
     }
}
