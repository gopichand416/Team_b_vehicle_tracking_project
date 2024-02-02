/*
 * GSM_imp.c
 *
 *  Created on: Jan 31, 2024
 *      Author: DELL
 */
#include"GSM.h"
#include"main.h"


char *str;
int gsm_connect_to_server()
{
	uint8_t state=0;
	uint8_t substate=0;
	while(1)
	{
	switch(state)
			  	  {
			  	  case 0:
			  	  {
			  		  switch(substate)
			  		  {
			  		  case 0:
			  			 str =send_to_gsm("ATE0\r");
			  			//HAL_Delay(1000);
			  			 printf("ATE0 \n");
			  			//if(strncmp(str,"\r\nOK\r\n",6))
			  			 if((strstr(str,"\r\nOK\r\n")!=NULL))
			  			{
			  				printf("state = %d substate = %d \n",state,substate);
			  				printf("ATE0 OK \n");
			  				  state=1;
			  				substate=0;

			  			  }
			  			  else if(strncmp(str,"\r\nERROR\r\n",6))
			  			  {
			  				printf("state = %d substate = %d \n",state,substate);
			  				printf("ATE0 ERROR \n");
			  				  state=0;
			  				  substate=0;

			  			  }
			  			  break;
			  		  }
			  		  break;
			  		  printf("case 0 state \n");
			  	  }
			  	  case 1:
			  		  switch(substate)
			  		  {
			  		  case 0:
			  			  str =send_to_gsm("AT+CMEE=2\r");
			  			  printf("CMEE=2 \n");
			  			  HAL_Delay(1000);
			  			  if(!(strncmp(str,"\r\nOK\r\n",6)))
			  			  {
			  				printf("state = %d substate = %d \n",state,substate);
			  				printf("CMEE=2 OK \n");
			  				  state=2;
			  				  substate=0;
			  			  }
			  			  else
			  			  {
			  				printf("state = %d substate = %d \n",state,substate);
			  				printf("CMEE=2 OK \n");
			  				  state=0;
			  				  substate=0;

			  			  }
			  			  break;
			  		  }

			  	  case 2:
			  		  switch(substate)
			  		  {
			  		  case 0:
			  			  str = send_to_gsm("AT+CPIN?\r");
			  			//HAL_Delay(1000);
			  			 printf("CPIN \n");
			  			  if((strstr(str,"READY")!=NULL))
			  			  {
			  				printf("state = %d substate = %d \n",state,substate);
			  				printf("CPIN READY \n");
			  			      state=3;
			  			      substate=0;
			  			  }
			  			  else if(!(strncmp(str,"\r\nERROR\r\n",6)))
			  			  {
			  				printf("state = %d substate = %d \n",state,substate);
			  				state=2;
			  				substate=0;
			  			  }
			  			  else
			  			  {
			  				printf("state = %d substate = %d \n",state,substate);
			  	  			state=2;
			 	  			substate=0;
			  			  }
			  			  break;
			  		  }
			  		case 3:
			  			switch(substate)
			  			{
			  			  case 0:
			  				  str =send_to_gsm("AT+CSQ\r");
			  				  //HAL_Delay(1000);
			  				  printf("CAQ \n");
			  				  int e=check_signal(str);
			  				  if((strstr(str,"OK")!=NULL))
			  				  {
			  					  printf("state = %d substate = %d \n",state,substate);
			  					  printf("CAQ OK\n");
			  					  if(e==0)
			  					  {
			  						  printf("signal OK\n");
			  						  state=4;
			  						  substate=0;
			  					  }
			  					  else
			  					  {
			  						  printf("signal NOT OK\n");
			  						  state=3;
			  						  substate=0;
			  					  }
			  				  }
			  				  else
			  				  {
			  					  printf("state = %d substate = %d \n",state,substate);
			  					  state=3;
			  					  substate=4;
			  				  }
			  				  break;
			  			//  case 1:

			  				}
			  			break;
				  	case 4:
				  	{
				  		switch(substate)
				  		{
				  		 case 0:
				  			  str =send_to_gsm("AT+CREG?\r");
				  			  //HAL_Delay(1000);
				  			  printf("CREG? \n");
				  			  if((strstr(str,"0,1"))||(strstr(str,"0,6")||(strstr(str,"1,6"))))
				  			  {
				  				  state=5;
				  				  substate=0;
				  				  printf("match found\n");
				  			  }
				  			  else
				  			  {
				  				  substate=1;
				  			  }
				  			  break;
				  		 case 1:
				  			 if(!(strncmp(str,"\r\nERROR\r\n",6)))
				  			 {
				  				 state=4;
				  				 substate=0;
				  			 }
				  			 else
				  			 {
				  				 state=4;
				  				 substate=0;
				  			 }
				  			 break;
				  		 default:
				  			 break;
				  		}
				  		break;
				  	}

				  	case 5:
				  		switch(substate)
				  		{
				  		case 0:
				  			str = send_to_gsm("AT+CGREG?\r");
				  			if((strstr(str,"0,1"))||(strstr(str,"1,1")))
				  			{
				  				state=6;
				  				substate=0;
				  				printf("match found\n");
				  			}
				  			else
				  			{
				  				substate=1;
				  			}
				  			break;
				  		case 1:
				  			str = send_to_gsm("AT+CGREG=1\r");
				  			if(strstr(str,"OK"))
				  			{
				  				state=5;
				  				substate=0;
				  			}
				  			else
				  			{
				  				state=5;
				  				substate=0;
				  			}
				  			break;
				  		default:
				  			break;
				  		}
				  		break;

				  	case 6:
				  		{
				  			switch(substate)
				  			{
				  			case 0:
				  				str = send_to_gsm("AT+CGDCONT?\r");
				  				//HAL_Delay(1000);
				  				printf("CGDCONT?\n");
				  				if((strstr(str,"OK")!=NULL))
				  				{
				  					printf("state = %d substate = %d \n",state,substate);
				  					state=7;
				  					substate=0;
				  				}
				  				else
				  				{
				  					printf("state = %d substate = %d \n",state,substate);
				  					state=6;
				  					substate=0;
				  				}
				  				break;
				  			}
				  			break;
				  		}
				  		case 7:
				  		{
				  			switch(substate)
				  			{
				  			case 0:
				  				str =send_to_gsm("AT+CGDCONT=1,\"IP\",\"jionet\"\r");
				  				//HAL_Delay(1000);
				  				printf("CGDCONT=1\n");
				  				if(!(strncmp(str,"\r\nOK\r\n",6)))
				  				{
				  					printf("state = %d substate = %d \n",state,substate);
				  					state=8;
				  					substate=0;
				  				}
				  				else
				  				{
				  					printf("state = %d substate = %d \n",state,substate);
				  					state=6;
				  					substate=0;
				  				}
				  			}
				  			break;
				  		}


				  		default:
				  			printf("completed work \n");
				  			return HAL_OK;
			  	  }
	}
}
int check_server_connection()
{
	char *str =send_to_gsm("AT+CIPOPEN?\r");
		char *ptr;
		    ptr=strstr(str,"139.59.78.252");
		    if(ptr)
		    {
		        printf("tcp connection established\n");
		        return 0;
		    }
		    else{
		        printf("tcp connection NOT established\n");
		        return 1;
		    }
}


