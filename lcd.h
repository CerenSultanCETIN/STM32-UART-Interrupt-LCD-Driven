/*
 * lcd.h
 *
 *  Created on: Dec 19, 2025
 *      Author: CERENSULTANÇETİN
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f4xx_hal.h"

void Lcd_Init(void);
void Lcd_Send_String(char *str);
void Lcd_Clear(void);
void Lcd_Cursor(uint8_t row, uint8_t col);



#endif /* LCD_H_ */
