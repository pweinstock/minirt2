/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:41:18 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/27 18:25:08 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

int	get_behind_nl(char (*temp)/*[BUFFER_SIZE + 1]*/)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((temp)[i] != '\n' && (temp)[i])
		i++;
	if ((temp)[i] == '\n')
	{
		while ((temp)[i + j] && ++j)
			(temp)[j - 1] = (temp)[i + j];
		return (1);
	}
	return (0);
}

char	*get_next_line_malloc(char (*temp)/*[BUFFER_SIZE + 1]*/, char **outp,
								int *i)
{
	char	*temp1;
	int		j;

	j = 0;
	while ((temp)[*i] && (((temp)[*i - 1] != '\n') || *i == 0))
		(*i)++;
	while ((*outp) != NULL && (*outp)[j])
		j++;
	temp1 = malloc(*i + j + 1);
	if (temp1 == NULL)
		return (0);
	if (temp1 == NULL)
		return (NULL);
	temp1[*i + j] = '\0';
	while ((*i) > 0 && (*i)--)
		temp1[j + (*i)] = (temp)[*i];
	while ((*outp) != NULL && j > 0 && j--)
		temp1[j] = (*outp)[j];
	free ((*outp));
	return (temp1);
}

char	*get_next_line(int fd)
{
	int			i;
	static char	temp[BUFFER_SIZE + 1];
	char		*outp;

	i = 1;
	outp = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (i)
	{
		i = 0;
		if (temp[i])
		{
			outp = get_next_line_malloc(temp, &outp, &i);
			if (get_behind_nl(temp))
				return (outp);
		}
		i = read(fd, temp, BUFFER_SIZE);
		if (i < 0)
			return (NULL);
		temp[i] = '\0';
	}
	return (outp);
}
