# speed_calculator
Simple data transfer speed calculator. Maintain speed in seconds.

# Test sample code
```c
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
	struct speed_calculator calc;
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
```
