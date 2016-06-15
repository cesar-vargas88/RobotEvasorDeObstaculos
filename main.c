/*
 * main.c
 *
 *  Created on: Jun 10, 2016
 *      Author: cesar
 */

# include <bcm2835.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>

//////////////////////////////////////
//	Señales Sensores Ultrasonicos	//
//////////////////////////////////////

#define UI_ECHO 4
#define UI_TRIG 17
#define UF_ECHO 23
#define UF_TRIG 24
#define UD_ECHO 27
#define UD_TRIG 22

//////////////////////////
//	Señales Motores		//
//////////////////////////

#define MI_IN1 	5
#define MI_IN2 	6
#define MD_IN1 	13
#define MD_IN2 	19

double MedicionDistancia(int Echo, int Trig);

void Adelante();
void Izquierda();

int main(int argc, char **argv)
{
    if(!bcm2835_init())

    	return 1;

	//////////////////////////////////////////////////////////////
	//	Configura ECHO de sensores Ultrasonicos como Salidas	//
	//////////////////////////////////////////////////////////////

	bcm2835_gpio_fsel(UI_ECHO, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(UF_ECHO, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(UD_ECHO, BCM2835_GPIO_FSEL_INPT);

	//////////////////////////////////////////////////////////////
	//	Configura TRIG de sensores Ultrasonicos como Entradas	//
	//////////////////////////////////////////////////////////////

	bcm2835_gpio_fsel(UI_TRIG, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(UF_TRIG, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(UD_TRIG, BCM2835_GPIO_FSEL_OUTP);

	//////////////////////////////////////////////////////////////////////
	//	Configura señales parea el control del puente H como salidas 	//
	//////////////////////////////////////////////////////////////////////

	bcm2835_gpio_fsel(MI_IN1, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(MI_IN2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(MD_IN1, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(MD_IN2, BCM2835_GPIO_FSEL_OUTP);

	while(1)
	{
		if(MedicionDistancia(UI_ECm
			Izquierda();
		else
			Adelante();
	}

    bcm2835_close();

    return 0;
}

double MedicionDistancia(int ECHO, int TRIG)
{
	double U_delta;
	double U_Distancia;
	struct timeval start;
	struct timeval end;

	bcm2835_gpio_write(ECHO, LOW);
	bcm2835_delayMicroseconds(2);
	bcm2835_gpio_write(TRIG, HIGH);
	bcm2835_delayMicroseconds(10);
	bcm2835_gpio_write(TRIG, LOW);

	while (!bcm2835_gpio_lev(ECHO));
		gettimeofday(&start, NULL);
	while (bcm2835_gpio_lev(ECHO));
		gettimeofday(&end, NULL);

	U_delta  = (end.tv_sec  -  start.tv_sec) * 1000.0;  // s to ms
	U_delta += (end.tv_usec - start.tv_usec) / 1000.0;  // us to ms
	U_Distancia = (U_delta * 34.3) / 2;

	//bcm2835_delay(100);

	printf("Distancia: %f cm\n", U_Distancia);
	return U_Distancia;
}

void Adelante()
{
	bcm2835_gpio_write(MI_IN1, HIGH);
	bcm2835_gpio_write(MI_IN2, LOW);
	bcm2835_gpio_write(MD_IN1, LOW);
	bcm2835_gpio_write(MD_IN2, HIGH);
	printf("Adelante\n");
}
void Izquierda()
{
	bcm2835_gpio_write(MI_IN1, HIGH);
	bcm2835_gpio_write(MI_IN2, LOW);
	bcm2835_gpio_write(MD_IN1, HIGH);
	bcm2835_gpio_write(MD_IN2, LOW);
	printf("Izquierda\n");
}
