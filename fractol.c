/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:45:42 by dberes            #+#    #+#             */
/*   Updated: 2023/11/10 16:13:22 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n && (p1[i] != '\0' || p2[i] != '\0'))
	{
		if (p1[i] < p2[i])
			return (-1);
		else if (p1[i] > p2[i])
			return (1);
		i++;
	}
	return (0);
}

int check_complex(double x, double y, t_data *data)
{
	int k;
	double  z_real;
	double  z_imag;
	double  temp;

	if (ft_strncmp(data->type, "Mandelbrot", 10) == 0)
	{
		data->c_x = x;
		data->c_y = y;
		z_real = 0;
		z_imag = 0;
	}
	else if (ft_strncmp(data->type, "Julia", 5) == 0)
	{
		z_real = x;
		z_imag = y;
		data->c_x = -0.8;
		data->c_y = 0.156;
	}
	k = 0;
	while (k <1000)
	{
		temp = z_real;
        
		z_real = (z_real*z_real - z_imag*z_imag + data->c_x);
		z_imag = (2*temp*z_imag + data->c_y);
		if ( z_real*z_real + z_imag*z_imag >= 4)
			return ((0x00FFFFFF / 1000) * k);
		k++;
	}
	return (170*256*256);
}

int	render_fractal(t_img *img, t_data *data)
{
	int x;
	int y;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			img_pix_put(img, x, y, check_complex((x/250.0f -2)*data->scale + data->x_move, (y/200.0f -2)*data->scale + data->y_move, data));
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
		data->x_move += ((double)(x -WINDOW_WIDTH/2)/250.0f*0.1*data->scale);
		data->y_move += ((double)(y -WINDOW_HEIGHT/2)/200.0f*0.1*data->scale);
	}
	else if (button == 5)
	{
		data->scale *= 1.05;
		data->x_move -= ((double)(x -WINDOW_WIDTH/2)/250.0f*0.1*data->scale);
		data->y_move -= ((double)(y -WINDOW_HEIGHT/2)/200.0f*0.1*data->scale);
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
	
	render_fractal(&data->img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	(void) argc;
    t_data	data;

	data.scale = 1;
	data.y_move = 0;
	data.x_move = 0;
	if (ft_strncmp(argv[1], "Mandelbrot", 10) == 0)
		data.type = "Mandelbrot";
	else if (ft_strncmp(argv[1], "Julia", 5) == 0)
		data.type = "Julia";
	else
	{
		printf("%s\n", "Wrong input. Fractals to choose:\nMandelbrot\nJulia");
		return (0);
	}
	
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
