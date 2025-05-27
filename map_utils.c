/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:38:47 by mgering           #+#    #+#             */
/*   Updated: 2024/08/13 15:07:53 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_min_max_map(t_fdf *data)
{
	int	i;
	int	j;
	int	min;
	int	max;
	int	temp_y;

	i = 0;
	min = INT_MAX;
	max = INT_MIN;
	temp_y = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			temp_y = (i + j) / 2 - data->map[i][j];
			if (temp_y > max)
				max = temp_y;
			if (temp_y < min)
				min = temp_y;
			j++;
		}
		i++;
	}
	set_scale(min, max, data);
}

void	set_scale(int min, int max, t_fdf *data)
{
	int	diff_y;
	int	diff_x;
	int	scale;
	int	margin_x;
	int	margin_y;

	scale = 1;
	diff_y = abs(min - max);
	diff_x = abs(data->height + data->width);
	margin_x = (WIDTH * 8 / 10);
	margin_y = (HEIGHT * 8 / 10);
	while (((scale + 1) * diff_y) < margin_y
		&& ((scale + 1) * diff_x) < margin_x)
		scale++;
	data->scale = scale;
	data->offset_y = (HEIGHT - (max * scale))
		- ((HEIGHT - (diff_y * scale)) / 2);
	data->offset_x = (WIDTH / 2) + ((diff_x / 2) * scale)
		- ((diff_x - data->height) * scale);
}
