/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 01:53:50 by yelazrak          #+#    #+#             */
/*   Updated: 2019/05/13 00:07:40 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls1.h"


t_ls1 *ft_alstnew(char *t, int flag)
{
    (void)flag;
    t_ls1   *new;
    struct stat ss1;

    lstat(t,&ss1); 
    if (!(new = (t_ls1*)malloc(sizeof(t_ls1))))
        return (NULL);
    new->p = ft_strdup(t);
   /* ((flag & T )== T) ? */new->t = ss1.st_mtime ;/*: 0;
    ((flag & S) == S) ?*/ new->s = ss1.st_size ;/*: 0;
    ((flag & S1) == S1) */ new->bs = ss1.st_blksize ;/*: 0;*/
    new->next = NULL;
    return (new);
}

// t_ls1 *ft_search(t_ls1 **alst, char *t, int flag)
// {
// 	t_ls1 *temp;
// 	//t_ls1 *new;

	
// 	if (*alst)
// 	{
//         temp = *alst;
// 		while (temp)
// 		{
// 			temp = temp->next;
// 		}
// 		temp = ft_alstnew(t, flag);
// 		// new->next = *alst;
// 		// *alst = new;
// 		return (*alst);
// 	}
// 	*alst = ft_alstnew(t, flag);
// 	//new = *alst;
// 	return (*alst);
// }

t_ls1 *ft_search(t_ls1 **alst, char *t, int flag)
{
	t_ls1 *temp;
	t_ls1 *new;

	
	if (*alst)
	{
        temp = *alst;
		while (temp)
		{
			temp = temp->next;
		}
		new = ft_alstnew(t, flag);
		new->next = *alst;
		*alst = new;
		return (*alst);
	}
	*alst = ft_alstnew(t, flag);
	new = *alst;
	return (*alst);
}

void    ft_print_r(t_ls1 *tmp)
{
    t_ls1 *lst;

    lst = tmp;
    while (lst)
    {
        printf("%s      \n",lst->p);
        lst = lst->next;
    }
}

void    ft_print_2(t_ls1 *tmp)
{
    if (tmp->next)
        ft_print_2(tmp->next);
    printf("%s      \n",tmp->p);

}



static int vef(char *s, int *a)
{
    int i;
    int *t;


    i = 0;
    t = a;
    while (s[++i])
    {
        if (s[i] == 'l')
            *t |= L;
        else if (s[i] == 'r')
            *t |= R1;
        else if (s[i] == 'a')
            *t |= A;
        else if (s[i] == 'R')
            *t |= R;
        else if (s[i] == 't')
            *t |= T;
        else if (s[i] == 'f')
            *t |= F1;
        else if (s[i] == 'F')
            *t |= F;
        else if (s[i] == 'S')
            *t |= S;
        else
            return (-1);
    }
    return (1);
}

void swap22(char  **x,char **y)
{
    char *tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
    
}

void bubbleSort_2(char *arr[], int n) 
{ 
   int i, j; 
   int swapped; 

  i = 1;
    while (i < n - 1)
   { 
     swapped = 0; 
     j = 1;
     while (j < n - i -1)
     { 
        if (ft_strcmp(arr[j],arr[j + 1]) > 0)
        { 
           swap22(&arr[j], &arr[j+1]); 
           swapped = 1; 
        } 
        j++;
     } 
     if (swapped == 0) 
        break; 
    i++;
   } 
}

t_ls1   *ls_open(int ac ,char **av, int *k)
{
    DIR *dip;
    t_ls1   *tmp;
    int i;

    tmp = NULL;
    i = 1;
   
    while ( i < ac)
    {
        if (av[i][0] == '-' && av[i][1] != '-')
        {
            if (vef(av[i],k) == -1)
                break;    
        }
        else
            break;
        
        i++;
    }
     if (i == ac)
        ft_search(&tmp,".", *k);
    bubbleSort_2(av,ac);
    while ( i < ac)
    {
        if (( dip = opendir(av[i])) == NULL)
            printf("ls: %s: No such file or directory\n",av[i]);
        else
        {
             ft_search(&tmp,av[i], *k);
             closedir(dip);
        }
           
        i++;
    }   
    return (tmp);
}