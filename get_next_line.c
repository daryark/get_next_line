/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:42:42 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/03 21:57:15 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(t_list *lst)
{
	char	*buf;
	int		len;
	int		i;

	len = lst_content_len(lst);
	buf = ft_calloc(sizeof(char), len + 1);
	if (!buf)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!*lst->content)
			lst = lst->next;
		buf[i++] = *lst->content++;
	}
	return (buf);
}

//create list first and all next nodes while line is the same
void	create_list(t_list **lst, int fd)
{
	char	*buf;
	int		chars_read;

	while (!find_newline(*lst))
	{
		buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buf)
			return ;
		chars_read = read(fd, buf, BUFFER_SIZE);
		printf("chars_read: %d\n", chars_read);
		printf("lst->content: %p\n", *lst);
		if (!chars_read)
		{
			free(buf);
			return ;
		}
		ft_lstadd_back(lst, ft_lstnew(buf));
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	if (fd < 0 || read(fd, &lst, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&lst, fd);
	if (lst == NULL)
		return (NULL);
	line = get_line(lst);
	// prep_nextline(lst);
	return (line);
}
