/*
 * lcd.c
 *
 *  Created on: Dec 19, 2025
 *      Author: CERENSULTANÇETİN
 */

#include "lcd.h"

/* Komut Gönderme Yardımcı Fonksiyonu */
void Lcd_Cmd(uint8_t cmd) {
    // Önce yüksek 4 bit (High nibble)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0); // RS = 0 (Komut)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (cmd >> 4) & 1); // D4
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (cmd >> 5) & 1); // D5
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (cmd >> 6) & 1); // D6
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (cmd >> 7) & 1); // D7

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1); // EN = 1
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0); // EN = 0

    // Sonra düşük 4 bit (Low nibble)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (cmd >> 0) & 1); // D4
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (cmd >> 1) & 1); // D5
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (cmd >> 2) & 1); // D6
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (cmd >> 3) & 1); // D7

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1); // EN = 1
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0); // EN = 0
}

/* Veri (Karakter) Gönderme Yardımcı Fonksiyonu */
void Lcd_Data(uint8_t data) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1); // RS = 1 (Veri)

    // Yüksek 4 bit
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (data >> 4) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (data >> 5) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (data >> 6) & 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (data >> 7) & 1);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);

    // Düşük 4 bit
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (data >> 0) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (data >> 1) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (data >> 2) & 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (data >> 3) & 1);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
}

/* Main.c'de çağırdığın ana fonksiyonlar */
void Lcd_Init(void) {
    HAL_Delay(50);
    Lcd_Cmd(0x02); // 4-bit moduna geçiş
    Lcd_Cmd(0x28); // 2 Satır, 5x8 matris (4x16 için de geçerlidir)
    Lcd_Cmd(0x0C); // Ekran açık, imleç kapalı
    Lcd_Cmd(0x01); // Ekranı temizle
    HAL_Delay(2);
}

void Lcd_Clear(void) {
    Lcd_Cmd(0x01);
    HAL_Delay(2);
}

void Lcd_Cursor(uint8_t row, uint8_t col) {
    uint8_t mask = 0x80;
    if(row == 0) mask = 0x80 + col;
    if(row == 1) mask = 0xC0 + col;
    if(row == 2) mask = 0x94 + col;
    if(row == 3) mask = 0xD4 + col;
    Lcd_Cmd(mask);
}

void Lcd_Send_String(char *str) {
    while(*str) Lcd_Data(*str++);
}
