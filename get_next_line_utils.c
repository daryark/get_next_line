/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:52:38 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/09 00:49:36 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;

	p = (void *)malloc(size * count);
	if (!p)
		return (NULL);
	i = 0;
	while (i < (count * size))
		*(unsigned char *)(p + i++) = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char	*buf;
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (s1[++i])
		len++;
	buf = ft_calloc(sizeof(char), len + 1);
	if (!buf)
		return (NULL);
	i = -1;
	while (s1[++i])
		buf[i] = s1[i];
	return (buf);
}

//if there is no list, the last will be NULL, so no \n char inside
int	find_newline(t_list	*lst)
{
	int		i;

	while (lst)
	{
		i = -1;
		while (lst->cont[++i])
		{
			if (lst->cont[i] == '\n')
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_lstadd_back(t_list **lst, char *buf)
{
	t_list	*node;
	t_list	*head;

	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	head = *lst;
	if (!head)
		*lst = node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	node->cont = buf;
	node->next = NULL;
}

int	lst_cont_len(t_list *lst)
{
	int		size;
	char	*cont_ptr;

	size = 0;
	while (lst)
	{
		cont_ptr = lst->cont;
		while (*cont_ptr && *cont_ptr != '\n')
		{
			size++;
			cont_ptr++;
		}
		if (*cont_ptr && *cont_ptr == '\n')
			return (++size);
		lst = lst->next;
	}
	return (size);
}
