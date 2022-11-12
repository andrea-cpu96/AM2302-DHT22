/*
 * am2302.c
 *
 *  Created on: Nov 11, 2022
 *      Author: andre
 */

#include <stdint.h>

#include "systemfunctions.h"
#include "ports.h"
#include "projectconf.h"

#include "onewire.h"

#include "am2302.h"

uint32_t timeElapsed;


void am2302_Read(uint8_t *dataBuff)
{

	start();

	while(Get_Port_Pin_State(DATA_PORT, DATA_PIN)); // Sensor pull down

	while(!(Get_Port_Pin_State(DATA_PORT, DATA_PIN))); // Sensor pull up

	// Sensor sends data

	while(Get_Port_Pin_State(DATA_PORT, DATA_PIN)); // Sensor pull down to start sending data

	int i = 39;

	for( ; i >= 0 ; i--)
	{

		while(!(Get_Port_Pin_State(DATA_PORT, DATA_PIN))); // Sensor pull up for data

		timeElapsed = Get_SystemTimeUs();

		while(Get_Port_Pin_State(DATA_PORT, DATA_PIN)); // Sensor pull down

		dataBuff[i] = (Compare_SystemTimeUs(timeElapsed) < 5) ? 0 : 1;

	}

}
