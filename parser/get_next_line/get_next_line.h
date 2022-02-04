/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:42:25 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:28:37 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 50

char	*get_next_line(int fd);
int		get_behind_nl(char (temp)[BUFFER_SIZE + 1]);
char	*get_next_line_malloc(char (temp)[BUFFER_SIZE + 1], char **outp,
			int *i);

#endif