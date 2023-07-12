/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:09:40 by gmallet           #+#    #+#             */
/*   Updated: 2023/07/12 18:10:01 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	gc_init(t_gcan *gcan)
{
	gcan->fnode = NULL;
	gcan->lnode = NULL;
	gcan->tsize = 0;
	gcan->nb_allocs = 0;
}

void	*gc_malloc(t_gcan *gcan, size_t size)
{
	if (gcan->fnode == NULL)
	{
		gcan->fnode = malloc(sizeof(t_gcan) + (size));
		if (gcan->fnode == NULL)
			return (NULL);
		gcan->lnode = gcan->fnode;
		gcan->lnode->prev = NULL;
	}
	else
	{
		gcan->lnode->next = malloc(sizeof(t_gcan) + (size));
		if (gcan->lnode->next == NULL)
			return (NULL);
		gcan->lnode->next->prev = gcan->lnode;
		gcan->lnode = gcan->lnode->next;
	}
	gcan->lnode->next = NULL;
	gcan->lnode->size = size;
	gcan->tsize += size;
	gcan->nb_allocs += 1;
	return (gcan->lnode + 1);
}

void	gc_free(t_gcan *gcan, void **ptr)
{
	t_gc_node	*node;

	node = ((t_gc_node *)(*ptr) - 1);
	if (node->prev != NULL)
		node->prev->next = node->next;
	else
		gcan->fnode = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	else
		gcan->lnode = node->prev;
	gcan->tsize -= node->size;
	gcan->nb_allocs -= 1;
	free(node);
	(*ptr) = NULL;
	return ;
}

void	gc_clean(t_gcan *gcan)
{
	while (gcan->fnode != NULL)
	{
		gcan->lnode = gcan->fnode->next;
		free(gcan->fnode);
		gcan->fnode = gcan->lnode;
	}
	gcan->fnode = NULL;
	gcan->lnode = NULL;
	gcan->tsize = 0;
	gcan->nb_allocs = 0;
}
