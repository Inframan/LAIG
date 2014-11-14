#include "plane.h"




plane::plane(void)
{
}

plane::plane(int p)
{

	parts = p;
	ctrlpoints = (float***) malloc(parts);

	float coords = 1/parts;

	for(int i = 0; i < parts;i++)
	{
		ctrlpoints[i] = (float**) malloc(parts);
		for(int j = 0;j < parts;j++)
		{
			ctrlpoints[i][j] = (float *) malloc(3);
			ctrlpoints[i][j][0] = i*coords;
			ctrlpoints[i][j][1] = 0;
			ctrlpoints[i][j][2] = j*coords;
		}

	}

	nrmcomponents = (float ***)malloc(parts);
	for(int i = 0; i < parts;i++)
	{
		nrmcomponents[i] = (float**) malloc(parts);
		for(int j = 0;j < parts;j++)
		{
			nrmcomponents[i][j] = (float *) malloc(3);
			nrmcomponents[i][j][0] = 0.0;
			nrmcomponents[i][j][1] = 1.0;
			nrmcomponents[i][j][2] = 0.0;
		}

	}

	for(int i = 0; i < parts;i++)
	{
		texpoints[i] = (float**) malloc(parts);
		for(int j = 0;j < parts;j++)
		{
			texpoints[i][j] = (float *) malloc(3);
			texpoints[i][j][0] = i*coords;
			texpoints[i][j][1] = j*coords;
		}

	}


}


void plane::draw()
{

}

plane::~plane(void)
{
}
