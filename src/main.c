
#include <stdio.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <unistd.h>

#include "utils.h"


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
	(void)params;
}




int main(int argc, char **argv)
{
	t_params params;
	(void)argc;
	(void)argv;

    printf("hello world!");
	
	// for the book course we create a ppm image
	create_ppm_image("test.ppm", WIDTH, HEIGHT);


	params.mlx = mlx_init(WIDTH, HEIGHT, "in a weekend!", true);
	params.img = mlx_new_image(params.mlx, WIDTH, HEIGHT);

	if (mlx_image_to_window(params.mlx, params.img, 30, 30) == -1)
	{
		write(2, "mlx_image_to_window failed\n", 27);
		return (1);
	}

	mlx_loop_hook(params.mlx, draw, &params);

	mlx_loop(params.mlx);
}
