/*
 * GSM_imp.c
 *
 *  Created on: Jan 31, 2024
 *      Author: DELL
 */
#include"GSM.h"
#include"main.h"

uint8_t state=0;
uint8_t substate=0;
char *str;
int gsm_connect_to_server()
{


		  switch(state)
		  	  {
		  	  case 0:
		  	  {
		  		  switch(substate)
		  		  {
		  		  case 0:
		  			 str = send_to_gsm("ATE0\r");
		  			HAL_Delay(1000);
		  			if(strncmp(str,"\r\nOK\r\n",6))
		  			{
		  				  substate=1;
		  				  printf("state = %d substate = %d \n",state,substate);
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=1;
		  				  substate=0;

		  			  }
		  			  break;
		  		  case 1:
		  			  if(strncmp(str,"\r\nERROR\r\n",6))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			  	  state=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			  	  state=0;
		  			  }
		  			  break;

		  		  }
		  	  }
		  	  case 1:
		  		  switch(substate)
		  		  {
		  		  case 0:
		  			  str = send_to_gsm("AT+CMEE=2\r");
		  			HAL_Delay(1000);
		  			  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=2;
		  				  substate=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=0;

		  			  }
		  			  break;
		  		  }

		  	  case 2:
		  		  switch(substate)
		  		  {
		  		  case 0:
		  			  str = send_to_gsm("AT+CGACT=1,1\r");
		  			HAL_Delay(1000);
		  			  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			      state=3;
		  			      substate=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			  	  substate=1;
		  			  }
		  			  break;
		  		  case 1:
		  			  if(!(strncmp(str,"\r\nERROR\r\n",6)))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=2;
		  				  substate=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			      substate=2;
		  			  }
		  			  break;
		  		  case 2:
		  			printf("state = %d substate = %d \n",state,substate);
		  			state=2;
		  			substate=0;
		  			  break;
		  			  //cme error
		  		  }

		  	  case 3:
		  		  switch(substate)
		  		  {
		  		  case 0:
		  			  str = send_to_gsm("AT+CGDCONT=?\r");
		  			HAL_Delay(1000);
		  			  if((strstr(str,"OK")!=NULL))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			       state=4;
		  			       substate=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=2;
		  				  substate=0;
		  			  }
		  		  }
		  		  break;

		  	  case 4:
		  		  	switch(substate)
		  		  		  {
		  		  		  case 0:
		  		  			  str = send_to_gsm("AT+CGDCONT=1,\"IP\",\"jionet\"\r");
		  		  			HAL_Delay(1000);
		  		  			  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  			       state=5;
		  		  			       substate=0;
		  		  			  }
		  		  			  else
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  				  state=4;
		  		  				  substate=0;
		  		  			  }
		  		  		  }
		  		  	break;

		  	  case 5:
		  		  switch(substate)
		  		  {
		  		  case 0:
		  		  	str = send_to_gsm("AT+CGREG=1\r");
		  		  HAL_Delay(1000);
		  		  	if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  	{
		  		  		printf("state = %d substate = %d \n",state,substate);
		  		  		state=6;
		  		  	    substate=0;
		  		  	  }

		  		  else
		  		  {
		  			printf("state = %d substate = %d \n",state,substate);
		  			  state=5;
		  			  substate=0;
		  		  }
		  		  }
		  		  break;

		  		  case 6:
		  		  		  switch(substate)
		  		  		  {
		  		  		  case 0:
		  		  			  str = send_to_gsm("AT+CGATT=1\r");
		  		  			  HAL_Delay(1000);
		  		  			  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  			       state=7;
		  		  			       substate=0;
		  		  			  }
		  		  			  else
		  		  			  {
		  		  				substate=1;
		  		  			  }
		  		  			break;
		  		  		case 1:
		  		  			 if(!(strncmp(str,"\r\nERROR\r\n",6)))
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  			  state=0;
		  		  			  substate=0;
		  		  			  }
		  		  			  else
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  			      substate=2;
		  		  			  }
		  		  			  break;
		  		  		case 2:
		  		  			state=0;
		  		  			substate=0;
		  		  			  break;
		  		  						  //cme error
		  		  			}

		  		  case 7:
		  		  		switch(substate)
		  		  		  {
		  		  			case 0:
		  		  				  str = send_to_gsm("AT+NETOPEN\r");
		  		  				HAL_Delay(1000);
		  		  				  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  				  {
		  		  					printf("state = %d substate = %d \n",state,substate);
		  		 			       state=8;
		  		 			       substate=0;
		  		  					  }
		  		  					else
		  		 	  			  {
		  		  						printf("state = %d substate = %d \n",state,substate);
					  				  substate=1;
					  			  }
		  		  					  break;
	  		  				  case 1:
		  		  					if(!(strncmp(str,"\r\n+IP ERROR: Network is already opened\r\n",6)))
		  		  					{
		  		  						printf("state = %d substate = %d \n",state,substate);
		  		  						state=8;
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

		  		  case 8:
		  		  		switch(substate)
		  		  		{
		  		  		case 0:
		  		  			 str = send_to_gsm("AT+CIPCCFG=2\r");
		  		  			HAL_Delay(1000);
		  		  			if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  			{
		  		  			printf("state = %d substate = %d \n",state,substate);
		  		  				  state=9;
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
		  		  case 9:
		  		  	  switch(substate)
		  		  	  {
		  		  	  case 0:
		  		  		  str = send_to_gsm("AT+CIPRXGET=1\r");
		  		  		HAL_Delay(1000);
		  		  		  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  		  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  		       state=10;
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
		  		  	case 10:
		  		  		  switch(substate)
		  		  		  {
		  		  			  case 0:
		  		  			  str = send_to_gsm("AT+CIPOPEN=0,\"TCP\",\"139.59.78.252\",49791\r");
		  		  			HAL_Delay(1000);
		  		  			  if(!(strncmp(str,"\r\n+CIPOPEN: 0,0\r\n",6)))
		  		  			  {
		  		  					printf("state = %d substate = %d \n",state,substate);
		  		  			       state=13;
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
		  		  	case 11:
		  		  	  		switch(substate)
		  		  	 		  {
		  		  			  case 0:
		  		  				  str = send_to_gsm("AT+CIPSEND=0,4\r");
		  		  				HAL_Delay(1000);
		  		  		  		 if(!(strstr(str,"\r\nOK\r\n")))
		  		  		  		  {
		  		  	 		  			printf("state = %d substate = %d \n",state,substate);
		  		  		  		      state=12;
		  		  		  		     substate=0;
		  		  	  			  }
		  		  	  			  break;
		  		  	  		  }
		  		  	  		 break;
		  		  /*	case 12:
		  		  			  switch(substate)
		  		  			  {
		  		  				  case 0:
		  		  						  str = send_to_gsm("DATA\r");
		  		  						HAL_Delay(1000);
		  		  						  if(!(strstr(str,"\r\nOK\r\n")))
		  		  						  {
		  		  								printf("state = %d substate = %d \n",state,substate);
		  		  							     state=13;
		  		  							     substate=0;
		  		  							 }
		  		  							 break;
		  		  				}
		  		  				 break;
		  		  	case 13:
		  		  			  switch(substate)
		  		  				  {
		  		  					  case 0:
		  		  						  str = send_to_gsm("AT+CIPCLOSE\r");
		  		  						  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  						  {
		  		  									printf("state = %d substate = %d \n",state,substate);
		  		  							       state=14;
		  		  							     substate=0;
		  		  							  }
		  		  						HAL_Delay(1000);
		  		  						  break;
		  		  					  }
		  		  				  break;*/
		  		  	 case 12:
		  		  		 	 HAL_Delay(1000);
		  		  			  printf("complete\n");
		  		  			  //state=0;
		  		  			  //substate=0;
		  		  			  break;


	  }
}

int gsm_disconnect_to_server()
{
	int cls_state=0;
	while(1)
	{
	switch(cls_state)
	{
	case 0:
		str = send_to_gsm("AT+CIPCLOSE\r");
			if(!(strncmp(str,"\r\nOK\r\n",6)))
			{
				printf("state = %d substate = %d \n",state,substate);
			    return HAL_OK;
			 }
			else
			{
				cls_state=0;
			}
	}
	}

}

switch(state)
		  	  {
		  	  case 0:
		  	  {
		  		  switch(substate)
		  		  {
		  		  case 0:
		  			 str = send_to_gsm("ATE0\r");
		  			//HAL_Delay(1000);
		  			 printf("ATE0 \n");
		  			if(strncmp(str,"\r\nOK\r\n",6))
		  			{
		  				printf("state = %d substate = %d \n",state,substate);
		  				  substate=1;

		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=1;
		  				  substate=0;

		  			  }
		  			  break;
		  		  case 1:
		  			  if(strncmp(str,"\r\nERROR\r\n",6))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			  	  state=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			  	  state=0;
		  			  }
		  			  break;

		  		  }
		  	  }
		  	  case 1:
		  		  switch(substate)
		  		  {
		  		  case 0:
		  			  str = send_to_gsm("AT+CMEE=2\r");
		  			 printf("CMEE=2 \n");
		  			//HAL_Delay(1000);
		  			  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=2;
		  				  substate=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=0;

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
		  			      state=3;
		  			      substate=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			  	  substate=1;
		  			  }
		  			  break;
		  		  case 1:
		  			  if(!(strncmp(str,"\r\nERROR\r\n",6)))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=2;
		  				  substate=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			      substate=2;
		  			  }
		  			  break;
		  		  case 2:
		  			printf("state = %d substate = %d \n",state,substate);
		  			state=2;
		  			substate=0;
		  			  break;
		  			  //cme error
		  		  }

		  	  case 3:
		  		  switch(substate)
		  		  {
		  		  case 0:
		  			  str = send_to_gsm("AT+CGDCONT=?\r");
		  			//HAL_Delay(1000);
		  			 printf("CGDCONT?\n");
		  			  if((strstr(str,"OK")!=NULL))
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  			       state=4;
		  			       substate=0;
		  			  }
		  			  else
		  			  {
		  				printf("state = %d substate = %d \n",state,substate);
		  				  state=2;
		  				  substate=0;
		  			  }
		  		  }
		  		  break;

		  		 case 4:
		  				  		  switch(substate)
		  				  		  {
		  				  		  case 0:
		  				  		  	str = send_to_gsm("AT+CGREG=1\r");
		  				  		 // HAL_Delay(1000);
		  				  		 printf("CGRE=1 \n");
		  				  		  	if(!(strncmp(str,"\r\nOK\r\n",6)))
		  				  		  	{
		  				  		  		printf("state = %d substate = %d \n",state,substate);
		  				  		  		state=5;
		  				  		  	    substate=0;
		  				  		  	  }

		  				  		  else
		  				  		  {
		  				  			printf("state = %d substate = %d \n",state,substate);
		  				  			  state=4;
		  				  			  substate=0;
		  				  		  }
		  				  		  }
		  				  		  break;
		  	  case 5:
		  		  	switch(substate)
		  		  		  {
		  		  		  case 0:
		  		  			  str = send_to_gsm("AT+CGDCONT=1,\"IP\",\"jionet\"\r");
		  		  			//HAL_Delay(1000);
		  		  			printf("CGDCONT=1\n");
		  		  			  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  			       state=7;
		  		  			       substate=0;
		  		  			  }
		  		  			  else
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  				  state=5;
		  		  				  substate=0;
		  		  			  }
		  		  		  }
		  		  	break;



		  		/*  case 6:
		  		  		  switch(substate)
		  		  		  {
		  		  		  case 0:
		  		  			  str = send_to_gsm("AT+CGATT=1\r");
		  		  			  HAL_Delay(1000);
		  		  			  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  			       state=7;
		  		  			       substate=0;
		  		  			  }
		  		  			  else
		  		  			  {
		  		  				substate=1;
		  		  			  }
		  		  			break;
		  		  		case 1:
		  		  			 if(!(strncmp(str,"\r\nERROR\r\n",6)))
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  			  state=0;
		  		  			  substate=0;
		  		  			  }
		  		  			  else
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  			      substate=2;
		  		  			  }
		  		  			  break;
		  		  		case 2:
		  		  			state=0;
		  		  			substate=0;
		  		  			  break;
		  		  						  //cme error
		  		  			}
*/
		  		case 7:
		  				  		  		switch(substate)
		  				  		  		{
		  				  		  		case 0:
		  				  		  			 str = send_to_gsm("AT+CIPMODE=0\r");
		  				  		  			//HAL_Delay(1000);
		  				  		  		 printf("CIPMODE=0 \n");
		  				  		  			if(!(strncmp(str,"\r\nOK\r\n",6)))
		  				  		  			{
		  				  		  			printf("state = %d substate = %d \n",state,substate);
		  				  		  				  state=8;
		  				  		  			 }
		  				  		  			else
		  				  		  			{
		  				  		  			printf("state = %d substate = %d \n",state,substate);
		  				  		  				state=8;
		  				  		  				substate=0;
		  				  		  			}
		  				  		  			break;
		  				  		  		 }
		  				  		  		break;
		  		  case 8:
		  		  		switch(substate)
		  		  		  {
		  		  			case 0:
		  		  				  str = send_to_gsm("AT+NETOPEN\r");
		  		  				//HAL_Delay(1000);
		  		  				 printf("NETOPEN\n");
		  		  				  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  				  {
		  		  					printf("state = %d substate = %d \n",state,substate);
		  		 			       state=9;
		  		 			       substate=0;
		  		  					  }
		  		  					else
		  		 	  			  {
		  		  						printf("state = %d substate = %d \n",state,substate);
					  				  substate=1;
					  			  }
		  		  					  break;
	  		  				  case 1:
		  		  					if(!(strncmp(str,"\r\n+IP ERROR: Network is already opened\r\n",6)))
		  		  					{
		  		  						printf("state = %d substate = %d \n",state,substate);
		  		  						state=9;
		  		  						substate=0;
		  		  					}
		  		  					else
		  		  					{
		  		  						state=8;
		  		  						substate=0;
		  		  					}
		  		  					break;

		  		  				}
		  		  				  break;


		  		  case 9:
		  		  	  switch(substate)
		  		  	  {
		  		  	  case 0:
		  		  		  str = send_to_gsm("AT+CIPRXGET=1\r");
		  		  		//HAL_Delay(1000);
		  		  		  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  		  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  		       state=10;
		  		  		     substate=0;
		  		  		  }
		  		  		else
		  		  		  {
		  		  			printf("state = %d substate = %d \n",state,substate);
		  		  		  state=9;
		  		  		  substate=0;
		  		  		  }
		  		  		  break;
		  		  		  }
		  		  		  break;
		  		  	case 10:
		  		  		  switch(substate)
		  		  		  {
		  		  			  case 0:
		  		  			  str = send_to_gsm("AT+CIPOPEN=0,\"TCP\",\"139.59.78.252\",49791\r");
		  		  			//HAL_Delay(1000);
		  		  			 printf("CIPOPEN\n");
		  		  			  if(!(strncmp(str,"\r\n+CIPOPEN: 0,0\r\n",6)))
		  		  			  {
		  		  					printf("state = %d substate = %d \n",state,substate);
		  		  			       state=13;
		  		  			     substate=0;
		  		  			  }
		  		  			else
		  		  			  {
		  		  				printf("state = %d substate = %d \n",state,substate);
		  		  				  state=8;
		  		  				  substate=0;
		  		  			  }
		  		  			  break;
		  		  			  }
		  		  			  break;
		  		  	case 11:
		  		  	  		switch(substate)
		  		  	 		  {
		  		  			  case 0:
		  		  				  str = send_to_gsm("AT+CIPSEND=0,4\r");
		  		  				HAL_Delay(1000);
		  		  		  		 if(!(strstr(str,"\r\nOK\r\n")))
		  		  		  		  {
		  		  	 		  			printf("state = %d substate = %d \n",state,substate);
		  		  		  		      state=12;
		  		  		  		     substate=0;
		  		  	  			  }
		  		  	  			  break;
		  		  	  		  }
		  		  	  		 break;
		  		  /*	case 12:
		  		  			  switch(substate)
		  		  			  {
		  		  				  case 0:
		  		  						  str = send_to_gsm("DATA\r");
		  		  						HAL_Delay(1000);
		  		  						  if(!(strstr(str,"\r\nOK\r\n")))
		  		  						  {
		  		  								printf("state = %d substate = %d \n",state,substate);
		  		  							     state=13;
		  		  							     substate=0;
		  		  							 }
		  		  							 break;
		  		  				}
		  		  				 break;
		  		  	case 13:
		  		  			  switch(substate)
		  		  				  {
		  		  					  case 0:
		  		  						  str = send_to_gsm("AT+CIPCLOSE\r");
		  		  						  if(!(strncmp(str,"\r\nOK\r\n",6)))
		  		  						  {
		  		  									printf("state = %d substate = %d \n",state,substate);
		  		  							       state=14;
		  		  							     substate=0;
		  		  							  }
		  		  						HAL_Delay(1000);
		  		  						  break;
		  		  					  }
		  		  				  break;*/
		  		  	 case 12:
		  		  		 	 HAL_Delay(1000);
		  		  			  printf("complete\n");
		  		  			  //state=0;
		  		  			  //substate=0;
		  		  			  return 0;
		  		  			  break;
