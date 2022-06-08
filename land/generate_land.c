#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		printf ("we need 3 arguments : nvx, nvy, gap");
		return 1;
	}

	int nvx =  atoi(argv[1]);
	int nvy = atoi(argv[2]);
	int ecart = atoi(argv[3]);
	FILE *texture = fopen("texture.csv", "w");
	FILE *altitude = fopen("height.csv", "w");
	

	srand(time(NULL));   // Initialization, should only be called once.
	
	int sx = ecart*nvx + 1;
	int sy = ecart*nvy + 1;
	

	float **land = (float**)malloc(sy*sizeof(float*));
	for (int i = 0; i < sy; i++)
		land[i] = (float*)malloc(sx*sizeof(float));
	
	
	for (int i = 0; i < sy; i+=ecart)
		for (int j = 0; j < sx; j+=ecart)
			land[i][j] = rand()%20 - 10;
		
	for (int i = 0; i < sy; i+=ecart)
	{
		for (int j = 0; j < sx-ecart; j+=ecart)
		{
			float to_add = (land[i][j + ecart] - land[i][j]) / ecart;
			for (int k = j + 1; k < j + ecart; k+=1)
				land[i][k] = land[i][k-1] + to_add;
		}
	}
	for (int j = 0; j < sx; j+=1)
	{
		for (int i = 0; i < sy-ecart; i+=ecart)
		{
			float to_add = (land[i + ecart][j] - land[i][j]) / ecart;
			for (int k = i + 1; k < i + ecart; k+=1)
				land[k][j] = land[k-1][j] + to_add;
		}
	}

	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx - 1; j++)
		{
			if (land[i][j] <= 0)
			{
				fprintf (altitude, "0,");	
				fprintf (texture, "0,");
			}
			else if (land[i][j] <= 50)
			{
				fprintf (altitude, "%f,", land[i][j]);
				fprintf (texture, "1,");
			}
			else if (land[i][j] <= 400)
			{
				fprintf (altitude, "%f,", land[i][j]);
				fprintf (texture, "2,");
			}
			else
			{
				fprintf (altitude, "%f,", land[i][j]);
                fprintf (texture, "3,");
			}
		}
		if (land[i][sx] <= 0)
        {   
            fprintf (altitude, "0\n");
            fprintf (texture, "0\n");
        }
        else if (land[i][sx] <= 5)
        {
            fprintf (altitude, "%f\n", land[i][sx]);
            fprintf (texture, "1\n");
        }
        else if (land[i][sx] <= 400)
        {
            fprintf (altitude, "%f\n", land[i][sx]);
            fprintf (texture, "2\n");
        }
        else
        {
            fprintf (altitude, "%f\n", land[i][sx]);
            fprintf (texture, "3\n");
        }
	}
	return 0;
}
