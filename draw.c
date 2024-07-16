/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:42:42 by mgering           #+#    #+#             */
/*   Updated: 2024/07/16 19:00:56 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham(int x1, int y1, int x2, int y2, t_fdf *data)
{
	int	dx;
	int	dy;
	int	err;
	int	step_x;
	int	step_y;
	int	z1;
	int	z2;

	z1 = data->map[y1][x1];
	z2 = data->map[y2][x2];


	x1 *= data->scale;
	y1 *= data->scale;
	x2 *= data->scale;
	y2 *= data->scale;
	z1 *= data->scale;
	z2 *= data->scale;

	isometric(&x1, &y1, z1);
	isometric(&x2, &y2, z2);

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	err = dx - dy;
	step_x = step_calc(x1, x2);
	step_y = step_calc(y1, y2);
	while (x1 != x2 || y1 != y2)
	{
		mlx_put_pixel(data->img_ptr, x1 + (WIDTH / 2), y1 + (WIDTH / 2), 0x00FF00FF);
		if (2 * err > -dy)
		{
			err -= dy;
			x1 += step_x;
		}
		if (2 * err < dx)
		{
			err += dx;
			y1 += step_y;
		}
	}
}

int	step_calc(int temp1, int temp2)
{
	if (temp1 < temp2)
		return (1);
	return (-1);
}

void	isometric(int *x, int *y, int z)
{
	int	temp_x;
	int	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = temp_x - temp_y;
	*y = (temp_x + temp_y) / 2 - z;
}

void	draw_lines(t_fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x + 1 < data->width)
				bresenham(x, y, x + 1, y, data);
			if (y + 1 < data->height)
				bresenham(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}
