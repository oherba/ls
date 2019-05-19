/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 01:53:50 by yelazrak          #+#    #+#             */
/*   Updated: 2019/05/19 02:13:36 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls1.h"

void    ft_max(t_d *d,t_ls1 *new,int flag)
{
if ((d->bsmax < new->bs)) 
        d->bsmax = new->bs;
if ((d->smax < new->s))
         d->smax = new->s;
if (d->pmax < (int)ft_strlen(new->p)) 
         d->pmax  = ft_strlen(new->p);

if (((flag & L) == L))
   {

        if(((int)ft_strlen(new->pw)) > d->pwmax)
                d->pwmax = ft_strlen(new->pw);
        if ((d->grmax < (int)ft_strlen(new->gr)))
                d->grmax  = ft_strlen(new->gr) ;
         if ((d->lmax < (new->ln)))
                d->lmax  = (new->ln) ;
        if ((d->mjmax < (new->major)))
                d->mjmax  = (new->major) ;
        //printf("mj =%d\n",d->mjmax);
       
        if ((d->mnmax < (new->minor)))
                d->mnmax  = (new->minor) ;
        //printf("mn =%d\n",d->mnmax);
   }

}
char *gid(gid_t t)
{
  
    struct group  *grpt;
    grpt = getgrgid(t);

    return(grpt->gr_name);
}
char *gid2(uid_t t)
{
    struct passwd *pw;
    pw = getpwuid(t);
    return(pw->pw_name);

}
t_ls1 *ft_alstnew(char *t, t_d *d,int flag)
{
    t_ls1   *new;
    struct stat ss1;
    char *g;
    char *k;
    if (d->path)
    {
        g = ft_strjoin(d->path,"/");
        k = ft_strjoin(g,t);
    }
    else
    {
        k = t;
    }

    if (0 >lstat(k,&ss1))
    return (NULL);
    if (!(new = (t_ls1*)malloc(sizeof(t_ls1))))
        return (NULL);
    new->minor = 0;
    new->major = 0;
    new->st = ss1.st_mode;
    new->p = ft_strdup(t);
    if ((((flag & T )== T) || ((flag & L) == L)) && ((flag & U )!= U))
         new->t = ss1.st_mtime;
    else
    {
      new->t = ss1.st_atime;
    }
    if (S_ISCHR(ss1.st_mode) || S_ISBLK(ss1.st_mode))
    {
        new->major = major(ss1.st_rdev);
       
        new->minor = minor(ss1.st_rdev);
        // printf("new->min =%d\n",new->minor);
    }
    if (((flag & S) == S)|| ((flag & L) == L)) 
            new->s = ss1.st_size;
    
    if (((flag & S1) == S1) || ((flag & L) == L)) 
         new->bs = ss1.st_blocks;

    if (((flag & L) == L))
    {
        
            new->gr = ft_strdup(gid(ss1.st_gid));
           
            new->pw =  ft_strdup(gid2(ss1.st_uid)) ;
           
            new->ln = ss1.st_nlink;
    }  

    ft_max(d,new, flag);

    d->total += new->bs;
    
    new->next = NULL;
    return (new);
}

t_ls1 *ft_search(t_ls1 **alst,t_d *d, char *t, int flag)
{
	t_ls1 *temp;
	 temp = *alst;
	if (*alst)
	{
        while (temp->next)
            temp = temp->next;
		temp->next = ft_alstnew(t,d, flag);
		return (temp);
	}
	*alst = ft_alstnew(t,d, flag);
	return (*alst);
}



// void ft_size(int *i,int *j,t_ls1 *lst)
// {
//     int b;
//      struct winsize max; 
//      int a;
//      int k;
// j++;
//      k = 0;
//      b = 0;
//      a = 1;
//      while (lst)
//      {
//          b++;
//          lst = lst->next;
//      }
//      while (a < max.ws_col)
//      {
//          a *= *i;
//          k++;
//      }
//      a =  max.ws_row/a;
    
// }  
// void    ft_print_r(t_ls1 *tmp,t_d *d)
// {
//     t_ls1 *lst;
//     //int i;
  
//     struct winsize max;
//     lst = tmp;
   

//     ioctl(0, TIOCGWINSZ , &max);
//     //i = ft_8(d->pmax);
  
//     //printf ("columns %d\n", max.ws_col);
//     //void(*d);
//     //ft_8(
//         d->pmax++;
//     while (lst)
//     {
//         ft_put_2(lst->p,11);
//         lst = lst->next;
//     }
// }

void    ft_print_2(t_ls1 *tmp)
{
    if (tmp->next)
        ft_print_2(tmp->next);
    printf("%s      \n",tmp->p);

}






static int vef(char *s, int *t)
{
    int i;

    i = 0;
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
        else if (s[i] == 'G')
            *t |= G;
        else if (s[i] == 'u')
            *t |= U;
        else if (s[i] == 'd')
            *t |= D;
        else if (s[i] == 'g')
        {
             *t |= G1;
             *t |= L;
        }
        else
        {
            ft_putstr("ls: illegal option -- ");
                ft_putchar(s[i]);
                ft_putchar('\n');
            return (-1);
        }
            
    }
    return (1);
}

// void swap22(char  **x,char **y)
// {
//     char *tmp;
//     tmp = *x;
//     *x = *y;
//     *y = tmp;
    
// }

// void Sort_2(char *a[], int m, int n) 
// {
//     int i;
//     int j;
//     char *key;


//     if (i < j)
//     {
//         i  = m + 1;
//         j = n;
//         key = a[m];
//         while ( i < j)
//         {
//             while (ft_strcmcp(a[i],key) >= 0 && i <= n)
//                 i++;
//             while (ft_strcmp(a[j],key) >= 0 && j >= m)
//                 j++;
//             if (i < j)
//                 swap22(a[i],a[j]);
//         }
//         swap22(key,a[j]);
//     }
//     Sort_2(a,m,j - 1);
//     Sort_2(a,j + 1,n); 
// }

int ls_param(int ac ,char **av, int *k)
{
    int i;
    
    
    i = 1;
    while ( i < ac)
    {
        if (av[i][0] == '-' && av[i][1] != '-')
        {
            if (vef(av[i],k) == -1)
            {
                
                ft_putendl("usage: ls [-ugltsarRfd1] [file ...]");
                exit(1);   
            }
                 
        }
        else
            break;
        
        i++;
    }
    return (i);
}

 void ft_file(t_d *d,t_ls1 *lst,int flag)
 {
    struct stat ss;
    int n;

    if (lst)
        {
            if ((flag & L) == L)
            { 
                    while(lst)
                    {
                          
                        lstat(lst->p,&ss);
                        ft_lsl(lst->p,ss,d, flag);
                        lst = lst->next;
                    }
                

            }
            else
            {
                  n = ft_8(d->pmax);
                ft_printbonus(lst ,n);
            }
            
           d->file = 0;

        }
 }
    //bubbleSort_2(av,ac);
t_ls1 *ls_open(int ac, char **av,int *k)
{
     struct stat ssb;
     //int t[111];
     t_ls1   *tmp;
   //   t_ls1   *tmp_2;
     t_ls1    *file;
     int i;
     t_d d;
     t_d d_2;

    tmp = NULL;
    ft_0(&d);
     ft_0(&d_2);
    i = ls_param(ac,av,k);
     ft_sort(av, i,ac - 1);
    if (i == ac)
        ft_search(&tmp,&d,".", *k);
    while (av[i])
    {
        if ( 0 > lstat(av[i],&ssb))
        {
            ft_putstr("ls: ");
            ft_putstr(av[i]);
            ft_putendl(": No such file or directory"); 
        }
        else if (S_ISDIR(ssb.st_mode) && (*k & D) != D)
            ft_search(&tmp,&d,av[i], *k);  
        else
        {
            d.path = ft_strdup("."); 
            ft_search(&file,&d_2,av[i], *k); 
        }
        i++;
    }
    if (file)
    {
        d_2.file = 1;
        ft_file(&d_2,file,*k);
        ft_putchar('\n');
    }
    return (tmp);
}