int gsm_disconnect_to_server()
{
	int cls_state=0;
	//while(1)
	{
	switch(cls_state)
	{
	case 0:
		str =(char *) send_to_gsm("AT+CIPCLOSE\r");
			if(!(strncmp(str,"\r\nOK\r\n",6)))
			{
//				printf("state = %d substate = %d \n",state,substate);
			    return HAL_OK;
			 }
			else
			{
				cls_state=0;
			}
	}
	}
	return -1;


}

int check_signal(char *str)
{
	char *rssi,*ber;
	int i=0;
	while(*(str+i)!='\0')
	{
	    if((str[i-1]==' ')&&(str[i-2]==':'))
	    {
		if((str[i]>='0')||(str[i]<='9'))
		{
			rssi=str+i;
			printf("rssi %c %c\n",*rssi,*(rssi+1));
		}
	    }
	    if(str[i-1]==',')
	    {
	        	if((str[i]>='0')||(str[i]<='9'))
		        {
		        	ber=str+i;
		        	printf("ber %c %c\n",*ber,*(ber+1));
	        	}

	    }
		i++;
	}
	printf("out rssi %c %c\n",*rssi,*(rssi+1));
	printf("out ber %c %c\n",*ber,*(ber+1));
	if((*ber=='9')&&(*(ber+1)=='9'))
	{
	    if(((*rssi>='2')||(*rssi<'9'))&&((*(rssi+1)>='0')||(*(rssi+1)<='9')))
	    {
	    printf("ok");
	    return 0;
	    }
	    else
	    {
	    	return 1;;
	    }
	}
	else
	{
	    return 1;
	}
}

