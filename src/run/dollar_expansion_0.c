/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:55:06 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/01 12:39:27 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "dollar_expansion.h"
#include "expansion.h"
#include "libft.h"
#include "word_list.h"
#include "error_handling.h"

static void	no_space_case(char **word, char **env)
{
	char	*tmp;

	tmp = ft_getenv_aram(*word + 1, env);
	ft_free ((void **)word);
	if (tmp == NULL)
		*word = ft_strdup("");
	else
		*word = ft_strdup(tmp);
	if (!*word)
		panic_malloc();
}

void	expand_word(t_word_node *node, char ***env)
{
	char	*tmp;
	char	*tmp2;
	char	*space;

	if (*node->word != '$')
		return ;
	if (*(node->word + 1) == ' ' || *(node->word + 1) == '\0')
		return ;
	space = strchr(node->word, ' ');
	if (space)
	{
		tmp2 = ft_substr(node->word + 1, 0, space - node->word - 1);
		if (!tmp2)
			panic_malloc();
		tmp = ft_getenv_aram(tmp2, *env);
		ft_free ((void **)&tmp2);
		tmp2 = ft_strjoin(tmp, space);
		ft_free ((void **)&node->word);
		node->word = tmp2;
	}
	else
		no_space_case(&node->word, *env);
}

static char	*join_words(t_word_node *head, char ***env)
{
	char	*out;
	char	*tmp;	

	out = NULL;
	while (head)
	{
		expand_word(head, env);
		if (head->word)
		{
			if (!out)
				tmp = ft_strdup(head->word);
			else
				tmp = ft_strjoin(out, head->word);
			if (!tmp)
				panic_malloc();
			ft_free ((void **)&out);
			out = tmp;
		}
		if (head->next)
			head = head->next;
		else
			head = NULL;
	}
	return (out);
}

static void	tokenizer(char **ptr, char **current, t_word_node **head, \
	t_data *data)
{
	while (1)
	{
		*ptr = is_there_unquoted_dollar(*current);
		if (!*ptr && func_1(current, head))
			break ;
		if (*ptr != *current)
		{
			if (func_5(ptr, current) && func_6(head, current))
				break ;
			func_2(head, current, ptr);
		}
		if (*(*ptr + 1) == '\0' && func_7(head))
			break ;
		if (func_3(ptr, head, data, current))
			continue ;
		func_4(ptr, current, head);
	}
}

void	dollar_expansion(char **word, t_data *data)
{
	char		*ptr;
	char		*current;
	t_word_node	*head;	

	if (!is_there_unquoted_dollar(*word))
		return ;
	current = *word;
	head = NULL;
	tokenizer(&ptr, &current, &head, data);
	ft_free((void **)word);
	*word = join_words(head, &data->env);
	free_word_list(head);
}
