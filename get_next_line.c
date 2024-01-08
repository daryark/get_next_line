/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:42:42 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/08 23:13:59 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		buffer[i] = s1[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

void	prep_nextline(t_list **lst)
{
	int		i;
	char	*new_s;
	t_list	*tmp;

	while (*lst)
	{
		i = 0;
		while ((*lst)->content[i])
		{
			if ((*lst)->content[i] == '\n' && (*lst)->content[i + 1])
			{
				new_s = ft_strdup(&((*lst)->content[i + 1]));
				free((*lst)->content);
				(*lst)->content = new_s;
				return ;
			}
			i++;
		}
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

char	*get_line(t_list *lst)
{
	char	*buf;
	int		len;
	int		b;
	int		l;

	len = lst_content_len(lst);
	buf = ft_calloc(sizeof(char), len + 1);
	if (!buf)
		return (NULL);
	b = 0;
	l = 0;
	while (b < len)
	{
		if (!lst->content[l])
		{
			lst = lst->next;
			l = 0;
		}
		buf[b++] = lst->content[l++];
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
		ft_lstadd_back(lst, buf);
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
	prep_nextline(&lst);
	return (line);
}

		// 		t_list *head = lst;
		// while (head)
		// {
		// 	printf("content: %s\n", (head)->content);
		// 	head = head->next;
		// }