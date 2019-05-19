/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 01:51:43 by yelazrak          #+#    #+#             */
/*   Updated: 2019/05/19 02:18:38 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls1.h"

void print_perms(mode_t st,char *t)
{
   // char perms[11];
    if(st && S_ISREG(st)) ft_putchar('-');
    else if(st && S_ISDIR(st)) ft_putchar('d');
    else if(st && S_ISFIFO(st)) ft_putchar('|');
    else if(st && S_ISSOCK(st)) ft_putchar('s');
    else if(st && S_ISCHR(st)) ft_putchar('c');
    else if(st && S_ISBLK(st)) ft_putchar('b');
    else ft_putchar('l');  // S_ISLNK
    (st & S_IRUSR) ? ft_putchar('r'):ft_putchar('-');
    (st & S_IWUSR) ? ft_putchar('w'):ft_putchar('-');
    if (!(st & S_ISUID))
        ft_putchar ( (st & S_IXUSR) ? 'x' : '-');
    else
    {
        if (st & S_IXUSR)
            ft_putchar ('s');
        else
            ft_putchar ('S');
    }
   // (st & S_IXUSR) ? ft_putchar('x'):ft_putchar('-');
    (st & S_IRGRP) ? ft_putchar('r'):ft_putchar('-');
    (st & S_IWGRP) ? ft_putchar('w'):ft_putchar('-');
    if (!(st & S_ISGID))
        ft_putchar  ( (st & S_IXGRP) ? 'x' :'-');
    else
    {
        if (st & S_IXGRP)
            ft_putchar ('s');
        else
            ft_putchar ('S');
    }
    //(st & S_IXGRP) ? ft_putchar('x'):ft_putchar('-');
    (st & S_IROTH) ? ft_putchar('r'):ft_putchar('-');
    (st & S_IWOTH) ? ft_putchar('w'):ft_putchar('-');
    if (!(st & S_ISVTX))
    ft_putchar ( (st & S_IXOTH) ? 'x' : '-');
    else
    {
        if (st & S_IXOTH)
            ft_putchar ('t');
        else
            ft_putchar ('T');
    }
    ft_acl(t);
    //(st & S_IXOTH) ? ft_putchar('x'):ft_putchar('-');

}

void    ls_r2(char * path,char *x,int flag)
{
    //(void)flag;
     struct stat    sst;
        char *t;
         //if(x[0] != '.' || (flag & A) == A) 
        if(((ft_strcmp(x,".") != 0) && (ft_strcmp(x,"..") != 0)))
        {
            
            t = ft_strnew(0);
            t = ft_strjoin(t,path);
            t = ft_strjoin(t,"/");
            t = ft_strjoin(t,path);
            lstat(t,&sst);
            if (sst.st_mode && S_ISDIR(sst.st_mode))
                {
                    printf("\n%s:\n",t);
                    ls_r(t,flag);
                }
        }
}

void ft_print_r2(t_ls1 *tmp,char *x,int flag)
{
    if (tmp->next)
        ft_print_r2(tmp->next,x,flag);
    ls_r2(x,tmp->p,flag);
    
}

void    name_from_path(mode_t d,char *path,int flag)
{
    int i;

    i = 0;
    i = ft_strlen(path);
    while(path[i] != '/')
        i--;
    i++;
    if (d == 0)
        ft_putstr(&path[i]);
    else
        ft_col(d,&path[i],flag);
}

void    puterror(char *path)
{
     ft_putstr("ls: ");
        name_from_path(0,path,0);
        ft_putstr(": ");
        perror(NULL);
}

char *ft_stat(char *path,char *p)
{
    //struct stat    sst;
    char *t;

    t = ft_strdup(path);
    t = ft_strjoin(t,"/");
    t = ft_strjoin(t,p);
    //lstat(t,sst);
    return (t);
}

void    ls_r(char * path,int flag)
{
   t_ls1 *tmp;
   struct stat    sst;
    char *t;
    t_d d;

    if ((flag & L) == L)
         ls_l(path,flag);
    else
        ls(path,flag);
    tmp = lls(path,&d,flag);
    if (tmp == NULL)
    {
        
        return ;
    }    
    while ( tmp!= NULL)
    {
        if(((ft_strcmp(tmp->p,".") != 0) && (ft_strcmp(tmp->p,"..") != 0)))
        {
            t = ft_stat(path,tmp->p);
            lstat(t,&sst);
            if (S_ISDIR(sst.st_mode))
                {
                     ft_putstr("\n");
                    ft_putendl(t);
                    if ((sst.st_mode & S_IRUSR) && (sst.st_mode & S_IXUSR))
                         ls_r(t,flag);
                }
        }
        tmp = tmp->next;
        free(t);
    }
}

void    ft_readlink(char *path,mode_t d, int flag,int f)
{
    char t[1024];

    
    if (S_ISLNK(d))
    {
       // t = ft_strnew(1024);
        ft_bzero(t, 1024);
        readlink(path, t, 1024);
        //ft_putstr(path);
         name_from_path(d,path,flag);
        ft_putstr(" -> ");
        ft_putstr(t);
        ft_putstr("\n");
        // ft_col(d,t);
      // printf("%s -> %s\n",path,t);
        //free(t);
    }
    else if (f == 1)
    {
        //ft_putstr(path);
        name_from_path(d,path,flag);
        ft_putstr("\n");

    }
    else
    {
        
        name_from_path(d,path,flag);
         ft_putstr("\n");
        
    }
}
 int		len(int n)
{
	int i;

	i = 0;
    if (n == 0)
        return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void    ft_put_1(int t,int i)
{
    int j;

    j = len(t); 
     
    while (j < i)
    {
        ft_putchar(' ');
        j++;
    }
    ft_putnbr(t);
  
}
void    ft_put_2(char *t,int i)
{
    int j;

    j = ft_strlen(t);
     ft_putstr(t);
    while (j < i)
    {
        ft_putchar(' ');
        j++;
    }
   
}

 void ft_col(mode_t x,char *t,int flag)
 {
     //(void)flag;
    //if((flag & G) == G)
   // {
        if (S_ISDIR(x) && ((flag & G) == G))
        {
            ft_putstr("\033[0;34m");
            ft_putstr(t);
        // ft_putendl(ft_strjoin("\033[0;34m",t));
            ft_putstr("\033[0m");
        }
        else if (S_ISLNK(x) && ((flag & G) == G))
        {
            ft_putstr("\033[0;33m");
             ft_putstr(t);
             // ft_putendl(ft_strjoin("\033[0;33m",t));
               ft_putstr("\033[0m");
         }
         else if (S_ISREG(x) && (x & S_IXOTH) && ((flag & G) == G))
        {
           ft_putstr("\033[0;31m");
              ft_putstr(t);
             ft_putstr("\033[0m");
        }
     else
     {
          ft_putstr(t);
     }
     
     
 }

int ft_8(int l)
{
    int i;
     i = 0;

     while (i <= l)
     {
        i += 8;
         
     }
     return (i);

}

 char **ft_ctab(t_ls1 *temp, int *m)
 {
     int i;
     int j;
     t_ls1 *alst;
     char **t;

     i = 0;
     alst = temp;
     j = 0;
    while (alst)
    {
       alst = alst->next;
       j++;
    }
   if (!(t = (char **)malloc(sizeof(char *)* j)))
        return (NULL);
    while (i < j)
    {
        t[i] = ft_strdup(temp->p);
        i++;
        temp = temp->next;
    }
    *m = j;
   // printf("%s\n",t[0]);
    return (t);
}

void ft_printbonus(t_ls1 *alst,int n)
{

     struct winsize max;
    int a;
    int b;
    int c;
    int i;
    int j;
    int m;
    char **t;


    m = 0;
    if (!(t = ft_ctab(alst,&m)))
    {
        
        return ;
    }
        //ft_putendl("jhihdhfhih");
    ioctl(0, TIOCGWINSZ , &max);
    a = max.ws_col /n;
    b = m / a;
    if (m  % a != 0)
        b++;
    c = m /b;
     if (m % c!= 0)
        c++;
        i = 0;
    while(i < b)
    {
        j = i;
        while (j < m )
        {
            ft_put_2(t[j],n);
            j += b;
        }
        ft_putchar('\n');
        i++;
    }
}

/*void ft_mjr_mnr(dev_t dev,int mjmax,int mnmax)
{
    ft_put_1(major(dev),len(d->mjmax));
    ft_put_1(minor(dev),len(d->mnmax));

    ft_putnbr((int)major(dev));
    ft_putstr("...");
    ft_putnbr((int)minor(dev));
}*/
void ft_lsl(char *path, struct stat sbuf,t_d *d,int flag)
{
    (void)flag;
     struct passwd * pwentp;
     struct group  * grpt;
     int a = 0;
                print_perms(sbuf.st_mode,path);
                ft_put_1((int)sbuf.st_nlink,len(d->lmax) +1);
                  ft_putstr(" "); 
                 if ((pwentp = getpwuid(sbuf.st_uid)) && (flag & G1) != G1)
                {
                     ft_put_2(pwentp->pw_name,d->pwmax);
                     ft_putstr("  ");
                }
              
                if ((grpt = getgrgid (sbuf.st_gid)))
                {
                     ft_put_2(grpt->gr_name,d->grmax);
                     ft_putstr("  ");
                }
                if (S_ISCHR(sbuf.st_mode) || S_ISBLK(sbuf.st_mode))
                {
                    ft_put_1(major(sbuf.st_rdev),len(d->mjmax));
                    //ft_putnbr(d->mjmax);
                    ft_putstr(", ");
                    //ft_putnbr(d->mnmax);
                    ft_put_1(minor(sbuf.st_rdev),len(d->mnmax));
                }
                else
                {
                    if (len(d->mnmax))
                    {
                        a = len(d->mnmax) + len(d->mjmax) + 2;
                    }
                    else
                    {
                        a = len(d->smax);
                    }
                    
                     ft_put_1((int)sbuf.st_size,a);
                }
               
                ft_putstr(" ");
                ft_putstr(ft_strsub(ctime(&sbuf.st_mtime),4,12));
                 ft_putstr(" "); 
                ft_readlink(path,sbuf.st_mode,sbuf.st_size,d->file);
}  

