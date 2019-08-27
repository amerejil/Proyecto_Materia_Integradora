/*
 Name:    Control_LEDs_RGB.ino
 Created: 26/07/2019 23:54:28
 Author:  amere
*/

#define piso_derecho 1
#define coral_rojo 2
#define coral_naranja 3
#define piso_izquierdo 4
#define algas 5
#define alga_central 6
#define alga_izquierda 7
#define delfin_derecho 8
#define delfin_izquierda 9
#define alga_derecha 10
#define UP 0
#define DOWN 1

#define blanco 1
#define amarillo 2
#define cafe 3
#define rojo 4
#define verde 5
#define cian 6
#define magenta 7
#define azul 8


// constants for min and max PWM
const int minPWM = 0;
const int maxPWM = 255;
int cont_ = random(1, 8);
// State Variable for Fade Direction

byte fadeDirection1 = UP;
byte fadeDirection2 = UP;
// Global Fade Value
// but be bigger than byte and signed, for rollover


int fadeValue1;
int fadeValue2;
// How smooth to fade?
int fadeIncrement = 2;
int fadeIncrement1 = 5;
int fadeIncrement2 = 5;

// millis() timing Variable, just for fading

unsigned long previousFadeMillis1;
unsigned long previousFadeMillis2;

// How fast to increment?
double tiempo_color = 1.5;
double fadeInterval1 = 75;
double fadeInterval2 = 120;
void setup() {
	pinMode(22, OUTPUT);
	pinMode(23, OUTPUT);
	pinMode(24, OUTPUT);
	pinMode(25, OUTPUT);
	pinMode(26, OUTPUT);
	pinMode(27, OUTPUT);
	pinMode(28, OUTPUT);
	pinMode(29, OUTPUT);
	pinMode(30, OUTPUT);
	pinMode(31, OUTPUT);
	pinMode(32, OUTPUT);
	pinMode(33, OUTPUT);
	pinMode(34, OUTPUT);
	pinMode(36, OUTPUT);
	pinMode(38, OUTPUT);
	pinMode(44,OUTPUT);
	pinMode(45, OUTPUT);
	pinMode(46,OUTPUT);
	Serial.begin(9600);
	// put pwmLED into known state (off)
	color_blanco(1, 0);
	color_blanco(2, 0);
	color_blanco(3, 0);
	color_blanco(4, 0);
	color_blanco(5, 0);
	//color_amarillo(5, 0);

}
class Desvanecimiento
{
	int puerto;
	int incremento;
	double tiempo;
	byte direccion = UP;
	int intensidad;
	int contador;
	unsigned long previousFadeMillis;
	int cnt = 0;
	double intervalo;

public:
	Desvanecimiento(int puerto_, int incremento_, double tiempo_, int intensidad_, unsigned long previousFadeMillis_, int cont)
	{
		puerto = puerto_;
		incremento = incremento_;
		tiempo = tiempo_;
		intensidad = intensidad_;
		previousFadeMillis = previousFadeMillis_;
		contador = cont;

	}
	int doTheFade(unsigned long thisMillis, int colores_permitidos[10]) {
		int colores[10] = { blanco,amarillo, cafe, rojo, verde, cian, magenta, azul };
		int cont_color = 0;
		for (int j = 0; j <= 9;j++)
		{
			if (colores_permitidos[j] != 0)
			{
				cont_color++;
				
			}
		}
		if (cont_color == 0)
		{
			cont_color = 8;
		}
		
		intervalo = (500 * incremento * tiempo) / 255;
		
		if (thisMillis - previousFadeMillis >= intervalo) {
			if (cnt == 9)
			{
				cnt = 0;
			}
			if (direccion == UP) {
				intensidad = intensidad + incremento;


				if (intensidad >= maxPWM) {

					intensidad = maxPWM;
					direccion = DOWN;
					if (cont_color == 8)
					{
						
						selector_de_color(colores[contador - 1], puerto, intensidad);
					}
					else
					{
						selector_de_color(colores_permitidos[contador - 1], puerto, intensidad);
					}
					
				}
				else
				{
					if (cont_color == 8)
					{
						
						selector_de_color(colores[contador - 1], puerto, intensidad);
					}
					else
					selector_de_color(colores_permitidos[contador - 1], puerto, intensidad);
				}
			}
			else {
				intensidad = intensidad - incremento;
				

				if (intensidad <= minPWM) {
					// At min, limit and change direction
					intensidad = minPWM;
					direccion = UP;
					cnt++;
					contador = random(1, cont_color);
					//Serial.println(contador);
					if (cont_color == 8)
					{
						
						selector_de_color(colores[contador - 1], puerto, intensidad);
					}
					else
					selector_de_color(colores_permitidos[contador - 1], puerto, intensidad);
					

				}
				else
				{
					if (cont_color == 8)
					{
						
						selector_de_color(colores[contador - 1], puerto, intensidad);
					}
					else
					selector_de_color(colores_permitidos[contador - 1], puerto, intensidad);
				}

			}

			previousFadeMillis = thisMillis;

		}
		if (cnt == 9)
		{
			selector_de_color(contador, puerto, 0);
			return(true);
		}

		else
			return(false);
	}
	//}
};
Desvanecimiento Coral_Naranja(coral_naranja, fadeIncrement, tiempo_color, 0, 0, cont_);
Desvanecimiento Coral_Rojo(coral_rojo, fadeIncrement, tiempo_color, 0, 0, random(1, 8));
Desvanecimiento Piso_Derecho(piso_derecho, fadeIncrement, tiempo_color, 0, 0, random(1, 8));
Desvanecimiento Piso_Izquierdo(piso_izquierdo, fadeIncrement, tiempo_color, 0, 0, random(1, 8));
Desvanecimiento Algas(algas, fadeIncrement, tiempo_color, 0, 0, random(1, 8));

