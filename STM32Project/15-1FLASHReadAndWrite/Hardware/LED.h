#ifndef __LED_H
#define __LED_H

typedef enum{Pin_1 = 1, Pin_2 = 2} LED_ID;

void LED_Init(void);
void LED_On(LED_ID id);
void LED_Off(LED_ID id);
void LED_Switch(LED_ID id);

#endif
