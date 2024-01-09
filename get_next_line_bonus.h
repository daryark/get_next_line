/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:54:35 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/09 16:59:11 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	char			*cont;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	create_list(t_list **lst, int fd);
char	*do_line(t_list *lst);
void	prep_nextline(t_list **lst);
void	ft_lstadd_back(t_list **lst, char	*buf);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
void	clean_node(t_list **lst);
int		find_newline(t_list	*lst);
int		lst_cont_len(t_list *lst);

#endif