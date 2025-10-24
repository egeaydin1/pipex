/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeaydin <egeaydin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:43:35 by egeaydin          #+#    #+#             */
/*   Updated: 2025/06/17 19:54:07 by egeaydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;
	size_t	s1size;

	if (!s1)
		return ((char *)s1);
	if (!s2)
		return ((char *)s2);
	i = -1;
	j = -1;
	s1size = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (s1size + (ft_strlen(s2) + 1)));
	if (!ptr)
		return (NULL);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
	{
		ptr[i] = s2[j];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
