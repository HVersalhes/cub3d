/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                               +:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/09/25 22:18:48 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* lista ligada de stashs: um no por file descriptor aberto */
typedef struct s_stash
{
	int				fd;
	char			*buf;
	struct s_stash	*next;
}	t_stash;

char	*get_next_line(int fd);
t_stash	*ft_stash_get(t_stash **stash, int fd);
void	ft_stash_del(t_stash **stash, int fd);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);

#endif
