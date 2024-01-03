/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:52:38 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/03 21:10:24 by dyarkovs         ###   ########.fr       */
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

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

//if there is no list, the last will be NULL, so no \n char inside
int	find_newline(t_list	*lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	while (lst->content && *lst->content != '\n')
		lst->content++;
	if (lst->content && *lst->content == '\n')
		return (1);
	return (0);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
	}
}

int	lst_content_len(t_list *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		while (lst->content && *lst->content != '\n')
		{
			size++;
			lst->content++;
		}
		if (lst->content && *lst->content == '\n')
			return (size);
		lst = lst->next;
	}
	return (size);
}