void    ft_0(t_d *d)
{
       d->pmax = 0;
       d->grmax = 0;
       d->pwmax = 0;
       d->smax = 0;
       d->mnmax = 0;
       d->mjmax = 0;
       d->bsmax = 0;
       d->total = 0;
       d->file = 0;
       d->path = NULL;

}

void ft_acl(char *path)
  {
    acl_t acl = NULL;
    int t;
    int a;

    t  = 0;
    a = 0;
    acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
    t = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
    if (t > 0)
    {
        ft_putchar('@');
        a++;
    }  
    else if (acl != NULL)
    { 
        ft_putchar('+');
        a++;
    }
    if (a == 0)
        ft_putchar(' ');
 }

void ls_l(char path[], int flag) 
{
     t_ls1 *tmp;
     t_d d;
    struct stat sbuf;
    char t[111111];
    
    ft_0(&d);
    if (!(tmp = lls(path,&d, flag)))
        return ;
    ft_putstr("total ");
    ft_putnbr(d.total);
    ft_putchar('\n');  
        while(tmp!= NULL)
        {
            ft_strcpy(t,path);
            ft_strcat(t,"/");
            ft_strcat(t,tmp->p);
            lstat(t,&sbuf);
            ft_lsl(t,sbuf,&d, flag);
           tmp = tmp->next;
        }
    //}
    
   
}