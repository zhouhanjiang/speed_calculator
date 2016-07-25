#ifndef __SPEED_CALCULATOR_H__
#define __SPEED_CALCULATOR_H__

struct speed_calculator
{
	unsigned long sc_last_update_time;
	unsigned long sc_slot[2];
	unsigned long long sc_total_bytes;
};
void speed_calculator_init(struct speed_calculator* p_calc);
void speed_calculator_update(struct speed_calculator* p_calc, unsigned long bytes);
unsigned long speed_calculator_get_speed(struct speed_calculator* p_calc);
unsigned long long speed_calculator_get_total_bytes(struct speed_calculator* p_calc);

#endif // !__SPEED_CALCULATOR_H__
