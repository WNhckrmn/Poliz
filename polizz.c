#include "stack.c"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>


int overflow(int first, int second);
int instack(char* pstring );
int MultiplicationOverflow(int first, int second);


int overflow(int a, int b) 
{
    return (a > 0 && b > 0 && (INT_MAX - b < a) ||
        a < 0 && b < 0 && (INT_MIN - b > a));
}
int MultiplicationOverflow(int a, int b) 
{
    return (a > INT_MAX/b || a < INT_MIN/b);
};

int main()
{
    char* pstring=calloc(1,sizeof(char*));
    fgets(pstring,100,stdin);
    int res=instack(pstring);
    free(pstring);  
    printf("%d\n",res);
    return 0;
}

int instack(char* pstring)
{
    stack s = stack_new();
    int len=strlen(pstring);
    for (int i = 0; i < len; i++)
    {
        int a;
        if(isdigit(pstring[i]))
        {
            a=(int)pstring[i]-'0';
            stack_push(&s, a);
        }
        else
        {
            if (pstring[i]=='-')
            {
                int k2=stack_pop(&s);
                int k1=stack_pop(&s);
                if(!(overflow(k1,k2)))
                {
                    int k=k1-k2;
                    stack_push(&s,k);
                }
                else
                {
                    perror("overflow in minus");
                    exit(0);
                }
                 
            }
            else if (pstring[i]=='+')
            {
                int k2=stack_pop(&s);
                int k1=stack_pop(&s);
                if(!(overflow(k1,k2)))
                {
                    int k=k1+k2;
                    stack_push(&s,k);
                }
                else
                {
                    perror("overflow in plus");
                    exit(0);
                }
                
            }
            else if(pstring[i]=='*')
            {
                int k2=stack_pop(&s);
                int k1=stack_pop(&s);
                if(!(MultiplicationOverflow(k1,k2)))
                {
                    int k=k1*k2;
                    stack_push(&s,k);
                }
                else
                {
                    perror("overflow in multiplication");
                    exit(0);
                }
                
            }
            else if(pstring[i]=='/')
            {
                int k2=stack_pop(&s);
                int k1=stack_pop(&s);
                if(k2==0)
                {
                    perror("the divisor is 0");
                    exit(0);
                }
                else
                {
                    int k=k1/k2;
                    stack_push(&s,k);
                }
            }
        }
        
    }
    if ((stack_len(s))!=1)
    {
        perror("Полиз был некорректным");
        exit(0);
    }
    return stack_pop(&s);
}

