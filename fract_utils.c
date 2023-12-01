/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:19:45 by dberes            #+#    #+#             */
/*   Updated: 2023/11/30 14:47:24 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	draw_fractal(double z_real, double z_imag, t_data *data)
{
	int		k;
	double	temp;

	k = 0;
	while (k < 300)
	{
		temp = z_real;
		z_real = (z_real * z_real - z_imag * z_imag + data->c_x);
		z_imag = (2 * temp * z_imag + data->c_y);
		if (z_real * z_real + z_imag * z_imag >= 4)
			return ((0x00FFFFFF / 1000) * k);
		k++;
	}
	return (170 * 256 * 256);
}

int	check_complex(double x, double y, t_data *data)
{
	double	z_real;
	double	z_imag;

	if (ft_strncmp(data->type, "Mandelbrot", 10) == 0)
	{
		data->c_x = x;
		data->c_y = y;
		z_real = 0;
		z_imag = 0;
	}
	else
	{
		z_real = x;
		z_imag = y;
        /*should get these from standard input*/
		data->c_x = -0.8;
		data->c_y = 0.156;
	}
	return (draw_fractal(z_real, z_imag, data));
}

int	render_fractal(t_img *img, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			img_pix_put(img, x, y, check_complex((x / 250.0f - 2) * data->scale
					+ data->x_move, (y / 200.0f - 2)
					* data->scale + data->y_move, data));
			x++;
		}
		y++;
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_fractal(&data->img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}

/*destroy window, image, display, free mlx-pointer*/
