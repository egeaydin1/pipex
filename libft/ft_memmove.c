/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeaydin <egeaydin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:33:20 by egeaydin          #+#    #+#             */
/*   Updated: 2025/06/17 18:37:00 by egeaydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tdest;
	char	*tsrc;

	if (!src && !dest)
		return (NULL);
	tdest = (char *)dest;
	tsrc = (char *)src;
	if (tdest < tsrc)
		ft_memcpy(tdest, tsrc, n);
	else
	{
		while (n > 0)
		{
			n--;
			tdest[n] = tsrc[n];
		}
	}
	return (dest);
}
