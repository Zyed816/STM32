#ifndef __Button_H
#define __Button_H

typedef enum{Pin_11 = 11, Pin_12 = 12} Button_ID;

void Button_Init(void);
uint8_t Button_Read(Button_ID id);

#endif
