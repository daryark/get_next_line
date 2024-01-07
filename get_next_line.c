/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:42:42 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/07 21:27:19 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	prep_nextline(t_list **lst)
{
	t_list	*head;
	int		i;
	char	*new_s;

	head = *lst;
	while (*lst)
	{
		i = 0;
		while ((*lst)->content[i])
		{
			printf("START POINT: %c\n", (*lst)->content[i]);
			printf("COntent: %c\n", (*lst)->content[i + 1]);
			printf("POINTER: %p\n", (*lst)->content);
			printf("STRING: %s\n", (*lst)->content);
			if ((*lst)->content[i] == '\n' && (*lst)->content[i + 1])
			{
				if ((*lst)->content[i + 1])
					new_s = &((*lst)->content[i + 1]);
				free((*lst)->content);
				(*lst)->content = new_s;
				return ;
			}
			i++;
		}
		head = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = head;
	}
	*lst = NULL;
}

char	*get_line(t_list *lst)
{
	char	*buf;
	int		len;
	int		i;

	len = lst_content_len(lst);
	printf("\nlen: %d\n", len);
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
		buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buf)
			return ;
		chars_read = read(fd, buf, BUFFER_SIZE);
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

	lst = NULL;
	if (fd < 0 || read(fd, &lst, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&lst, fd);
	if (lst == NULL)
		return (NULL);
	printf("STRING BEFORE: %s\n", lst->content);
	line = get_line(lst);
	prep_nextline(&lst);
	return (line);
}
