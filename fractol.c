/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:45:42 by dberes            #+#    #+#             */
/*   Updated: 2023/11/09 16:14:08 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <complex.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define MLX_ERROR 1
#define GREEN_PIXEL 0xFF00
#define RED_PIXEL 0xFF0000
#define WHITE_PIXEL 0xFFFFFF

typedef struct s_img
{
    void    *mlx_img;
    char    *addr;
    int     bpp; /*bits per pixel*/
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
    double  scale;
	double	x_move;
	double	y_move;
	double	x_dist;
	double	y_dist;
    t_img   img;
}	t_data;


void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}

/*
void img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;
    int     i;

    i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img ->bpp / 8));
    while (i >=0)
    {
        if (img->endian !=0)
            *pixel++ = (color >> i) & 0xFF;
        else
            *pixel++ = (color >> (img->bpp - 8 -i)) & 0xFF;
        i -= 8;
    }
}
*/

int check_complex(double x, double y, t_data *data)
{
	int k;
	double  z_real;
	double  z_imag;
	double  temp;

	z_real = 0;
	z_imag = 0;
	k = 0;
	while (k <256)
	{
		temp = z_real;
        
		z_real = (z_real*z_real - z_imag*z_imag + x);
		z_imag = (2*temp*z_imag + y);
		if ( z_real*z_real + z_imag*z_imag >= 4)
			return ((0x00FFFFFF / 256) * k);
		k++;
	}
	return (170*256*256);
}

int	render_mandelbrot(t_img *img, t_data *data)
{
	int x;
	int y;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			img_pix_put(img, x, y, check_complex((x/250.0f -2 + data->x_dist/2)*data->scale + data->x_move, (y/200.0f -2 + data->y_dist/2)*data->scale + data->y_move, data));
			x++;
		}
		y++;
	}
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
    {
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
    }
	else if (keysym == XK_Up)
		data->y_move += 0.1*data->scale;
	else if (keysym == XK_Down)
		data->y_move -= 0.1*data->scale;
	else if (keysym == XK_Left)
		data->x_move += 0.1*data->scale;
	else if (keysym == XK_Right)
		data->x_move -= 0.1*data->scale;
    return (0);
}

int	handle_mouse_event(int button, int x, int y, t_data *data)
{
    if(button == 4)
	{
        data->scale *= 0.95;
		data->x_move += (x/WINDOW_WIDTH - 0.5)*0.1*data->scale;
		data->y_move += (y/WINDOW_HEIGHT - 0.5)*0.1*data->scale;
	}
	else if (button == 5)
	{
		data->scale *= 1.05;
		data->x_move -= (x/WINDOW_WIDTH - 0.5)*data->scale;
		data->y_move -= (y/WINDOW_HEIGHT - 0.5)*data->scale;
	}
    return (0);
}

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	exit(0);
}

int	render (t_data *data)
{
	if (data->win_ptr == NULL)
        return (1);
	render_mandelbrot(&data->img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(void)
{
    t_data	data;

	data.scale = 1;
	data.y_move = 0;
	data.x_move = 0;
	data.x_dist = 0;
	data.y_dist = 0;
    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "trial 42");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
    data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, NoEventMask, &close_window, &data);
    mlx_mouse_hook(data.win_ptr, &handle_mouse_event, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
