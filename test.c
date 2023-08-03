/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:09:32 by gmallet           #+#    #+#             */
/*   Updated: 2023/07/12 18:09:34 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

typedef struct s_rand
{
	int		g;
	int		c;
}	t_rand;

int	test_total_wipe(void)
{
	t_gcan	gc;
	t_rand	*ptr1;
	t_rand	*ptr2;
	t_rand	*ptr3;

	gc_init(&gc);
	ptr1 = gc_malloc(&gc, sizeof(t_rand));
	if (ptr1 == NULL)
		return (1);
	ptr2 = gc_malloc(&gc, sizeof(t_rand));
	if (ptr2 == NULL)
		return (1);
	ptr3 = gc_malloc(&gc, sizeof(t_rand));
	if (ptr3 == NULL)
		return (1);
	gc_clean(&gc);
	return (0);
}

int	test_total_wipe_refeed(void)
{
	t_gcan	gc;
	t_rand	*ptr1;
	t_rand	*ptr2;

	gc_init(&gc);
	ptr1 = gc_malloc(&gc, sizeof(t_rand));
	if (ptr1 == NULL)
		return (1);
	gc_free(&gc, (void **)&ptr1);
	ptr1 = gc_malloc(&gc, sizeof(t_rand));
	if (ptr1 == NULL)
		return (1);
	ptr2 = gc_malloc(&gc, sizeof(t_rand));
	if (ptr2 == NULL)
		return (1);
	gc_free(&gc, (void **)&ptr1);
	gc_free(&gc, (void **)&ptr2);
	ptr1 = gc_malloc(&gc, sizeof(t_rand));
	if (ptr1 == NULL)
		return (1);
	gc_clean(&gc);
	return (0);
}

int	test_access(void)
{
	t_gcan	gc;
	t_rand	*ptr1;

	gc_init(&gc);
	ptr1 = gc_malloc(&gc, sizeof(t_rand));
	if (ptr1 == NULL)
		return (1);
	ptr1->g = 1;
	ptr1->c = 1;
	gc_free(&gc, (void **)&ptr1);
	gc_clean(&gc);
	return (0);
}

int	main(void)
{
	if (test_total_wipe())
		return (1);
	if (test_total_wipe_refeed())
		return (1);
	if (test_access())
		return (1);
}
