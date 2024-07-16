/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:29:05 by mgering           #+#    #+#             */
/*   Updated: 2024/07/16 19:01:35 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>		//for quick maths
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "libs/MLX42/include/MLX42/MLX42.h"
# define WIDTH 1048
# define HEIGHT 1048

typedef struct s_fdf
{
	int		height;
	int		width;
	int		**map;
	int		scale;
	void	*mlx_ptr;
	void	*img_ptr;
}	t_fdf;

void	fill_map_data(char *fdf_file, t_fdf *data);
int		step_calc(int temp1, int temp2);
void	draw_lines(t_fdf *data);
void	isometric(int *x, int *y, int z);

#endif