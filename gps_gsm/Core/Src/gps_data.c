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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1)
    {
        // Process the received data
    	//printf("data is %s\n",gps.Data);
//        gpsData(&gps);
    	gps_status = gpsData(&gps);
    }
}

int get_gps_data()
{
//	memset(gps.Data,'\0',sizeof(gps.Data));
//	char b[1000];
//	memset(b,'\0',sizeof(b));
//	char Rx_buff[750];
	HAL_UART_Receive_IT(&huart1,(uint8_t*)gps.Data,750);
	//strcpy(gps.Data,Rx_buff);
	//memset(Rx_buff,'\0',750);
//	HAL_Delay(5000);
		  {
//							printf("%s\n",b);
				printf("received start from MODULE\n");
			    printf("%s\n",gps.Data);
			    printf("received end  from MODULE\n");
			    return 0;
			   // gps_status = gpsData(&gps);
//		 	  		    	gps_output_flag = gpsData(&gps);
//		 	  		    	return gps_output_flag;
		  }
//	else
//	{
//		return 1;
//	}
}

int gpsData(gpsdata* data)
{
	char *current_flag;
	int counter;
	int comma = 0;
	printf("in func\n");
			//HAL_UART_Receive(&GpsData->UartPort,(uint8_t*)GpsData->Data,700,HAL_MAX_DELAY);
	current_flag=strstr(data->Data,"GNGGA");
	//printf("string found\n");
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
		sscanf(data->buffer,"GNGGA,%lf,%f,%c,%f,%c,%d,",&data->time,&data->latitude,&data->N_OR_S,&data->longitude,&data->E_OR_W,&data->fix);
        printf("lat:%f\n",data->latitude);
        printf("lon:%f\n",data->longitude);


		current_flag=strstr(data->Data,"RMC");
			//printf("string found\n");
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
	double Deg_Val=0.0,Min_Val=0.0,Sec_Val=0.0,lon=0.0,lat=0.0;
	int hr,min,sec;
	//int hours, minutes, seconds;

	lon=data->longitude;
	lat=data->latitude;
	if((data->E_OR_W=='E' && data->N_OR_S=='S')||(data->E_OR_W=='W' && data->N_OR_S=='N'))
	{
		Deg_Val=(int)(lon/100);
		Min_Val=(int)(lon-(Deg_Val*100));
		Sec_Val=((lon-(Deg_Val*100))-Min_Val)*100;
		data->longitude=(Deg_Val+(Min_Val*Min_To_Degree)+(Sec_Val*Sec_To_Degree))*-1;
		printf("longitude : %f\n",data->longitude);

		Deg_Val=(int)((lat/100));
		Min_Val=(int)(lat-(Deg_Val*100));
		Sec_Val=((lat-(Deg_Val*100))-Min_Val)*10;
		data->latitude=(Deg_Val+(Min_Val*Min_To_Degree)+(Sec_Val*Sec_To_Degree));
		printf("latitude : %f\n",data->latitude);
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
   	// Adjusting for overflow
   	if (ist_min >= 60) {
   	    ist_hr++;
   	    ist_min -= 60;
   	}

//	        // Format and store in gpsData
//	     sprintf(data->time, "%02d:%02d:%02d", hours, minutes, seconds);
			//sprintf(json_str,"{\"latitude\":%f %c,\n \"longitude\":%f %c,\n \"time\":%s,\nData = %s\n }",data->latitude,data->N_OR_S, data->longitude,data->E_OR_W,data->time,data->Date);

//		sprintf(json_str,"latitude:%f %c,longitude:%f %c,time:%d:%d:%d,Date = %s\n",data->latitude,data->N_OR_S, data->longitude,data->E_OR_W,ist_hr,ist_min,sec,data->Date);
		sprintf(json_str,"\n{\n\"lat\":%f %c,\n \"lon\":%f %c,\n \"time\": %d:%d:%d \n \"Date\" = %s\n }",data->latitude,data->N_OR_S, data->longitude,data->E_OR_W,ist_hr,ist_min,sec,data->Date);
//	     sprintf(json_str,"{\"latitude\":%f %c,\n \"longitude\":%f %c,\n \"time\":\"%lf \" \nData = %s\n }",data->latitude,data->N_OR_S, data->longitude,data->E_OR_W,data->time,data->Date);
	     printf("json format is %s\n",json_str);

}

