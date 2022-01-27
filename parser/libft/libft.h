#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

# endif