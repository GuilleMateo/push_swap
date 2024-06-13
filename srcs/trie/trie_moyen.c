/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie_moyen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:34:14 by mguille           #+#    #+#             */
/*   Updated: 2023/02/28 00:34:23 by mguille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/push_swap.h"

static void	trie(t_pile *p, t_mayon *mayon_b)
{
	t_mayon	*suivant;

	suivant = find_most_close(p->a, mayon_b);
	if (suivant->index < mayon_b->index)
	{
		if (suivant->next == NULL)
			suivant = p->a;
		else
			suivant = suivant->next;
	}
	faire_r_ou_rr(p, suivant->position, PILE_A);
	use_instruction(TRUE, p, 1, PA);
}

void	trie_moyen(t_pile *p)
{
	while (p->len_a > 3)
		use_instruction(1, p, 1, PB);
	trie_moin_de_3(p, pa_est_il_trier(p));
	while (p->b)
		trie(p, p->b);
	faire_r_ou_rr(p, find_min(p->a)->position, PILE_A);
}
