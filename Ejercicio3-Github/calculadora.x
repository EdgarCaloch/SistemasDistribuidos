struct numeros{
 int x;
 int y;
};

program calculadora_PROG{
 version calculadora_VERS{
   float suma(numeros) = 1;
   float resta(numeros) = 2;
   float multiplicacion(numeros) = 3;
   float division(numeros) = 4;
 } = 1;
} = 0x31111111;
