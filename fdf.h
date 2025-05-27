/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:29:05 by mgering           #+#    #+#             */
/*   Updated: 2024/08/13 15:08:23 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>		//for quick maths
# include <limits.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "libs/MLX42/include/MLX42/MLX42.h"
# define WIDTH 1980
# define HEIGHT 1024

typedef struct s_fdf
{
	int				offset_x;
	int				offset_y;
	int				height;
	int				width;
	int				**map;
	int				scale;
	uint32_t		color;
	void			*mlx_ptr;
	void			*img_ptr;
}	t_fdf;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_draw
{
	t_point	newp1;
	t_point	newp2;
	int		dx;
	int		dy;
	int		err;
	int		x_step;
	int		y_step;
}	t_draw;

//---------------fdf.c-------------
void	hook(void *param);
int32_t	main(int argc, char **argv);

//---------------get_map_data.c-------------
int		get_width(char *line);
void	get_height_width(t_fdf *data, char *fdf_file);
void	fill_data_row(int	*altitude, char *line);
void	fill_map_data(char *fdf_file, t_fdf *data);

//---------------map_utils.c-------------
void	check_min_max_map(t_fdf *data);
void	set_scale(int min, int max, t_fdf *data);

//---------------draw_line_algo.c-------------
void	draw_line(t_fdf *data, t_draw draw_var);
void	draw_setup(t_point p1, t_point p2, t_fdf *data);
void	iterate_map(t_fdf *data);

//---------------draw_utils.c-------------
void	put_pixel_in_window(t_point p, t_fdf *data);
void	setup_calc_var(t_point p1, t_point p2, t_fdf *data, t_draw *draw_var);
int		slope_calc(int temp1, int temp2);
t_point	apply_scale(t_point p, t_fdf *data);
void	isometric(t_point *p1, t_point *p2);

//---------------error.c.c-------------
void	*error(t_fdf *data);
void	free_data(t_fdf *data);
void	check_map_file(char *file);

#endif
