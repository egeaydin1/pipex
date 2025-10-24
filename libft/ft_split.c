/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hientranpc <hientranpc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:20:32 by egeaydin          #+#    #+#             */
/*   Updated: 2025/10/06 13:04:14 by hientranpc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countwords(char *str, char set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != set && (str[i + 1] == set || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_free(char **res, size_t wordlen)
{
	while (wordlen--)
		free(res[wordlen]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	wordlen;
	size_t	words;
	size_t	i;
	char	**res;

	words = countwords((char *)s, c);
	i = 0;
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	while (i < words)
	{
		wordlen = 0;
		while (*s == c)
			s++;
		while (s[wordlen] != c && s[wordlen])
			wordlen++;
		res[i] = ft_substr(s, 0, wordlen);
		if (!res[i])
			return (ft_free(res, i));
		s += wordlen;
		i++;
	}
	res[i] = NULL;
	return (res);
}
