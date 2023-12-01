/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:45:42 by dberes            #+#    #+#             */
/*   Updated: 2023/12/01 13:59:37 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		clean_exit(data, 0);
	else if (keysym == XK_Up)
		data->y_move += 0.1 * data->scale;
	else if (keysym == XK_Down)
		data->y_move -= 0.1 * data->scale;
	else if (keysym == XK_Left)
		data->x_move += 0.1 * data->scale;
	else if (keysym == XK_Right)
		data->x_move -= 0.1 * data->scale;
	return (0);
}

int	handle_mouse_event(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		data->scale *= 0.95;
		data->x_move += ((double)(x - WIDTH / 2) / 250.0f * 0.1 * data->scale);
		data->y_move += ((double)(y - HEIGHT / 2) / 200.0f * 0.1 * data->scale);
	}
	else if (button == 5)
	{
		data->scale *= 1.05;
		data->x_move -= ((double)(x - WIDTH / 2) / 250.0f * 0.1 * data->scale);
		data->y_move -= ((double)(y - HEIGHT / 2) / 200.0f * 0.1 * data->scale);
	}
	return (0);
}

int	clean_exit(t_data *data, int error)
{
	if (data->mlx_ptr && data->win_ptr && data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (error);
}

int	check_type(char *type, t_data *data)
{
	if (ft_strncmp(type, "Mandelbrot", 10) == 0)
	{
		data->type = "Mandelbrot";
		return (1);
	}
	else if (ft_strncmp(type, "Julia", 5) == 0)
	{
		data->type = "Julia";
		return (1);
	}
	else
	{
		ft_printf("%s\n", "Wrong input.\n");
		ft_printf("%s\n", "Fractals to choose:\nMandelbrot\nJulia");
		return (0);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	data.scale = 1;
	data.y_move = 0;
	data.x_move = 0;
	if (check_type(argv[1], &data) == 0)
		return (0);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		clean_exit(&data, MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Fractals 42");
	if (data.win_ptr == NULL)
		clean_exit(&data, MLX_ERROR);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	if (data.img.mlx_img == NULL)
		clean_exit(&data, MLX_ERROR);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, 
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, NoEventMask, &clean_exit, &data);
	mlx_mouse_hook(data.win_ptr, &handle_mouse_event, &data);
	mlx_loop(data.mlx_ptr);
}
