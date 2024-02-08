/*
 * INT_Flash.h
 *
 *  Created on: 08-Feb-2024
 *      Author: DELL
 */

#ifndef INC_INT_FLASH_H_
#define INC_INT_FLASH_H_

#include "stm32l4xx_hal.h"

void writeStringToFlash(uint64_t address, const char* str);
void readDataFromFlash(uint64_t address, char* buffer, uint64_t dataSize);
void eraseFlashPage(uint64_t pageAddress);

#endif /* INC_INT_FLASH_H_ */
