/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeaydin <egeaydin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:56:02 by egeaydin          #+#    #+#             */
/*   Updated: 2025/06/17 19:06:26 by egeaydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	i;

	i = 0;
	srcsize = ft_strlen(src);
	while (src[i] && i < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size <= srcsize)
		dst[size - 1] = '\0';
	else if (size != 0)
		dst[i] = '\0';
	return (srcsize);
}
