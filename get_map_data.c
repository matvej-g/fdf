/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:39:01 by mgering           #+#    #+#             */
/*   Updated: 2024/07/16 19:01:11 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *fdf_file)
{
	char	*line;
	int		height;
	int		fd;

	height = 0;
	fd = open(fdf_file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		height++;
	}
	close(fd);
	return (height);
}

int	get_width(char *fdf_file)
{
	int		width;
	int		fd;
	char	*line;
	char	**split_line;

	width = 0;
	fd = open(fdf_file, O_RDONLY);
	line = get_next_line(fd);
	split_line = ft_split(line, ' ');
	while (split_line[width])
	{
		free(split_line[width]);
		width++;
	}
	free(split_line);
	free(line);
	close(fd);
	return (width);
}

void	write_data_map(int	*altitude, char *line)
{
	int		i;
	char	**values;

	i = 0;
	values = ft_split(line, ' ');
	while(values[i])
	{
		altitude[i] = ft_atoi(values[i]);
		free(values[i]);
		i++;
	}
	free(values);
}

void	fill_map_data(char *fdf_file, t_fdf *map_data)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	map_data->height = get_height(fdf_file);
	map_data->width = get_width(fdf_file);
	map_data->map = (int **)malloc(sizeof(int *) * (map_data->height + 1));
	while (i < map_data->height)
	{
		map_data->map[i] = (int *)malloc(sizeof(int) * (map_data->width + 1));
		i++;
	}
	i = 0;
	fd = open(fdf_file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		write_data_map(map_data->map[i], line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	map_data->map[i] = NULL;
	free(line);
	close(fd);
}

/* 
#include <stdio.h>

int	main(void)
{
	t_fdf	*data;
	int		i;
	int		j;

	data = (t_fdf*)malloc(sizeof(t_fdf));
	if (!data)
		return (1);
	i = 0;
	j = 0;
	fill_map_data("test.fdf", data);
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			printf("%3d", data->map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("%d", data->width);
	//system("leaks fdf");
	// Free each row of the map
	for (i = 0; i < data->height; i++)
	{
		free(data->map[i]);
	}
	// Free the map array pointer
	free(data->map);
	// Free the data structure
	free(data);
	return (0);
} */
