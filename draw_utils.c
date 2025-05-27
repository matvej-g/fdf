/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:41:44 by mgering           #+#    #+#             */
/*   Updated: 2024/08/05 13:59:24 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_in_window(t_point p, t_fdf *data)
{
	if ((p.x + data->offset_x) < WIDTH && (p.y + data->offset_y)
		< HEIGHT && (p.x + data->offset_x) > 0 && (p.y + data->offset_y) > 0)
		mlx_put_pixel(data->img_ptr, p.x + data->offset_x, p.y
			+ data->offset_y, 0xFFFFFFFF);
}

void	setup_calc_var(t_point p1, t_point p2, t_fdf *data, t_draw *draw_var)
{
	draw_var->newp1 = apply_scale(p1, data);
	draw_var->newp2 = apply_scale(p2, data);
	isometric(&draw_var->newp1, &draw_var->newp2);
	draw_var->dx = abs(draw_var->newp2.x - draw_var->newp1.x);
	draw_var->dy = abs(draw_var->newp2.y - draw_var->newp1.y);
	draw_var->err = draw_var->dx - draw_var->dy;
	draw_var->x_step = slope_calc(draw_var->newp1.x, draw_var->newp2.x);
	draw_var->y_step = slope_calc(draw_var->newp1.y, draw_var->newp2.y);
}

int	slope_calc(int temp1, int temp2)
{
	if (temp1 < temp2)
		return (1);
	return (-1);
}

t_point	apply_scale(t_point p, t_fdf *data)
{
	t_point	new_p;

	new_p.x = p.x * data->scale;
	new_p.y = p.y * data->scale;
	new_p.z = p.z * data->scale;
	return (new_p);
}

void	isometric(t_point *p1, t_point *p2)
{
	int	temp_x;
	int	temp_y;
	int	temp2_x;
	int	temp2_y;

	temp_x = p1->x;
	temp_y = p1->y;
	temp2_x = p2->x;
	temp2_y = p2->y;
	p1->x = temp_x - temp_y;
	p1->y = (temp_x + temp_y) / 2 - p1->z;
	p2->x = temp2_x - temp2_y;
	p2->y = (temp2_x + temp2_y) / 2 - p2->z;
}
