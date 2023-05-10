// Example sine lut generator

#include <stdio.h>
#include <math.h>

#define M_PI_ 3.1415926535f
#define SIN_SIZE 512
#define SIN_FP 12

int main()
{
	FILE *fp= fopen("sinlut.c", "w");

	fprintf(fp, "//\n// Sine lut; %d entries, LUT of 16bit values in 4.%d format.\n//\n\n", SIN_SIZE, SIN_FP);
	fprintf(fp, "const short sin_lut[%d] = \n{", SIN_SIZE);

	unsigned short hw;
	int i;

	for(i=0; i<SIN_SIZE; i++)
	{
		hw = (unsigned short)(sin(i * 2 * M_PI_ / SIN_SIZE) * (1 << SIN_FP));

		if(i % 8 == 0)
		{
			fputs("\n\t", fp);
		}

		// 2023/05/09 fixed. i==128 is cos(0). hw:0xffff -> 0x1000.
		if(i == 128)
		{
			hw = 0x1000;
		}

		fprintf(fp, "0x%04X, ", hw);
	}
	fputs("\n};\n", fp);

	fclose(fp);

	return 0;
}