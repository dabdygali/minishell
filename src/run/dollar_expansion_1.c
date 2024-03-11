/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:25:10 by akeryan           #+#    #+#             */
/*   Updated: 2024/02/23 00:08:20 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "error_handling.h"
#include "word_list.h"
#include "libft.h"
#include "data.h"

int	func_1(char **current, t_word_node **head)
{
	if (ft_strlen(*current) > 0)
		add_word_back(head, new_word(*current));
	return (1);
}

void	func_2(t_word_node **head, char **current, char **ptr)
{
	char		*substr;
	t_word_node	*node;

	substr = ft_substr(*current, 0, *ptr - *current);
	if (!substr)
		panic("ft_substr failed");
	node = new_word_m(substr);
	add_word_back(head, node);
	*current = *ptr;
}

int	func_3(char **ptr, t_word_node **head, t_data *data, char **current)
{
	if (*(*ptr + 1) == '$' || *(*ptr + 1) == '?')
	{
		if (*(*ptr + 1) == '$')
			add_word_back(head, new_word_m(ft_itoa(data->dbl_dollar)));
		else
			add_word_back(head, new_word_m(ft_itoa(data->exit_status)));
		*ptr += 2;
		*current = *ptr;
		return (1);
	}
	else
		return (0);
}

void	func_4(char **ptr, char **current, t_word_node **head)
{
	char		*substr;
	t_word_node	*node;

	while (*(*ptr + 1) != '$' && *(*ptr + 1) != '\0' && *(*ptr + 1) != '"' \
					&& *(*ptr + 1) != '\'')
		(*ptr)++;
	(*ptr)++;
	if (*ptr != *current)
	{
		substr = ft_substr(*current, 0, *ptr - *current);
		if (!substr)
			panic_malloc();
		node = new_word_m(substr);
		add_word_back(head, node);
		*current = *ptr;
	}
}

int	func_5(char **ptr, char **current)
{
	if ((*(*ptr + 1) == '\0' || *(*ptr + 1) == '"') && \
		!ft_strchr(*current + 1, '$'))
		return (1);
	else
		return (0);
}
