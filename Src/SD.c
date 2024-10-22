/*
 * SD.c
 *
 *  Created on: Oct 15, 2024
 *      Author: diego
 */
#include "SD.h"
#include "fatfs_sd.h"
#include "fatfs.h"
#include "string.h"
#include "stdio.h"



#define MAX_FILE_SIZE 100000  // Tamaño máximo
#define MAX_LINE_LENGTH 1024

FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t totalSpace, freeSpace;

void sd_operation(const char* filename, unsigned char contenido[], size_t tamaño){
	HAL_Delay(500); // Retardo para estabilización
	char buffer[MAX_LINE_LENGTH];
	char* token;



	 // 1. Montar SD
	fres = f_mount(&fs, "/", 0);
	if (fres == FR_OK) {
		//transmit_uart("Micro SD card is mounted successfully!\r\n");
	} else {
		//transmit_uart("Micro SD card's mount error!\r\n");
		return; // Salir si no se puede montar la tarjeta
	}
	 // 2. Abrir archivo
	fres = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE | FA_READ);
	if (fres == FR_OK) {
		//transmit_uart("File opened for reading.\r\n");
	} else {
		//transmit_uart("File was not opened for reading!\r\n");
		f_mount(NULL, "", 1); // Desmontar SD en caso de error
		return;
	}

	// 3. Leer el archivo

	//contenido[0] = NULL;  // Inicializa el arreglo vacío
	tamaño = 0;

	while (f_gets(buffer, sizeof(buffer), &fil)!= NULL) {
		// Incrementar el contador de líneas por cada línea leída
		 // Extraer los números separados por comas
		 token = strtok(buffer, ",");
		 while (token != NULL){



			 // Convertir el token a un número de 8 bits (unsigned char) y almacenarlo
			 unsigned char numero = atoi(token);  // Convertir a entero
			 (contenido)[tamaño] = numero;
			 (tamaño)++;
			  // Leer el siguiente número
			 token = strtok(NULL, ",");
		 }
		 //*tamano = indice;  // Actualiza el tamaño real del arreglo

	}

	// 4. Cerrar archivo
	fres = f_close(&fil);
	if (fres == FR_OK) {
		//transmit_uart("The file is closed.\r\n");
	} else {
		//transmit_uart("The file was not closed.\r\n");
	}
	// 6. Desmontar SD
	f_mount(NULL, "", 1);
	if (fres == FR_OK) {
		//transmit_uart("The Micro SD card is unmounted!\r\n");
	} else {
		//transmit_uart("The Micro SD was not unmounted!\r\n");
	}
}


