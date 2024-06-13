/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie_de_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:34:14 by mguille           #+#    #+#             */
/*   Updated: 2023/02/28 00:34:23 by mguille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/push_swap.h"

static int	cout_placement(int position, int len)
{
	if (position > len / 2)
		return (position - len);
	return (position);
}

void	faire_r_ou_rr(t_pile *p, int position, int ab)
{
	int	res;

	if (ab)
		res = cout_placement(position, p->len_a);
	else
		res = cout_placement(position, p->len_b);
	while (res)
	{
		if (res < 0)
		{
			if (ab)
				use_instruction(TRUE, p, 1, RRA);
			else
				use_instruction(TRUE, p, 1, RRB);
			res++;
		}
		else
		{
			if (ab)
				use_instruction(TRUE, p, 1, RA);
			else
				use_instruction(TRUE, p, 1, RB);
			res--;
		}
	}
}

void	trie_moin_de_3(t_pile *pil, int p_min)
{
	if (!pil || !p_min)
		return ;
	if (pil->len_total == 2 || (pil->len_a == 3 && p_min == -2))
		return (use_instruction(TRUE, pil, 1, SA));
	else if (pil->len_a == 3 && p_min == -3)
		return (use_instruction(TRUE, pil, 2, RA, SA));
	else if (pil->len_a == 3 && p_min == -1)
		return (use_instruction(TRUE, pil, 2, RRA, SA));
	else if (p_min > 0)
		return (faire_r_ou_rr(pil, p_min, PILE_A));
}
