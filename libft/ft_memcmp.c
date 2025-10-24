/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeaydin <egeaydin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 07:29:27 by egeaydin          #+#    #+#             */
/*   Updated: 2025/06/14 16:31:52 by egeaydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*pstr1;
	char	*pstr2;

	i = 0;
	pstr1 = (char *)s1;
	pstr2 = (char *)s2;
	if (n == 0)
		return (0);
	while ((unsigned char)pstr2[i] == (unsigned char)pstr1[i] && i < n)
	{
		if (i == n - 1)
			break ;
		i++;
	}
	return ((unsigned char)pstr1[i] - (unsigned char)pstr2[i]);
}
