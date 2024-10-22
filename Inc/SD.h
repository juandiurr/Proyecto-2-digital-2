/*
 * SD.h
 *
 *  Created on: Oct 15, 2024
 *      Author: diego
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include <stdint.h>
#include "main.h"

void sd_operation(const char* filename, unsigned char contenido[], size_t tamaño);

#endif /* INC_SD_H_ */
