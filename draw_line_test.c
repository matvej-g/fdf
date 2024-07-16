/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:48:46 by mgering           #+#    #+#             */
/*   Updated: 2024/07/15 18:20:10 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static mlx_image_t	*g_img;

int	step_calc(int temp1, int temp2);

void	bresenham(int *x1, int *y1, int x2, int y2, t_fdf *data)
{
	int	dx;
	int	dy;
	int	err;
	int	step_x;
	int	step_y;
	int z1 = data->map[y1][x1];
	int z2 = data->map[y2][x2];

	dx = abs(x2 - *x1);
	dy = abs(y2 - *y1);
	err = dx - dy;
	step_x = step_calc(*x1, x2);
	step_y = step_calc(*y1, y2);
	while ((*x1 != x2 && *x1 < WIDTH) || (*y1 != y2 && *y1 < HEIGHT))
	{
		mlx_put_pixel(g_img, *x1, *y1, 0x00FF00FF);
		if (2 * err > -dy)
		{
			err -= dy;
			*x1 += step_x;
		}
		if (2 * err < dx)
		{
			err += dx;
			*y1 += step_y;
		}
	}
}

int	step_calc(int temp1, int temp2)
{
	if (temp1 < temp2)
		return (1);
	return (-1);
}


void	hook(void* param, t_fdf *data)
{
	int x1;
	int y1;
	int	x2;
	int y2;

	x1 = 2;
	y1 = 3;
	x2 = 20;
	y2 = 255;
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	bresenham(&x1, &y1, x2 , y2, data);
}

int32_t	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}