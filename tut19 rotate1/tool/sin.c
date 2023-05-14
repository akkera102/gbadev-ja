// Example sine lut generator

#include <stdio.h>
#include <math.h>

#define M_PI_ 3.1415926535f
#define SIN_SIZE 360
#define SIN_FP 8

int main()
{
	FILE *fp= fopen("sinlut.c", "w");


	signed short hw;
	int i;

	fprintf(fp, "const short MathSinTab[%d] = \n{", SIN_SIZE);

	for(i=0; i<SIN_SIZE; i++)
	{
		hw = (signed short)(sin(i * 2 * M_PI_ / SIN_SIZE) * (1 << SIN_FP));

		if(i % 8 == 0)
		{
			fputs("\n\t", fp);
		}

		fprintf(fp, "%d, ", hw);
	}
	fputs("\n};\n\n\n", fp);


	fprintf(fp, "const short MathCosTab[%d] = \n{", SIN_SIZE);

	for(i=0; i<SIN_SIZE; i++)
	{
		hw = (signed short)(cos(i * 2 * M_PI_ / SIN_SIZE) * (1 << SIN_FP));

		if(i % 8 == 0)
		{
			fputs("\n\t", fp);
		}

		fprintf(fp, "%d, ", hw);
	}
	fputs("\n};\n", fp);


	fclose(fp);

	return 0;
}