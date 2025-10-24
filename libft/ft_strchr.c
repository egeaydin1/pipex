/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeaydin <egeaydin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:09:23 by egeaydin          #+#    #+#             */
/*   Updated: 2025/06/14 16:10:03 by egeaydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*a;
	int		i;
	char	new_c;

	a = (char *)s;
	i = 0;
	new_c = (char)c;
	while (a[i])
	{
		if (a[i] == new_c)
			return ((&a[i]));
		i++;
	}
	if (new_c == 0)
	{
		return (&a[i]);
	}
	return (0);
}
