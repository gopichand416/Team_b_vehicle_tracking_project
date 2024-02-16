/*
 * gps_data.c
 *
 *  Created on: 03-Feb-2024
 *      Author: DELL
 */
#include"main.h"
#include<string.h>
#include<stdio.h>
#include"GPS.h"


extern UART_HandleTypeDef huart1;

extern char json_str[100];


#define Min_To_Degree  0.01666666667
#define Sec_To_Degree	 0.000277777778
char rx_data[60],*ptr;
int Flag=0;
extern uint8_t flag ;
extern gpsdata gps;
extern int gps_status;
int dd,mm,yy;
/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1)
    {
        // Process the received data
    	//printf("data is %s\n",gps.Data);
//        gpsData(&gps);
    	gps_status = gpsData(&gps);
    }
}*/
void gps_callback(UART_HandleTypeDef *huart)
{
	printf("gps_callback called \n");
	 if (huart == &huart1)
	 {
	gps_status = gpsData(&gps);
	 }
}
int get_gps_data()
{
//	memset(gps.Data,'\0',sizeof(gps.Data));
//	char b[1000];
//	memset(b,'\0',sizeof(b));
//	char Rx_buff[750];
//	HAL_UART_Receive(&huart1,(uint8_t*)gps.Data,750,5000);
	int i=HAL_UART_Receive_IT(&huart1,(uint8_t*)gps.Data,750);
	//strcpy(gps.Data,Rx_buff);
	//memset(Rx_buff,'\0',750);
//	HAL_Delay(5000);
		 if(i==0) {
				printf("status : %d\n",i);
				printf("received start from MODULE\n");
			    printf("%s\n",gps.Data);
			    printf("received end  from MODULE\n");
			    gps_status = gpsData(&gps);
			    return 0;
			   // gps_status = gpsData(&gps);
//		 	  		    	gps_output_flag = gpsData(&gps);
//		 	  		    	return gps_output_flag;
		  }
	else
	{
		printf("received NOT from MODULE\n");
		return 1;
	}
}

int gpsData(gpsdata* data)
{
	char *current_flag;
	int counter;
	int comma = 0;
	printf("in func\n");
	current_flag=strstr(data->Data,"GNGGA");
	if(*current_flag=='G')
	{
		counter=0;
		while(*(current_flag+counter)!='*')
		{
			data->particular_flag_data[counter]=*(current_flag+counter);
			counter++;
		}
	    printf(" string is %s", data->particular_flag_data);
		sprintf(data->buffer,"%s",data->particular_flag_data);
		sscanf(data->buffer,"GNGGA,%lf,%lf,%c,%lf,%c,%d,",&data->time,&data->latitude,&data->N_OR_S,&data->longitude,&data->E_OR_W,&data->fix);

		current_flag=strstr(data->Data,"RMC");
		if(*current_flag=='R')
		{
			printf("\nrmc ->%d\n",*current_flag);
			counter=0;

				while(comma < 9) {
					if(*(current_flag + counter) == ',')
						comma++;
					counter++;
					if(comma == 9)
						break;

				}

					for(int i=counter; i < counter+7; i++)
					data->Date[i-counter]= *(current_flag+i);
		}


		if(data->fix==1||data->fix==2||data->fix==6)
		{
			printf("valid fix\n");
			gps_data_extraction(data);
			return 0;

		}
		else
		{
			printf("invalid signal no fix\n");
			data->fix=0;
			return 1;
		}
	 }
	else
	{
		printf("no data\n");
		return 1;
	}
	return 1;
}
void gps_data_extraction(gpsdata* data)
{
	double Deg_Val=0.0,Sec_Val=0.0,lon=0.0,lat=0.0;
	int hr,min,sec;
	lon=data->longitude;
	lat=data->latitude;
	if((data->E_OR_W=='E' || data->N_OR_S=='S')||(data->E_OR_W=='W' || data->N_OR_S=='N'))
	{
		// Extract degrees and seconds directly
		Deg_Val = (int)(lon/100); // Extract degrees
		Sec_Val = fmod(lon, 100); // Extract remaining seconds
		lon= Deg_Val + Sec_Val / 60.0; // Convert seconds to minutes
		data->longitude=lon;

		Deg_Val = (int)(lat/100);
		Sec_Val = fmod(lat, 100);
		lat = Deg_Val + Sec_Val / 60.0;
		data->latitude=lat;
	}
	hr=(int)((data->time)/10000);
	min=(int)(data->time-(hr*10000))/100;
	sec=(int)(data->time-((hr*10000)+(min*100)));
	int ist_hr = hr + 5;  // 5 hours difference
	int ist_min = min + 30;  // 30 minutes difference
	if(ist_hr>=24)
	{
		ist_hr-=24;
	}
	if (ist_min >= 60)
	{
		ist_hr++;
		ist_min -= 60;
	}

	sprintf(json_str,"$ %lf %c,%lf %c, %02d:%02d:%02d, %c%c/%c%c/%c%c#\n",data->latitude,data->N_OR_S, data->longitude,data->E_OR_W,ist_hr,ist_min,sec,data->Date[0],data->Date[1],data->Date[2],data->Date[3],data->Date[4],data->Date[5]);
}
