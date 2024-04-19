/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_rect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:48:46 by mgering           #+#    #+#             */
/*   Updated: 2024/04/19 19:36:51 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#define WIDTH 256
#define HEIGHT 256

static mlx_image_t	*g_img;

void	hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	for (int x = 0; x < 32; x++)
		for(int y= 0; y < 32; y++)
			mlx_put_pixel(g_img, x, y, 0x00FF00FF);
	for (int x = 0; x < 32; x++)
		for(int y= 32; y < 64; y++)
			mlx_put_pixel(g_img, x, y, 0xFF0000FF);
	for (int x = 0; x < 32; x++)
		for(int y= 64; y < 96; y++)
			mlx_put_pixel(g_img, x, y, 0x0000FFFF);
}

int32_t	main(void)
{
	mlx_t*    mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 256, 256);
	mlx_image_to_window(mlx, g_img, 112, 80);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}