int connect_tcp_server()
{
	int state=0;
	int substate=0;
	int count=30;
	while(count--)
	{
	switch(state)
	{
	case 0:
	{
		switch(substate)
		{
		case 0:
			str=send_to_gsm("AT+CIPMODE?\r");
			if(strstr(str,"+CIPMODE: 0"))
			{
				state=1;
				substate=0;
			}
			else
			{
				substate=1;
			}
			break;
		case 1:
			str=send_to_gsm("AT+CIPMODE=0\r");
			if(strstr(str,"OK"))
			{
				state=0;
				substate=0;
			}
			else
			{
				substate=0;
			}
			break;
		}
		break;
	}
	case 1:
	{
		switch(substate)
		{
		case 0:
			str = send_to_gsm("AT+NETOPEN\r");
			//HAL_Delay(1000);
			printf("NETOPEN\n");
			if(!(strncmp(str,"\r\nOK\r\n",6)))
			{
				printf("state = %d substate = %d \n",state,substate);
				state=2;
				substate=0;
			}
			else
			{
				printf("state = %d substate = %d \n",state,substate);
				substate=1;
			}
			break;
		case 1:
			if((strstr(str,"Network is already opened")!=NULL))
			{
				printf("state = %d substate = %d \n",state,substate);
				state=2;
				substate=0;
			}
			else
			{
				state=0;
				substate=0;
			}
			break;

		}
		break;
	}
	case 2:
	{
		switch(substate)
		{
		case 0:
			str =send_to_gsm("AT+CIPOPEN=0,\"TCP\",\"139.59.78.252\",49791\r");
			//HAL_Delay(1000);
			printf("CIPOPEN\n");
			if((strstr(str,"CIPOPEN: 0,0")!=NULL))
				//if(!(strncmp(str,"\r\n+CIPOPEN: 0,0\r\n",6)))
			{
				printf("state = %d substate = %d \n",state,substate);
				state=3;
				substate=1;
			}
			else
			{
				printf("state = %d substate = %d \n",state,substate);
				//state=0;
				substate=1;
			}
			break;
		case 1:
			if(check_server_connection()==0)
			{
				printf("state = %d substate = %d \n",state,substate);
				state=3;
				substate=0;

			}
			else
			{
				printf("state = %d substate = %d \n",state,substate);
				state=0;
				substate=0;
			}
			break;
		}
		break;
	}
	default:
		printf("opened successfulyy\n");
		return 0;
	}
}
	printf("Time out\n");

	return 1;
}

int check_REG_NETWORK(char *str)
{
	char *n,*stat;
	int i=0;
	while(*(str+i)!='\0')
	{
	    if((str[i-1]==' ')&&(str[i-2]==':'))
	    {
		if((str[i]=='0')||(str[i]<='9'))
		{
			n=str+i;
			printf("n %c\n",*n);
		}
	    }
	    if(str[i-1]==',')
	    {
	        	if((str[i]>='0')||(str[i]<='9'))
		        {
		        	stat=str+i;
		        	printf("stat %c\n",*stat);
	        	}

	    }
		i++;
	}
	printf("out n %c\n",*n);
	printf("out stat %c\n",*stat);
	if((*n=='0')|(*n=='1'))
	{
	    if((*stat=='1')||(*stat=='6'))
	    {
	    printf("ok");
	    return 0;
	    }
	}
	else
	{
	    return 1;
	}
	return -1;
}



