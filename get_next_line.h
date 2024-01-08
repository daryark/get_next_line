/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:38:45 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/08 19:27:01 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define MAGENTA "\033[0;35m"
# define RED "\033[0;31m"
# define RESET_COLOR "\033[0m"

# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	create_list(t_list **lst, int fd);
char	*get_line(t_list *lst);

int		find_newline(t_list	*lst);
int		lst_content_len(t_list *lst);

void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_list **lst, char	*buf);
// t_list	*ft_lstnew(char *content);


char    *ft_strdup(const char *s1);

#endif