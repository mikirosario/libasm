

Shameless copypaste from github xD

So from what I'm seeing, we interpret that the higher positions
in a string are like the high bytes of a variable, more significant.
We keep comparing strings, subtract s2 from s1, where s1 is listmem->data
and s2 is listmem->next->data, and if the result is positive, then s1 is
'greater' than s2, so we swap them so that they are in ascending order.

This version goes through the whole list until tmp2->next is null.
If there were any swaps it resets i and all pointers to reiterate
over and over until no preceding string is greater than a proceding
string.

Looks like something I'd invent so easiest for me to understand, but
I saw a seemingly more efficient version I'll want to look into now
that I understand what this function is all about. (Thanks again
Piscine Subjects for being SO clear that straight C is easier to
read... :p). I appreciate the safety features though. ;)

void		ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*tmp1;
	t_list	*tmp2;
	int		i;

	i = 1;
	if (*begin_list == NULL || (*begin_list)->next == NULL)
		return ;
	while (i)
	{
		i = 0;
		tmp1 = *begin_list;
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if ((*cmp)(tmp1->data, tmp2->data) > 0)
			{
				ft_swap(&tmp1, &tmp2);
				i = 1;
			}
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	}
}