/*
 * GSM.h
 *
 *  Created on: Jan 31, 2024
 *      Author: DELL
 */
#include<stdio.h>
#include<string.h>
#include "main.h"
#ifndef SRC_GSM_H_
#define SRC_GSM_H_



int check_signal(char *);
int check_REG_NETWORK(char *);
int check_server_connection();
int connect_tcp_server();
int gsm_init();
int gsm_disconnect_to_server();
char* send_to_gsm(char *);
int send_mesg_to_server(char *,int );
int my_check_server();
int check_signal_quality();
int get_gsm_init();
void gsm_actual_server();
char *send_to_gsm(char *);
int send_mesg_to_server(char *,int );


#endif /* SRC_GSM_H_ */
