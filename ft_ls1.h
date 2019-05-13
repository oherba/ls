/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 23:34:53 by yelazrak          #+#    #+#             */
/*   Updated: 2019/05/12 22:29:31 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_LS1_H
#define FT_LS1_H

#include <stdio.h>
# include "libft/libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h> 
#include <time.h> 
#include <stdlib.h>

#include <sys/types.h>
#include <grp.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
//#define	S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)	/* 
#include <stdio.h>

#define	FLAGS	0b00000000000
#define	L   	0b00000000001
#define	R1		0b00000000010
#define	A		0b00000000100
#define	R		0b00000001000
#define	T		0b00000010000
#define	F1		0b00000100000
#define	F	    0b00001000000
#define	S		0b00010000000
#define	S1		0b00100000000


// #define	S_ISl(m)	(((L) & m) == L)
// #define	S_ISr(m)	(((R1) & m) == R1)
// #define	S_ISr(m)	(((A) & m) == A)
// #define	S_ISr(m)	(((R) & m) == R)
// #define	S_ISr(m)	(((T) & m) == T)
// #define	S_ISr(m)	(((F1) & m) == F1)
// #define	S_ISr(m)	(((F) & m) == F)
// #define	S_ISr(m)	(((S) & sm) == S)

typedef struct s_ls1
{
    char *p;
    int t;
    int s;
    int bs ;
    struct s_ls1 *next;
}               t_ls1;

void print_perms(mode_t st);
void    ls_r(char * path, int flag);
void ls_l(char path[], int flag);
t_ls1 *ft_alstnew(char *y, int flag);
t_ls1 *ft_search(t_ls1 **alst, char *y, int flag);
void    ft_print_r(t_ls1 *tmp);
void    ft_print_2(t_ls1 *tmp);
void swap(int *x,int *y);
void quicksort(int list[],int m,int n);
void ls(char path[],int flag);
t_ls1 *lls(char path[],int flag);
t_ls1   *ls_open(int ac ,char **av ,int *k);
void    ft_readlink(char *path,mode_t d, size_t l);
void ft_lsl(char *path, struct stat sbuf, int flag);


#endif