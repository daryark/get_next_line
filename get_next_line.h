/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:38:45 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/21 21:56:32 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_gnl_lst
{
	char				*cont;
	struct s_gnl_lst	*next;
}	t_gnl_lst;

char	*get_next_line(int fd);
void	create_list(t_gnl_lst **lst, int fd);
char	*do_line(t_gnl_lst *lst);
void	prep_nextline(t_gnl_lst **lst);
void	ft_lstadd(t_gnl_lst **lst, char	*buf);

void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_strdup_gnl(const char *s1);
void	clean_node(t_gnl_lst **lst);
int		find_newline(t_gnl_lst	*lst);
int		lst_cont_len(t_gnl_lst *lst);

#endif
