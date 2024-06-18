
#include <stdio.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <unistd.h>
#include <limits.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_params
{
	void *mlx;
	mlx_image_t *img;
} t_params;

/*
to be passed to mlx_loop_hook to update the image
*/
void draw(void *param)
{
	t_params *params = (t_params *)param;

}

/*
PPM format. as in wiki:
P3 means the colors are in ascii, and the first two numbers are 
the width and height of the image. Then RGB triplets follow
By convention, each of the red/green/blue components are represented 
internally by real-valued variables that range from 0.0 to 1.0. 
These must be scaled to integer values between 0 and 255 before 
we print them out. 
*/
void create_ppm_image(char *filename, int width, int height)
{
	int image_width = width;
	int image_height = height;

	// render
	char filepath[PATH_MAX];
	sprintf(filepath, "assets/%s", filename);
	FILE *file = fopen(filepath, "w");
	fprintf(file, "P3\n%d %d\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; j++) 
	{
		for (int i = 0; i < image_width; i++)
		{
			float r = (float)i / (image_width - 1);
			float g = (float)j / (image_height - 1);
			float b = 0.0;

			int ir = (int)(255.999 * r);
			int ig = (int)(255.999 * g);
			int ib = (int)(255.999 * b);

			fprintf(file, "%d %d %d\n", ir, ig, ib);
		}
	}
}



int main(int argc, char **argv)
{
	t_params params;

    printf("hello world!");
	create_ppm_image("test.ppm", WIDTH, HEIGHT);


	params.mlx = mlx_init(WIDTH, HEIGHT, "in a weekend!", true);
	params.img = mlx_new_image(params.mlx, WIDTH, HEIGHT);

	if (mlx_image_to_window(params.mlx, params.img, 30, 30) == -1)
	{
		write(2, "mlx_image_to_window failed\n", 27);
		return (1);
	}



	mlx_loop(params.mlx);
}
