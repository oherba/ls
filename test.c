
 #include "ft_ls1.h"
 
t_ls1* SortedMerget(t_ls1 *a, t_ls1* b,int flag)
{
	t_ls1	*result;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	result = NULL;	
	// if (a->t > b->t && (R1 & flag) == R1)
	// {
	// 	result = a;
	// 	result->next = SortedMerget(a->next, b,flag);
	// }
	// else 
	if (a->t >= b->t)
	{
		result = a;
		result->next = SortedMerget(a->next, b,flag);
	}
	else
	{
		result = b;
		result->next = SortedMerget(a, b->next,flag);
	}

	return result;
}

t_ls1* SortedMerges(t_ls1* a, t_ls1* b,int flag)
{
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	t_ls1* result = NULL;
	// if (a->s < b->s && (R1 & flag) == R1)
	// {
	// 	result = a;
	// 	result->next = SortedMerget(a->next, b,flag);
	// }
	// else 
	if (a->s >= b->s)
	{
		result = a;
		result->next = SortedMerges(a->next, b,flag);
	}
	else
	{
		result = b;
		result->next = SortedMerges(a, b->next,flag);
	}

	return result;
}

t_ls1* SortedMerge(t_ls1* a, t_ls1* b,int flag)
{
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	t_ls1* result = NULL;
	// if (ft_strcmp(a->p ,b->p ) > 0 && (R1 & flag) == R1)
	// {
	// 	result = a;
	// 	result->next = SortedMerget(a->next, b,flag);
	// }
	// else 
	if (ft_strcmp(a->p ,b->p )<= 0)
	{
		result = a;
		result->next = SortedMerge(a->next, b,flag);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next,flag);
	}

	return result;
}

void FrontBackSplit(t_ls1* source, t_ls1** frontRef,t_ls1** backRef)
{
	if (source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
		return;
	}

	t_ls1* slow = source;
	t_ls1* fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}
void MergeSort(t_ls1 **head, int flag)
{

	if (*head == NULL || (*head)->next == NULL)
		return;

	t_ls1* a;
	t_ls1* b;

	FrontBackSplit(*head, &a, &b);
	MergeSort(&a, flag);
	MergeSort(&b, flag);
    if((flag & S) == S)
        *head = SortedMerges(a, b, flag);
    else if((flag & T) == T)
        *head = SortedMerget(a, b,flag);
    else
        *head = SortedMerge(a, b, flag);
   
}

void sswap(char **x, char **y)
{
	char *t;

	t = *x;
	*x = *y;
	*y = t;
}

void ft_sort(char *a[], int m, int n) 
{
    int i;
    int j;
    char *key;

    if (m < n)
    {
        key = a[m];
        i  = m + 1 ;
        j = n;
    
        while ( i <= j)
        {
            while ((i <= n) && (ft_strcmp(a[i] ,key) <= 0) )
                i++;  
            while ((j >= m)  && (ft_strcmp(a[j],key) > 0 ))
                j--;
            if (i < j)
                sswap(&a[i],&a[j]);
        }
        sswap(&a[m],&a[j]);
       ft_sort(a,m,j-1);
        ft_sort(a,j+1,n);
    }
}
