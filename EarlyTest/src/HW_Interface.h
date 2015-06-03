
#ifndef _HW_INTERFACE_H
#define _HW_INTERFACE_H




void board_init(void);
void led_control(int color, int blink);
void BSR_write(unsigned int data);
int convert_legs_behavior_to_bsr(int* movement_state);

#endif //_HW_INTERFACE_H