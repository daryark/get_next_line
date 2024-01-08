/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:52:38 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/08 23:30:32 by dyarkovs         ###   ########.fr       */
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

//if there is no list, the last will be NULL, so no \n char inside
int	find_newline(t_list	*lst)
{
	int		i;

	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
				return (1);
			i++;
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
	node->content = buf;
	node->next = NULL;
}

int	lst_content_len(t_list *lst)
{
	int		size;
	char	*content_ptr;

	size = 0;
	while (lst)
	{
		content_ptr = lst->content;
		while (*content_ptr && *content_ptr != '\n')
		{
			size++;
			content_ptr++;
		}
		if (*content_ptr && *content_ptr == '\n')
			return (++size);
		lst = lst->next;
	}
	return (size);
}
