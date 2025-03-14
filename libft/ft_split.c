/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:46:31 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/21 09:13:36 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_all(char **words, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (unsigned char)s[i] == (unsigned char)c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && (unsigned char)s[i] != (unsigned char)c)
				i++;
		}
	}
	return (count);
}

static	int	word_len(char const *s, char c)
{
	int	current_len;

	current_len = 0;
	while (*(s + current_len) && *(s + current_len) != c)
		current_len++;
	return (current_len);
}

static char	*allocate_and_copy(char const *s, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (word);
	while (len > 0)
	{
		word[i] = *(s + i);
		i++;
		len--;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		index_word;
	int		current_len;

	if (!s)
		return (NULL);
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (result);
	index_word = 0;
	result[count_words(s, c)] = NULL;
	while (*s)
	{
		while ((unsigned char)*s == (unsigned char)c)
			s++;
		if (!*s)
			break ;
		current_len = word_len(s, c);
		result[index_word] = allocate_and_copy(s, current_len);
		if (!result[index_word])
			return (free_all(result, index_word));
		s += current_len;
		index_word++;
	}
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s[] = "hello!zzzzzzzz";
// 	char	**result;
// 	int	i = 0;

// 	// printf("Count: %d\n", count_words(s, 'z'));
// 	// printf("word len: %d\n", word_len(s, 'z'));
// 	result = ft_split(s, 'z');
// 	while(result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		i++;
// 	}
// 	free_all(result, 1);
// 	return (0);
// }