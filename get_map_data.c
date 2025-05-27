/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:39:01 by mgering           #+#    #+#             */
/*   Updated: 2024/08/13 14:44:49 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_width(char *line)
{
	int		width;
	char	**split_line;

	width = 0;
	split_line = ft_split(line, ' ');
	if (split_line)
	{
		while (split_line[width])
		{
			free(split_line[width]);
			width++;
		}
		free(split_line);
	}
	return (width);
}

void	get_height_width(t_fdf *data, char *fdf_file)
{
	char	*line;
	int		height;
	int		fd;

	height = 0;
	fd = open(fdf_file, O_RDONLY);
	line = get_next_line(fd);
	data->width = get_width(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		height++;
	}
	close(fd);
	data->height = height;
}

void	fill_data_row(int	*altitude, char *line)
{
	int		i;
	int		val;
	char	**values;

	i = 0;
	values = ft_split(line, ' ');
	while (values[i])
	{
		val = ft_atoi(values[i]);
		altitude[i] = val;
		free(values[i]);
		i++;
	}
	free(values);
}

void	fill_map_data(char *fdf_file, t_fdf *data)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	get_height_width(data, fdf_file);
	data->map = (int **)malloc(sizeof(int *) * (data->height + 1));
	while (i < data->height)
	{
		data->map[i] = (int *)malloc(sizeof(int) * (data->width + 1));
		i++;
	}
	i = 0;
	fd = open(fdf_file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		fill_data_row(data->map[i], line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	data->map[i] = NULL;
	free(line);
	close(fd);
}
