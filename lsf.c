/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:47:31 by yelazrak          #+#    #+#             */
/*   Updated: 2019/05/19 15:53:15 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls1.h"

t_ls1 *lls(char path[],t_d *d,int flag)
{
    DIR * dir;
    struct dirent * file;
    t_ls1 *tmp = NULL;

    d->path = ft_strdup(path);
    if (!(dir = opendir(path)))
    {
        

        return (NULL);
    }
       
    else
    { 
         while((file=readdir(dir)) != NULL) 
            {
                if(file->d_name[0] != '.' || (flag & A) == A) 
                    ft_search(&tmp,d, (char *)file->d_name,flag);
            }
        if((flag & F1) != F1)
            MergeSort(&tmp,flag);
        free(file);
        closedir(dir);
    }
    return (tmp);
}


void ls(char path[], int flag) 
{
    t_ls1 *tmp_2;
   t_d d;
  
   int n;

   ft_0(&d);
    tmp_2 = lls(path,&d,flag);
    if (tmp_2 == NULL)
    {
        puterror(path);
        return ;
    }
    if ((flag & C) != C)
    {   
        n = ft_8(d.pmax);
        ft_printbonus(tmp_2 ,n);

    } 
    else
    {
         while (tmp_2)
            {
                ft_putendl(tmp_2->p);
                tmp_2 = tmp_2->next;
            }
    }

   

}

int main(int argc ,char **argv)
{
    t_ls1 *lst;
     t_ls1 *mlst;
    int k;
    int g;
    // t_d d;
    

    k = 0;
    g = 0;
    lst = NULL;
    
    if (!(lst = ls_open(argc,argv, &k)))
        return (0);
    mlst = lst;
   if ((k & F1) == F1)
        k |= A;
    if ((k & R) == R)
    {
        // if (file)
        // {
        //     ft_printbonus(file ,16);
        // }
       
        if (lst->next != NULL)
            g = 1;
        while (lst)
        {
             if (g)
             {
                 ft_putstr(lst->p);
                 ft_putstr(":\n");

             }
                //printf("%s:\n",lst->p);
                
             ls_r(lst->p,k);
             lst = lst->next;
        }
    }
    else if((k & L) == L)
    {
        // if (file)
        // {
        //     lstat(file->p,&sbuf);
        //     ft_lsl(file->p,sbuf,&d, k);
        // }
        if (lst->next != NULL)
            g = 1;
        while (lst)
        {
             if (g)
             {
                    ft_putstr(lst->p);
                 ft_putstr(":\n");
             }
               //printf("%s:\n",lst->p);                        
                ls_l(lst->p,k);
                 //ls_l("x",k);
             lst = lst->next;
        }
    }
    else
    {
         if (lst->next != NULL)
            g = 1;
        while (lst)
        {
            if (g)
            {
                ft_putstr(lst->p);
                ft_putstr(":\n");
            }
                //printf("%s:\n",lst->p);
            ls(lst->p,k);
            lst = lst->next;
        }
    } 
    return (0);
}