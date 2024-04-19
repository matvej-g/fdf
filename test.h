/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:29:05 by mgering           #+#    #+#             */
/*   Updated: 2024/04/19 14:30:27 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libs/MLX42/include/MLX42/MLX42.h"
# define WIDTH 256
# define HEIGHT 256

typedef struct mlx
{
	void		*window;
	void		*context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;

#endif