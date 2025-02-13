/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:45:51 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/12 09:47:15 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

char	*img_finder(int sp_num)
{
	char	*tmp;
	char	*path;

	path = ft_itoa(sp_num);
	if (!path)
		exit(1);
	tmp = ft_strjoin("xpm/", path);
	if (!tmp)
		exit(1);
	free(path);
	path = ft_strjoin(tmp, ".xpm");
	if (!path)
		exit(1);
	free(tmp);
	return (path);
}

void	render_animation(t_mlx *mlx)
{
	int		height;
	int		width;
	int		i;
	void	*img;

	height = HTH;
	width = WTH;
	i = 1;
	while (i < SP)
	{
		img = mlx_new_image(mlx->ptr, WTH, HTH);
		img = mlx_xpm_file_to_image(mlx->ptr, img_finder(i), &width, &height);
		mlx_put_image_to_window(mlx->ptr, mlx->window, img, 0, 0);
		mlx_destroy_image(mlx->ptr, img);
		i++;
	}
}
