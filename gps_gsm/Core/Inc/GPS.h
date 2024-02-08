/*
 * GPS.h
 *
 *  Created on: 03-Feb-2024
 *      Author: DELL
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

typedef struct gpsdata
{
	double time;
	//char time[8];
	float latitude;
	float longitude;
	double Knots;
	char Date[9];
	char N_OR_S;
	char E_OR_W;
	int fix;
	char Data[750];
	char buffer[100];
	char particular_flag_data[100];
}gpsdata;
int get_gps_data();
int gpsData(gpsdata* );
void gps_data_extraction(gpsdata* );

#endif /* INC_GPS_H_ */
