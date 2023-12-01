/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:05:23 by dberes            #+#    #+#             */
/*   Updated: 2023/12/01 13:21:17 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <complex.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft/libft.h"

# define WIDTH 1000
# define HEIGHT 800
# define MLX_ERROR 1
# define GREEN_PIXEL 0xFF00
# define RED_PIXEL 0xFF0000
# define WHITE_PIXEL 0xFFFFFF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	double	scale;
	double	x_move;
	double	y_move;
	double	c_x;
	double	c_y;
	char	*type;
	t_img	img;
}	t_data;

int	check_complex(double x, double y, t_data *data);
int	render_fractal(t_img *img, t_data *data);
int	handle_keypress(int keysym, t_data *data);
int	handle_mouse_event(int button, int x, int y, t_data *data);
int	clean_exit(t_data *data, int error);
int	render(t_data *data);
int	draw_fractal(double z_real, double z_imag, t_data *data);
int	check_type(char *type, t_data *data);

#endif // FRACTOL_H
