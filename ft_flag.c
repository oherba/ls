/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 01:51:43 by yelazrak          #+#    #+#             */
/*   Updated: 2019/05/12 22:29:32 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls1.h"

void print_perms(mode_t st)
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
    (st & S_IXUSR) ? ft_putchar('x'):ft_putchar('-');
    (st & S_IRGRP) ? ft_putchar('r'):ft_putchar('-');
    (st & S_IWGRP) ? ft_putchar('w'):ft_putchar('-');
    (st & S_IXGRP) ? ft_putchar('x'):ft_putchar('-');
    (st & S_IROTH) ? ft_putchar('r'):ft_putchar('-');
    (st & S_IWOTH) ? ft_putchar('w'):ft_putchar('-');
    (st & S_IXOTH) ? ft_putchar('x'):ft_putchar('-');

}

void    ls_r2(char * path,char *x,int flag)
{
    //(void)flag;
     struct stat    sst;
        char t[128];
         //if(x[0] != '.' || (flag & A) == A) 
        if(((ft_strcmp(x,".") != 0) && (ft_strcmp(x,"..") != 0)))
        {
            ft_strcpy(t,path);
            ft_strcat(t,"/");
            ft_strcat(t,x);
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

void    ls_r(char * path,int flag)
{
   t_ls1 *tmp;
     struct stat    sst;
     char t[128];

    if ((flag & L) == L)
         ls_l(path,flag);
    else
        ls(path,flag);
    printf("\n");
    tmp = lls(path,flag);
    //ft_putendl("---------");
    //ft_print_2(tmp);
   // ft_print_r2(tmp,path,flag);
    while ( tmp!= NULL)
    {

    

        if(((ft_strcmp(tmp->p,".") != 0) && (ft_strcmp(tmp->p,"..") != 0)))
        {
            ft_strcpy(t,path);
            ft_strcat(t,"/");
            ft_strcat(t,tmp->p);
            lstat(t,&sst);
            //printf("|%s|\n",t);
            //ft_lsl(t,flag);
            if (sst.st_mode && S_ISDIR(sst.st_mode))
                {
                    printf("\n%s:\n",t);
                    ls_r(t,flag);
                }
        }
        tmp = tmp->next;
    }
}

// void ls_l(char path[], int flag) 
// {
//      t_ls1 *tmp;
//     struct stat sbuf;
//     struct passwd * pwentp;
//     struct group  * grpt;
//     tmp = lls(path, flag);
//     while(tmp!= NULL)
//      {
//          lstat(tmp->p, &sbuf);
//         if (tmp->p[0]!='.' || ((flag & A) == A))
//         {
                
//                 print_perms(sbuf.st_mode);
//                 printf("%8d ", (int)sbuf.st_nlink);
//                 if ((pwentp = getpwuid(sbuf.st_uid)))
//                     printf("%6s   ", pwentp->pw_name);
//                // else
//                     //printf("%8d", sbuf.st_uid);
 
//                 if ((grpt = getgrgid (sbuf.st_gid)))
//                     printf("%8s", grpt->gr_name);
//                 //else
//                    // printf("%8d", sbuf.st_gid);
//                 printf("%8d  ", (int)sbuf.st_size);
//                 printf("%8s ",ft_strsub(ctime(&sbuf.st_mtime),4,12));
 
//                 printf("%-8s\n", tmp->p);
//         }  
//         tmp = tmp->next;
//     }
// }

void    ft_readlink(char *path,mode_t d, size_t l)
{
    char *t;
    if (S_ISLNK(d))
    {
        t = ft_strnew(l);
        readlink(path,t,l);
        printf("%s -> %s\n",path,t);
        free(t);

    }
    else
    {
        printf("%-8s\n", path);
    }
}

void ft_lsl(char *path, struct stat sbuf, int flag)
{
   // struct stat sbuf;
    struct passwd * pwentp;
    struct group  * grpt;
    (void)flag;

    //lstat(path, &sbuf);
        //if (path[0]!='.' || ((flag & A) == A))
        {
                
                print_perms(sbuf.st_mode);
                printf("%8d  ", (int)sbuf.st_nlink);
                if ((pwentp = getpwuid(sbuf.st_uid)))
                    printf("%8s   ", pwentp->pw_name);
                else
                    printf("%8d", sbuf.st_uid);
 
                if ((grpt = getgrgid (sbuf.st_gid)))
                    printf("%8s", grpt->gr_name);
                else
                    printf("%8d", sbuf.st_gid);
                printf("%8d  ", (int)sbuf.st_size);
                printf("%8s ",ft_strsub(ctime(&sbuf.st_mtime),4,12));
                ft_readlink(path,sbuf.st_mode,(int)sbuf.st_size);
                //printf("%-8s\n", "035454545");
        }
}  

// void    print_l(struct stat sbuf,int flag)
// {
//     if (lst->next)
//     {
//         print_l(lst->next, flag);
//     }
//     ft_lsl(lst->p,flag);
// }

void ls_l(char path[], int flag) 
{
     t_ls1 *tmp;
    struct stat sbuf;
    char t[128];
    tmp = lls(path, flag);
    // if (((flag & R1) == R1 && (flag & F1) != F1) || (flag & T) == T)
    // {
    //      while(tmp!= NULL)
    //     {
    //         ft_lsl(tmp->p,flag);
    //         tmp = tmp->next;
    //     }
    //     // print_l(tmp, flag);
    // }
    // else
    // {
         //print_l(tmp, flag);
         
        while(tmp!= NULL)
        {
            ft_strcpy(t,path);
            ft_strcat(t,"/");
            ft_strcat(t,tmp->p);
            lstat(t,&sbuf);
            ft_lsl(tmp->p,sbuf,flag);
          // printf("%s\n",tmp->p);
           tmp = tmp->next;
        }
    //}
    
   
}