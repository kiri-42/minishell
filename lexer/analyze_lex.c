/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_lex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:40 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/09 16:09:02 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "lexer.h"
#include <unistd.h>
#include <readline/history.h>

static t_lexer_product	*new_lexer_product(void)
{
	t_lexer_product	*product;

	product = ft_calloc(1, sizeof(t_lexer_product));
	if (product == NULL)
		exit(EXIT_FAILURE);
	return (product);
}

void	make_token_list(const char *line, t_token **token,
		t_lexer **lexer, t_lexer_product **lexer_product)
{
	*lexer_product = new_lexer_product();
	*lexer = new_lexer(line);
	while (true)
	{
		*token = next_token(*lexer);
		ft_lstadd_back(&(*lexer_product)->token_list, ft_lstnew(*token));
		if ((*token)->type == TOKEN_EOF)
			break ;
	}
	return ;
}

bool	should_return(t_lexer_product *lexer_product)
{
	if (((t_token *)lexer_product->token_list->content)->type == TOKEN_EOF)
	{
		delete_lexer_product(lexer_product);
		return (true);
	}
	if (!is_valid_tokens(lexer_product->token_list))
	{
		if (write(STDERR, "syntax error\n", 13) < 0)
			exit(EXIT_FAILURE);
		delete_lexer_product(lexer_product);
		g_exit_status = 258;
		return (true);
	}
	return (false);
}

bool	heredoc_process(t_lexer *lexer, t_lexer_product *lexer_product,
		t_list *env)
{
	bool	flag;

	flag = true;
	while (lexer->io_here_delimiters != NULL && flag)
		flag = read_heredoc(lexer, env);
	if (!flag)
	{
		delete_lexer_product(lexer_product);
		return (true);
	}
	return (false);
}

t_lexer_product	*analyze_lex(const char *line, t_list *env)
{
	t_lexer			*lexer;
	t_token			*token;
	t_lexer_product	*lexer_product;

	make_token_list(line, &token, &lexer, &lexer_product);
	if (should_return(lexer_product))
	{
		delete_lexer_without_heredocs(lexer);
		return (NULL);
	}
	if (heredoc_process(lexer, lexer_product, env))
		return (NULL);
	if (ft_strlen(lexer->input) > 0)
		add_history(lexer->input);
	expand_envvar(lexer_product->token_list, env);
	word_split(lexer_product->token_list);
	ft_lstiter(lexer_product->token_list, &expand_quote);
	lexer_product->heredocs = lexer->heredocs;
	delete_lexer_without_heredocs(lexer);
	return (lexer_product);
}
