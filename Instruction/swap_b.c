/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:34:14 by mguille           #+#    #+#             */
/*   Updated: 2023/02/28 00:34:23 by mguille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

void	sb(t_pile *pils, int affichage)
{
	t_mayon	*second;
	t_mayon	*first;

	if (!pils || pils->b == 0 || pils->len_b <= 1)
		return ;
	if (affichage)
		ft_printf("sb\n");
	first = pils->b;
	second = pils->b->next;
	first->position = 1;
	second->position = 0;
	first->previous = second;
	second->previous = 0;
	first->next = second->next;
	if (second->next)
		second->next->previous = first;
	second->next = first;
	pils->b = second;
}
