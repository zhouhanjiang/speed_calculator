////////////////////////////////////////
// file: speed_calculator.c
// author: XTao<vertextao@hotmail.com>
// date: 2016-07-25
////////////////////////////////////////

#include "speed_calculator.h"
#include <time.h>

void speed_calculator_init(speed_calculator_t* p_calc)
{
	p_calc->sc_last_update_time = 0;
	p_calc->sc_slot[0] = 0;
	p_calc->sc_slot[1] = 0;
	p_calc->sc_total_bytes = 0;
}

void speed_calculator_update(speed_calculator_t* p_calc, unsigned long bytes)
{
	// unsigned long current = (unsigned long)(clock() / CLOCKS_PER_SEC);
	unsigned long current = (unsigned long)time(NULL);
	unsigned long idx = current & 0x1;
	if (current - p_calc->sc_last_update_time > 0) p_calc->sc_slot[idx] = 0;
	p_calc->sc_slot[idx] += bytes;
	p_calc->sc_total_bytes += bytes;
	p_calc->sc_last_update_time = current;
}

unsigned long speed_calculator_get_speed(speed_calculator_t* p_calc)
{
	// unsigned long current = (unsigned long)(clock() / CLOCKS_PER_SEC);
	unsigned long current = (unsigned long)time(NULL);
	unsigned long idx = current & 0x1;
	if (current - p_calc->sc_last_update_time > 1)
		return 0;
	else
		return p_calc->sc_slot[idx ^ 0x1];
}

unsigned long long speed_calculator_get_total_bytes(speed_calculator_t* p_calc)
{
	return p_calc->sc_total_bytes;
}

#if 1 /////// test code ////////

#ifdef _WIN32
#include <Windows.h>
#define sc_sleep(millisecond) Sleep(millisecond)
#elif __GNUC__
#include <unistd.h>
#define sc_sleep(millisecond) usleep( (millisecond)*1000)
#else
#error NOT SUPPORT
#endif
#include <stdio.h>
#include <stdlib.h>
int main()
{
	speed_calculator_t calc;
	speed_calculator_init(&calc);
	srand((unsigned int)time(NULL));
	int i = 0;
	for (; i < 100; ++i)
	{
		sc_sleep(100);

		// random number [80000, 100000)
		unsigned long bytes = 80000 + rand() % 20000;

		speed_calculator_update(&calc, bytes);
		if (i % 15 == 0)
		{
			unsigned long speed = speed_calculator_get_speed(&calc);
			printf("speed: %lu\n", speed);
		}
	}

	sc_sleep(1000);
	unsigned long speed = speed_calculator_get_speed(&calc);
	printf("idle 1s, speed: %lu\n", speed);

	sc_sleep(1000);
	speed = speed_calculator_get_speed(&calc);
	printf("idle 2s, speed: %lu\n", speed);

	unsigned long long total_bytes = speed_calculator_get_total_bytes(&calc);
	printf("total bytes: %llu\n", total_bytes);

	getchar();
}

#endif
