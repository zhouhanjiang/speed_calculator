////////////////////////////////////////
// file: speed_calculator.h
// author: XTao<vertextao@hotmail.com>
// date: 2016-07-25
////////////////////////////////////////

#ifndef __SPEED_CALCULATOR_H__
#define __SPEED_CALCULATOR_H__

typedef struct speed_calculator
{
	unsigned long sc_last_update_time;
	unsigned long sc_slot[2];
	unsigned long long sc_total_bytes;
} speed_calculator_t;
void speed_calculator_init(speed_calculator_t* p_calc);
void speed_calculator_update(speed_calculator_t* p_calc, unsigned long bytes);
unsigned long speed_calculator_get_speed(speed_calculator_t* p_calc);
unsigned long long speed_calculator_get_total_bytes(speed_calculator_t* p_calc);

#endif // !__SPEED_CALCULATOR_H__
