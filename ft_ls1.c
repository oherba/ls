/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:08:17 by yelazrak          #+#    #+#             */
/*   Updated: 2019/05/14 13:53:32 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls1.h"





// // void ft_sort(char **av, int ac, int (*f)(char *, char *))
// // {
// //     int i;
// //     int a;

// //     a = 0;
// //     while (!a)
// //     {
// //         a = 0;
// //         i  = 0;
// //         while(i < ac)
// //         {
// //             if (f(av[i], av[i + 1]) > 0)
// //                 {
// //                     swap(&av[i], &av[i + 1]);
// //                     a = 1;
// //                 }
// //             i++;
// //         }
// //     }
// // }

// void swap(char  **x,char **y)
// {
//     char *temp;
//     temp = *x;
//     *x = *y;
//     *y = temp;
// }
 
// int choose_pivot(int i,int j )
// {
//     return((i+j) /2);
// }
 
// void quicksort(char *av[],int m ,int n)
// {
//     int i,j,k;
//     char *key;
//     //int m;

//    // m = 1;
//     if( m < n)
//     {
//         k = choose_pivot(m,n);
//         swap(&av[m],&av[k]);
//         key = av[m];
//         i = m+1;
//         j = n;
//         while(i <= j)
//         {
//             while((i <= n) && ft_strcmp(av[i],key) <= 0)
//             //(av[i] <= key))
//                 i++;
//             while((j >= m) && ft_strcmp(av[j],key) > 0)
//             //(av[j] > key))
//                 j--;
//             if( i < j)
//                 swap(&av[i],&av[j]);
//         }
//         /* swap two elements */
//         swap(&av[m],&av[j]);
 
//         /* recursively sort the lesser av */
//         quicksort(av,m,j-1);
//         quicksort(av,j+1,n);
//     }
//     ft_putendl("yassine");
// }


// t_ls1 *ft_alstnew(char *t)
// {
//     t_ls1   *new;
      
//     new = (t_ls1*)malloc(sizeof(t_ls1)); 
//     new->t = ft_strdup(t);
//     new->next = NULL;
//     return (new);
// }

// void ft_alstadd(t_ls1 **lst, char *t)
// {
//     if (*lst)
//         (*lst)->next = ft_alstnew(t);
//     else
//         *lst = ft_alstnew(t);
// }

// t_ls1   *ls_open(int ac ,char **av)
// {
//     DIR *dip;
//     t_ls1   *tmp;  
//     int i;

//     tmp = NULL;
//     i = 1;
//     if (ac == 1)
//         ft_alstadd(&tmp,".");
//     while ( i < ac)
//     {
//         if (( dip = opendir(av[i])) == NULL)
//             printf("ls: %s: No such file or directory\n",av[i]);
//         else
//             ft_alstadd(&tmp,av[i]);
//         i++;
//     }
//     return (tmp);
// }

// void    ft_print(t_ls1 *lst)
// {
//     while (lst)
//     {
//         printf("%s\n",lst->t);
//         lst= lst->next;
//     }
// }

//  void   ls(t_ls1  *lst)
//  {
//      t_ls1 *tmp;
//      DIR *dip;
//     struct dirent *dit;
    
//     tmp = lst;
//     while (tmp)
//     {
//         //printf("%s:\n",tmp->t);
//         dip = opendir(tmp->t);
//          while ((dit = readdir(dip)) != NULL)
//             {
//                 if (dit->d_name[0] != '.')
//                  {
//                     printf("%-11s",dit->d_name);
//                  }
//              }
//         closedir(dip);
//         tmp = tmp->next;
//     }
//  }


// // int main(int argc, char **argv)
// // {
// //     t_ls1   *lst;
// //     int i;

// //     i = 1;
// //     bubbleSort(argv, argc,&ft_strcmp);
// //     lst = ls_open(argc,argv);
// //     ls(lst);

// //    return (0);
// // }

// // int main(int argc, char  **argv)
// // {
// //     int i= 1;

// //     quicksort(argv,1,argc);
// //     while (i < argc)
// //     {
// //         ft_putendl(argv[i]);
// //         i++;
// //     }

// //     return (0);

// // }


static int partition(char **a, int left, int right)
{
    char *pivot; 
    int i, j;
    char *t;

    pivot = a[left];
    i = left ; j = right - 1;
    while (1)
    {
       while (ft_strcmp(a[i],pivot) < 0 && i < right)
        i++;
       while (ft_strcmp(a[j],pivot) > 0 ) 
       //(j > left))
        j--;
        if (i >= j) 
            break;
        t = a[i]; 
        a[i] = a[j]; 
        a[j] = t;
    }
    t = a[left]; 
    a[left] = a[j]; 
    a[j] = t;
    return j;
}

 void quickSort(char **a, int left, int right)
{
    int j;
    if (left < right)
    {
        j = partition(a, left, right);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}


int main(int argc ,char **argv)
{
    int i;

    i = 1;
    //char arr[] = "bacgd";
    //ft_putendl(arr);
    quickSort(argv, 1, argc - 1);
    //ft_putendl(arr);
     while (i < argc)
    {
        ft_putendl(argv[i]);
        i++;
    }
    return (0);
    //system("pause");
}