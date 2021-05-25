#include"tm4c123gh6pm.h"
#include"math.h" 
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>


#define PI 3.142857

 void GPS_Init()
 {
	 
 }
 void Recieve_GPS()
 {
 
 }
 
 void readGPS();
 void get_distance(double arr[]);
 
 double arr[4];
 int K = 0;
 
 int main(void)
{
	
	while (1)
	{
	 readGPS();
		if (K == 4)
		{
			get_distance(arr);
			K = 2;
			arr[0] = arr[2];
			arr[1] = arr[3];
		}
	}
}



void readGPS()
{
	char c0, GPSValues[100],SaveValue[100], GPSlatitude[10], GPSlongitudeResult[10], GPSparseValue[12][20], *token;
	double latitude = 0.0, longitude = 0.0 , latitudeResult = 0.0,longitudeResult = 0.0, deg , min , sec;
	int index = 0, degrees, i = 0, j = 0;

	// *****************get $GPRMC,56561 , 5181N , 22333333, *A
	//	  while(!UARTSendByte(UART2_BASE));
	//    c0=UARTRecieveByte(UART2_BASE);
	if (c0 == '$')
	{
		//while(!UARTSendByte(UART2_BASE));
		//   char  c1=UARTRecieveByte(UART2_BASE);
		if (c1 == 'G')
		{
			// while(!UARTSendByte(UART2_BASE));
			//  char c2=UARTRecieveByte(UART2_BASE);
			if (c2 == 'P')
			{
				//	  while(!UARTSendByte(UART2_BASE));
				// char   c3=UARTRecieveByte(UART2_BASE);
				if (c3 == 'R')
				{
					//	  while(!UARTSendByte(UART2_BASE));
				 //  char  c4 = UARTRecieveByte(UART2_BASE);
					if (c4 == 'M')
					{
						//	  while(!UARTSendByte(UART2_BASE));
					   // char   c5 = UARTRecieveByte(UART2_BASE);

						if (c5 == 'C')
						{
							//	  while(!UARTSendByte(UART2_BASE));
						   // char   c6=UARTRecieveByte(UART2_BASE);
							if (c6 == ',')
							{
								//	  while(!UARTSendByte(UART2_BASE));
							   //  char  c7=UARTRecieveByte(UART2_BASE);

								// get values in GPMRC untll *A
								while (c7 != '*')
								{
									GPSValues[index] = c7;
									//	  while(!UARTSendByte(UART2_BASE));
								   // char   c7=UARTRecieveByte(UART2_BASE);
									index++;
								}

								// cut string GPS values put it in SaveValue
								index = 0;
								token = strtok(GPSValues, ",");
								while (token != NULL)
								{
									strcpy(&SaveValue[index], token);
									token = strtok(NULL, ",");
									index++;
								}

								// if SaveValue[1] = "A" Active , or , "V" Void

								if (strcmp(&SaveValue[1], "A") == 0)
								{
									latitude = atof(&SaveValue[2]);
									longitude = atof(&SaveValue[4]);
									
									// global arr for distance
									
									arr[K] = latitude ;
									K++;
									arr[K] = longitude ;
									K++;

									// calculate latitude

									deg = latitude / 100;
									min = latitude - (double)(deg * 100);
									sec = min / 60.00;
									latitudeResult = deg + sec;
									//latitudeResult = result;
								   // sprintf(latitudeResult, "%f", result);

									// calculate longitude

									deg = longitude / 100;
									min = longitude - (double)(deg * 100);
									sec = min / 60.00;
									longitudeResult = deg + sec;
									//longitudeResult = result;
									 //sprintf(longitudeResult, "%f", result);

								}
							}
						}
					}
				}
			}


		}

	}
}
 void get_distance(double arr[])
 {
	 //r_distance set it as gloable value
	 double R, lat1, lon1, lat2, lon2, dlon, dlat, a , c , distance , r_distance;
		 // include math library
		 // approximate radius of earth in km
		 R = 6373.0;

//	 lat1 = radians(52.2296756);
//	 lon1 = radians(21.0122287);
//	 lat2 = radians(latitude);
//	 lon2 = radians(longitude);

	 //lon2 - lon1
	 dlon = (arr[3] - arr[1])*(double)(PI / 180);
	 //lat2 - lat1
	 dlat = (arr[2] - arr[0])*(double)(PI / 180);

	 a = sin((dlat/2) * 2 + cos(lat1) * cos(lat2) * sin(dlon / 2) * 2);
	 c = 2 * atan2(sqrt(a), sqrt(1 - a));

		// phase 1  interrupt = 100m for lamb , phase 2  interrupt = 150m for lamb
	 distance = R * c;
	 // calculate all distance
	 r_distance += distance;

 }
 
	