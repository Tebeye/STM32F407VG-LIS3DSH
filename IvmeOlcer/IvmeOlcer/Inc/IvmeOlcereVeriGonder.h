/*
 * IvmeOlcereVeriGonder.h
 *
 *  Created on: 4 Mar 2020
 *      Author: Berke
 */

#ifndef IVMEOLCEREVERIGONDER_H_
#define IVMEOLCEREVERIGONDER_H_

void IvmeOlcerVeriOku(SPI_HandleTypeDef* hspi,
					 uint8_t *data,
					 uint8_t addr,
					 uint8_t count)
{

		/* Start SPI transmission */
	   HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_RESET);

		/* Add read bit */
		addr |= 0x80;

		if (count > 1) {
			/* Add autoincrement bit */
			addr |= 0x40;
		}

		/* Send address */
	  	HAL_SPI_Transmit(hspi,&addr,1,50);
		/* Receive data */
	  	HAL_SPI_Receive(hspi, data,1,50);

		/* Stop SPI transmission */
		HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_SET);





}

#endif /* IVMEOLCEREVERIGONDER_H_ */
