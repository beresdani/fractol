#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>

#define MLX_ERROR 1

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}	t_data;


typedef struct s_rect
{
    int x;
    int y;
    int width;
    int height;
    int color;
}   t_rect;

int	handle_no_event(t_data *data)
{
    return (0);
}


int render_rect(t_img *img, t_rect rect)
{
    int i;
    int j;

    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
            img_pix_put(img, j++, i, rect.color);
        i++;
    }
    return (0);
}

/*
int render_background(t_img *img, int color)
{
    int i;
    int j;

    i = 0;
    while (i < WINDOW_HEIGHT)
    {
        j = 0;
        while (j < WINDOW_WIDTH)
            img_pix_put(img, j++, i, color);
        i++;
    }
    return (0);
}
*/
 /* render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
    render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL}); */


int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	printf("Keypress: %d\n", keysym);
    return (0);
}

int main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr,500, 500, "My First Window");
    if (data.win_ptr == NULL)
    {
        free(data.win_ptr);
        return (MLX_ERROR);
    }
    mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	if (data.win_ptr != NULL)
	{
		printf("%p\n", data.win_ptr);
		mlx_pixel_put(data.mlx_ptr, data.win_ptr, 250, 250, 0xFF0000);
	}
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_loop(data.mlx_ptr);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}