#ifndef __OLED_Hardware_H
#define __OLED_Hardware_H

void OLED_Init_H(void);
void OLED_Clear_H(void);
void OLED_ShowChar_H(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString_H(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum_H(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum_H(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum_H(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum_H(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif
