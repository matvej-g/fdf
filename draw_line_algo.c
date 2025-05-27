/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:42:42 by mgering           #+#    #+#             */
/*   Updated: 2024/08/05 17:35:35 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_fdf *data, t_draw draw_var)
{
	int	err2;

	while (draw_var.newp1.x != draw_var.newp2.x
		|| draw_var.newp1.y != draw_var.newp2.y)
	{
		put_pixel_in_window(draw_var.newp1, data);
		err2 = 2 * draw_var.err;
		if (err2 > -draw_var.dy)
		{
			draw_var.err -= draw_var.dy;
			draw_var.newp1.x += draw_var.x_step;
		}
		if (err2 < draw_var.dx)
		{
			draw_var.err += draw_var.dx;
			draw_var.newp1.y += draw_var.y_step;
		}
	}
}

void	draw_setup(t_point p1, t_point p2, t_fdf *data)
{
	t_draw	draw_var;

	setup_calc_var(p1, p2, data, &draw_var);
	draw_line(data, draw_var);
}

void	iterate_map(t_fdf *data)
{
	t_point	p1;
	t_point	p2;

	p1.y = 0;
	while (p1.y < data->height)
	{
		p1.x = 0;
		while (p1.x < data->width)
		{
			p1.z = data->map[(int)p1.y][(int)p1.x];
			if (p1.x + 1 < data->width)
			{
				p2 = (t_point){p1.x + 1, p1.y, data->map[p1.y][p1.x + 1]};
				draw_setup(p1, p2, data);
			}
			if (p1.y + 1 < data->height)
			{
				p2 = (t_point){p1.x, p1.y + 1, data->map[p1.y + 1][p1.x]};
				draw_setup(p1, p2, data);
			}
			p1.x++;
		}
		p1.y++;
	}
}
