/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:56:32 by amarouf           #+#    #+#             */
/*   Updated: 2025/03/01 10:09:38 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	main(int ac, char **av)
{
	t_mlx	mlx;

	ft_bzero(&mlx, sizeof(t_mlx));
	mlx.bonus = true;
	return (start(ac, av, &mlx));
}