void encender_led(byte puerto_R, byte puerto_G, byte puerto_B, int intensidad_R, int intensidad_G, int intensidad_B)
{
	bool digital_R, digital_G, digital_B;
	if (intensidad_R == 255)
	{
		digital_R = 1;
	}
	else
	{
		digital_R = 0;
	}
	if (intensidad_G == 255)
	{
		digital_G = 1;
	}
	else
	{
		digital_G = 0;
	}
	if (intensidad_B == 255)
	{
		digital_B = 1;
	}
	else
	{
		digital_B = 0;
	}
	
	if (puerto_R <= 13 || puerto_R>=44)
	{
		analogWrite(puerto_R, intensidad_R);
		analogWrite(puerto_G, intensidad_G);
		analogWrite(puerto_B, intensidad_B);
		Serial.println(puerto_G);
	}

	else {
		digitalWrite(puerto_R, digital_R);
		digitalWrite(puerto_G, digital_G);
		digitalWrite(puerto_B, digital_B);
	}

}
void color_amarillo(int puerto, int intensidad_amarillo)
{
	switch (puerto)
	{
	case 1:
		encender_led(2, 3, 4, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 2:
		encender_led(5, 6, 7, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 3:
		encender_led(8, 9, 10, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 4:
		encender_led(11, 12, 13, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 5:
		encender_led(44, 45, 46, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 6:
		encender_led(22, 24, 26, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 7:
		encender_led(23, 25, 27, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 8:
		encender_led(28, 30, 32, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 9:
		encender_led(29, 31, 33, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	case 10:
		encender_led(34, 36, 38, intensidad_amarillo, intensidad_amarillo, 0);
		break;
	}

}
void color_rojo(int puerto, int intensidad_rojo)
{
	switch (puerto)
	{
	case 1:
		encender_led(2, 3, 4, intensidad_rojo, 0, 0);
		break;
	case 2:
		encender_led(5, 6, 7, intensidad_rojo, 0, 0);
		break;
	case 3:
		encender_led(8, 9, 10, intensidad_rojo, 0, 0);
		break;
	case 4:
		encender_led(11, 12, 13, intensidad_rojo, 0, 0);
		break;
	case 5:
		encender_led(44, 45, 46, intensidad_rojo, 0, 0);
		break;
	case 6:
		encender_led(22, 24, 26, intensidad_rojo, 0, 0);
		break;
	case 7:
		encender_led(23, 25, 27, intensidad_rojo, 0, 0);
		break;
	case 8:
		encender_led(28, 30, 32, intensidad_rojo, 0, 0);
		break;
	case 9:
		encender_led(29, 31, 33, intensidad_rojo, 0, 0);
		break;
	case 10:
		encender_led(34, 36, 38, intensidad_rojo, 0, 0);
	}

}
void color_verde(int puerto, int intensidad_verde)
{
	switch (puerto)
	{
	case 1:
		encender_led(2, 3, 4, 0, intensidad_verde, 0);
		break;
	case 2:
		encender_led(5, 6, 7, 0, intensidad_verde, 0);
		break;
	case 3:
		encender_led(8, 9, 10, 0, intensidad_verde, 0);
		break;
	case 4:
		encender_led(11, 12, 13, 0, intensidad_verde, 0);
		break;
	case 5:
		encender_led(44, 45, 46, 0, intensidad_verde, 0);
		break;
	case 6:
		encender_led(22, 24, 26, 0, intensidad_verde, 0);
		break;
	case 7:
		encender_led(23, 25, 27, 0, intensidad_verde, 0);
		break;
	case 8:
		encender_led(28, 30, 32, 0, intensidad_verde, 0);
		break;
	case 9:
		encender_led(29, 31, 33, 0, intensidad_verde, 0);
		break;
	case 10:
		encender_led(34, 36, 38, 0, intensidad_verde, 0);
	
	}
}
void color_azul(int puerto, int intensidad_azul)
{
	switch (puerto)
	{
	case 1:
		encender_led(2, 3, 4, 0, 0, intensidad_azul);
		break;
	case 2:
		encender_led(5, 6, 7, 0, 0, intensidad_azul);
		break;
	case 3:
		encender_led(8, 9, 10, 0, 0, intensidad_azul);
		break;
	case 4:
		encender_led(11, 12, 13, 0, 0, intensidad_azul);
		break;
	case 5:
		encender_led(44, 45, 46, 0, 0, intensidad_azul);
		break;
	case 6:
		encender_led(22, 24, 26, 0, 0, intensidad_azul);
		break;
	case 7:
		encender_led(23, 25, 27, 0, 0, intensidad_azul);
		break;
	case 8:
		encender_led(28, 30, 32, 0, 0, intensidad_azul);
		break;
	case 9:
		encender_led(29, 31, 33, 0, 0, intensidad_azul);
		break;
	case 10:
		encender_led(34, 36, 38, 0, 0, intensidad_azul);
		break;
	}
}
void color_blanco(int puerto, int intensidad_blanco)
{
	switch (puerto)
	{
	case 1:
		encender_led(2, 3, 4, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 2:
		encender_led(5, 6, 7, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 3:
		encender_led(8, 9, 10, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 4:
		encender_led(11, 12, 13, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 5:
		encender_led(44, 45, 46, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 6:
		encender_led(22, 24, 26, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 7:
		encender_led(23, 25, 27, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 8:
		encender_led(28, 30, 32, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 9:
		encender_led(29, 31, 33, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	case 10:
		encender_led(34, 36, 38, intensidad_blanco, intensidad_blanco, intensidad_blanco);
		break;
	}
}
void color_magenta(int puerto, int intensidad_magenta)
{
	switch (puerto)
	{
	case 1:
		encender_led(2, 3, 4, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 2:
		encender_led(5, 6, 7, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 3:
		encender_led(8, 9, 10, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 4:
		encender_led(11, 12, 13, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 5:
		encender_led(44, 45, 46, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 6:
		encender_led(22, 24, 26, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 7:
		encender_led(23, 25, 27, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 8:
		encender_led(28, 30, 32, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 9:
		encender_led(29, 31, 33, intensidad_magenta, 0, intensidad_magenta);
		break;
	case 10:
		encender_led(34, 36, 38, intensidad_magenta, 0, intensidad_magenta);
		break;
	}
}
void color_cian(int puerto, int intensidad_cian)
{
	switch (puerto)
	{
	case 1:
		encender_led(2, 3, 4, 0, intensidad_cian, intensidad_cian);
		break;
	case 2:
		encender_led(5, 6, 7, 0, intensidad_cian, intensidad_cian);
		break;
	case 3:
		encender_led(8, 9, 10, 0, intensidad_cian, intensidad_cian);
		break;
	case 4:
		encender_led(11, 12, 13, 0, intensidad_cian, intensidad_cian);
		break;
	case 5:
		encender_led(44, 45, 46, 0, intensidad_cian, intensidad_cian);
		break;
	case 6:
		encender_led(22, 24, 26, 0, intensidad_cian, intensidad_cian);
		break;
	case 7:
		encender_led(23, 25, 27, 0, intensidad_cian, intensidad_cian);
		break;
	case 8:
		encender_led(28, 30, 32, 0, intensidad_cian, intensidad_cian);
		break;
	case 9:
		encender_led(29, 31, 33, 0, intensidad_cian, intensidad_cian);
		break;
	case 10:
		encender_led(34, 36, 38, 0, intensidad_cian, intensidad_cian);
		break;
	}
}
void color_cafe(int puerto, float intensidad_cafe)
{
	switch (puerto)
	{
	case 1:
		encender_led(2, 3, 4, 100 * (intensidad_cafe / 255), 20 * (intensidad_cafe / 255), 0);
		break;
	case 2:
		encender_led(5, 6, 7, 100 * (intensidad_cafe / 255), 20 * (intensidad_cafe / 255), 0);
		break;
	case 3:
		encender_led(8, 9, 10, 100 * (intensidad_cafe / 255), 20 * (intensidad_cafe / 255), 0);
		break;
	case 4:
		encender_led(11, 12, 13, 100 * (intensidad_cafe / 255), 20 * (intensidad_cafe / 255), 0);
		break;
	}
}
void selector_de_color(int color, int puerto, int intensidad)
{
	switch (color)
	{
	case rojo:
		color_rojo(puerto, intensidad);
		break;
	case verde:
		color_verde(puerto, intensidad);
		break;
	case azul:
		color_azul(puerto, intensidad);
		break;
	case magenta:
		color_magenta(puerto, intensidad);
		break;
	case blanco:
		color_blanco(puerto, intensidad);
		break;
	case amarillo:
		color_amarillo(puerto, intensidad);
		break;
	case cian:
		color_cian(puerto, intensidad);
		break;
	case cafe:
		color_cafe(puerto, intensidad);
		break;
	}
}
void matrix_secuencia_on_off_(double tiempo, int color[10], int puertos[10])
{
	int cont = 0;
	for (int j = 0; j <= 9;j++)
	{
		if (puertos[j] != 0)
		{
			cont++;
		}

	}
	for (int i = 0; i < cont;i++)
	{
		selector_de_color(color[i], puertos[i], 255);
		delay(tiempo * 1000);
		selector_de_color(rojo, puertos[i], 0);
	}

}
void matrix_secuencia_on_off_hold(double tiempo, int color[10], int puertos[10])
{
	int cont = 0;
	for (int j = 0; j <= 9;j++)
	{
		if (puertos[j] != 0)
		{
			cont++;
		}

	}
	for (int i = 0; i < cont;i++)
	{
		selector_de_color(color[i], puertos[i], 255);
		delay(tiempo * 1000);

	}
	//delay(10000);
	for (int i = 0; i < cont;i++)
	{
		selector_de_color(rojo, puertos[i], 0);
		//delay(tiempo * 1000);

	}
}
void matrix_secuencia_on(double tiempo, int puertos[10], int color[10]) 
{
	int cont = 0;
	for (int k = 0; k <= 9;k++)
	{
		if (puertos[k] != 0)
		{
			cont++;
			//Serial.println(cont);
		}

	}
	for (int j = 0;j < cont;j++)
	{
		
			selector_de_color(color[j], puertos[j], 255);
			
		
	}
	for (int i = 0; i < cont;i++)
	{
		selector_de_color(rojo, puertos[i], 0);
		//delay(tiempo * 1000);

	}
	//delay(1000 * (tiempo ));
}
void matrix_secuencia_on_off_cambio_color(double tiempo, int puertos[10], int color[10])
{
	int cont = 0;
	for (int k = 0; k <= 9;k++)
	{
		if (puertos[k] != 0)
		{
			cont++;
		}

	}
	for (int j = 0;j < cont;j++)
	{
		for (int i = 1;i <= 6;i++)
		{
			selector_de_color(i, puertos[j], 255);
			delay(1000 * (tiempo / 7));
		}
		selector_de_color(color[j], puertos[j], 255);
	}
	for (int i = 0; i < cont;i++)
	{
		selector_de_color(rojo, puertos[i], 0);
		//delay(tiempo * 1000);

	}

}
void matrix_secuencia_cambio_color(double tiempo, int puertos[10], int color[10])
{
	int cont = 0;
	for (int k = 0; k <= 9;k++)
	{
		if (puertos[k] != 0)
		{
			cont++;
		}

	}
	for (int j = 0;j < cont;j++)
	{
		for (int i = 1;i <= 6;i++)
		{
			selector_de_color(i, puertos[j], 255);
			//delay(1000 * (tiempo / 7));
		}
		selector_de_color(color[j], puertos[j], 255);
	}
	for (int i = 0; i < cont;i++)
	{
		selector_de_color(rojo, puertos[i], 0);
		//delay(tiempo * 1000);

	}

}
void loop() {
	static int flag = 0;

	unsigned long currentMillis = millis();
	unsigned long currentMillis1 = millis();
	unsigned long currentMillis2 = millis();
	unsigned long currentMillis3 = millis();
	unsigned long currentMillis4 = millis();
	pinMode(22,INPUT);
	pinMode(23, INPUT);
	pinMode(24, INPUT);
	pinMode(25, INPUT);
	pinMode(26, INPUT);
	pinMode(27, INPUT);
	pinMode(34, INPUT);
	pinMode(36, INPUT);
	pinMode(38, INPUT);
	//int color_pwm[10] = { blanco,blanco,cafe,rojo,verde, magenta,magenta };
	//int puertos_pwm[10] = { piso_izquierdo,piso_derecho,coral_naranja, coral_rojo,algas,delfin_derecho,delfin_izquierda };

	int color[10] = { blanco,blanco,cafe,rojo,verde, verde, verde, magenta,magenta };
	int color_[10] = { blanco,blanco,cafe,rojo,verde, verde, verde, magenta,magenta };
	int puertos[10] = { piso_izquierdo,piso_derecho,coral_naranja, coral_rojo,alga_izquierda,alga_central,alga_derecha,delfin_derecho,delfin_izquierda };
	int color_piso[10] = { amarillo,cian, magenta };
	int color_delfin_[10] = { amarillo };
	int color_coral[10] = {rojo, cafe, magenta};
	int color_algas[10] = {verde};
	
	

	if (flag == 0) {
	
		
		color_magenta(8, 255);
		color_magenta(9, 255);
		Coral_Naranja.doTheFade(currentMillis, color_coral);
		Piso_Derecho.doTheFade(currentMillis1, color_piso);
		Piso_Izquierdo.doTheFade(currentMillis2, color_piso);
		Algas.doTheFade(currentMillis4,color_algas);
		//Serial.println(Delfin_Izquierdo.doTheFade(currentMillis_));
		if (Coral_Rojo.doTheFade(currentMillis3, color_coral))
		{
			flag = 1;

		}

	}
	if (flag == 1)
	{
		//color_verde(5, 0);
		
		color_magenta(8, 0);
		color_magenta(9, 0);
		pinMode(44, INPUT);
		pinMode(45, INPUT);
		pinMode(46, INPUT);
		pinMode(22, OUTPUT);
		pinMode(23, OUTPUT);
		pinMode(24, OUTPUT);
		pinMode(25, OUTPUT);
		pinMode(26, OUTPUT);
		pinMode(27, OUTPUT);
		pinMode(34, OUTPUT);
		pinMode(36, OUTPUT);
		pinMode(38, OUTPUT);
		
		
		matrix_secuencia_on_off_(0.1, color, puertos);
		matrix_secuencia_on_off_(0.1, color, puertos);
		matrix_secuencia_on_off_(0.3, color, puertos);
		
		matrix_secuencia_on_off_hold(0.5, color, puertos);
		for (int i = 0; i < 80; i++)
		{
			color_blanco(1, 255);
			color_rojo(2, 255);
			color_cafe(3, 255);
			color_blanco(4, 255);
			color_verde(10, 255);
			color_verde(6, 255);
			color_verde(7, 255);
			color_magenta(8, 255);
			color_magenta(9, 255);
			//delay(1);
			/*color_verde(1, 0);
			color_verde(2, 0);
			color_verde(3, 0);

			color_verde(4, 0);

			color_verde(10, 0);
			

			
			color_verde(6, 0);

			color_verde(7, 0);*/

			//color_verde(8, 0);

			//color_verde(9, 0);
			//delay(1);
		}
		
		flag = 0;

	}
	
}