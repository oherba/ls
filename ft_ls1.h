/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 23:34:53 by yelazrak          #+#    #+#             */
/*   Updated: 2019/05/19 15:02:41 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_LS1_H
#define FT_LS1_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <stdio.h>
#include <sys/ioctl.h>
# include "libft/libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <errno.h>
#include <stdio.h> 
#include <time.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <grp.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

#define	FLAGS	0b00000000000000
#define	L   	0b00000000000001
#define	R1		0b00000000000010
#define	A		0b00000000000100
#define	R		0b00000000001000
#define	T		0b00000000010000
#define	F1		0b00000000100000
#define	F	    0b00000001000000
#define	S		0b00000010000000
#define	S1		0b00000100000000
#define	G1		0b00001000000000
#define	U		0b00010000000000
#define	D		0b00100000000000
#define	G		0b01000000000000
#define	C		0b10000000000000


typedef struct s_d
{
    int bsmax;
    int smax;
    int pmax;
    int grmax;
    int pwmax;
    int total;
     int lmax;
    char *path;
    int file;
    int mjmax;
    int mnmax;
}              t_d;

typedef struct s_ls1
{
    char *p;
    int t;
    int s;
    int bs;
    int ln;
    char *gr;
    char *pw;
    int  major;
    int    minor;
    mode_t st;
    struct s_ls1 *next;
}               t_ls1;

void print_perms(mode_t st,char *t);
void    ls_r(char * path, int flag);
void ls_l(char path[], int flag);
t_ls1 *ft_alstnew(char *y,t_d *d ,int flag);
t_ls1 *ft_search(t_ls1 **alst, t_d *d,char *y, int flag);
void    ft_print_r(t_ls1 *tmp,t_d *d);
void    ft_print_2(t_ls1 *tmp);
void swap(int *x,int *y);

//void ft_lsl(char *path, struct stat sbuf,t_d *d,int flag);
void quicksort(int list[],int m,int n);
void ls(char path[],int flag);
t_ls1 *lls(char path[],t_d *d,int flag);
t_ls1   *ls_open(int ac ,char **av ,int *k);
void    ft_readlink(char *path,mode_t d, int l,int f);
void ft_lsl(char *path, struct stat sbuf, t_d *d,int flag);
void MergeSort(t_ls1** head, int flag);
void	ft_sort(char **t,int m,int n);
int		len(int n);
void    ft_0(t_d *d);
void ft_acl(char *path);
 void ft_col(mode_t s,char *t,int flag);
void    ft_put_2(char *t,int i);
int ft_8(int l);
void    puterror(char *path);
//char *ft_stat( struct stat *sst,char *path,char *p);
void ft_printbonus(t_ls1 *alst,int n);




#endif