/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeaydin <egeaydin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:50:02 by egeaydin          #+#    #+#             */
/*   Updated: 2025/06/18 19:15:50 by egeaydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstnew;
	t_list	*newcontent;
	void	*content;

	lstnew = NULL;
	while (lst != NULL)
	{
		content = (*f)(lst->content);
		newcontent = ft_lstnew(content);
		if (newcontent == NULL)
		{
			del(content);
			ft_lstclear(&lstnew, del);
			return (NULL);
		}
		ft_lstadd_back(&lstnew, newcontent);
		lst = lst->next;
	}
	return (lstnew);
}
