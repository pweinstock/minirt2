/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 10:01:14 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/05 13:43:15 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	size_t	sum;

	i = 0;
	sign = 1;
	sum = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		sum = (sum * 10) + (str[i] - 48);
		i++;
	}
	if(str[i] != 0 && str[i] != '.')
	{
		printf("Error\n%c: Is not a number", str[i]);
		exit(0);
	}
	return (sum * sign);
}
