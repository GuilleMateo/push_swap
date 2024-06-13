/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:34:14 by mguille           #+#    #+#             */
/*   Updated: 2023/02/28 00:34:23 by mguille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

void	pa(t_pile *pils, int affichage)
{
	t_mayon	*element;

	if (!pils || pils->b == 0)
		return ;
	if (affichage)
		ft_printf("pa\n");
	element = pils->b;
	pils->b = element->next;
	if (pils->b)
		pils->b->previous = 0;
	element->position = 0;
	element->next = 0;
	adjusted_position(-1, pils->b);
	adjusted_position(1, pils->a);
	element->next = pils->a;
	if (element->next)
		element->next->previous = element;
	pils->a = element;
	pils->len_a = pils->len_a + 1;
	pils->len_b = pils->len_b - 1;
}
