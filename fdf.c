/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:08:49 by mgering           #+#    #+#             */
/*   Updated: 2024/08/13 15:07:43 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
	}
}
// void check_leaks(void)
// {
//     system("leaks fdf");
// }
	// atexit(check_leaks);

int32_t	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc != 2)
	{
		write(2, "use one map as parameter\n", 26);
		exit(EXIT_FAILURE);
	}
	check_map_file(argv[1]);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		exit(EXIT_FAILURE);
	fill_map_data(argv[1], data);
	check_min_max_map(data);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "FDF", false);
	if (!data->mlx_ptr)
		free(error(data));
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img_ptr)
		free(error(data));
	mlx_image_to_window(data->mlx_ptr, data->img_ptr, 0, 0);
	iterate_map(data);
	mlx_loop_hook(data->mlx_ptr, &hook, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	return (EXIT_SUCCESS);
}
