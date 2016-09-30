#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxn = 9999;
const int maxm = 1005;
const int mod = 10000;
const double eps = 1e-8;
const double pi = acos( -1.0);
const int inf = std::numeric_limits<int>::max();
const int INIT_SIZE	= 80;
const int INC_SIZE = 10;

typedef struct
{
    char  *base;
    int  top;
    int  stacksize;
} CharStack;

bool InitStack(CharStack &S)
{
    S.base = new char[INIT_SIZE];
    if(!S.base) return false;
    S.top = 0;
    S.stacksize = INIT_SIZE;
    return true;
}

void DestroyStack(CharStack &S)
{
    if(S.base) delete S.base;
}

int StackEmpty(CharStack &S)
{
    if(S.top == 0) return true;
    return false;
}

bool Push(CharStack &S, char ch)
{
    if(S.top >= S.stacksize)
    {
        char *p;
        int newsize = S.stacksize + INC_SIZE;
        p = new char[newsize];
        if(!p) return false;

        memcpy(p, S.base, S.stacksize);
        delete S.base;
        S.base = p;
    }
    S.base[S.top++] = ch;
    return true;
}

bool Pop(CharStack &S, char &ch)
{
    if(S.top <= 0) return false;
    ch = S.base[--S.top];
    return true;
}

bool GetTop(CharStack &S, char &ch)
{
    if(S.top <= 0) return false;
    ch = S.base[S.top-1];
    return true;
}

int Matching(char *exp)
{
    bool state = true;
    char *p = exp;
    char ch;
    CharStack S;

    InitStack(S);

    while(*p && state)
    {
        switch(*p)
        {
	        case '(':
	        case '[':
	        case '{':
	            Push(S, *p);
	            break;

	        case ')':
	            if(GetTop(S, ch) && ch == '(')
	                Pop(S, ch);
	            else
	                state = false;
	            break;

	        case ']':
	            if(GetTop(S, ch) && ch == '[')
	                Pop(S, ch);
	            else
	                state = false;
	            break;

	        case '}':
	            if(GetTop(S, ch) && ch == '{')
	                Pop(S, ch);
	            else
	                state = false;
	            break;
        }
        p++;
    }

    if(!StackEmpty(S))
        state = false;
    DestroyStack(S);

    if(state) return true;
    return false;
}

bool INOP(char ch)
{
    switch(ch)
    {
	    case '+':
	    case '-':
	    case '*':
	    case '/':
	    case '(':
	    case ')':
	    case '[':
	    case ']':
	    case '{':
	    case '}':
	    case '#':
	        return true;
	    default:
	        return false;
    }
}

int Level(char ch)
{
    switch(ch)
    {
	    case '+':
	    case '-':
	        return 2;
	    case '*':
	    case '/':
	        return 3;
	    case '(':
	    case ')':
	    case '[':
	    case ']':
	    case '{':
	    case '}':
	        return 1;
	    case '#':
	        return 0;
	    default:
	        return 0;
    }
}


void TransSuf(char* suffix, char* exp)
{
    CharStack S;
    char ch,c;

    InitStack(S);
    Push(S, '#');
    ch = *exp++;
    while(!StackEmpty(S))
    {
        if(!INOP(ch))
            *suffix++ = ch;
        else
        {
            switch(ch)
            {
            case '(':
            case '[':
            case '{':
                Push(S, ch);
                break;

            case ')':
                Pop(S, c);
                while(c != '(')
                {
                    *suffix ++ = c;
                    Pop(S, c);
                }
                break;
            case ']':
                Pop(S, c);
                while(c != '[')
                {
                    *suffix ++ = c;
                    Pop(S, c);
                }
                break;
            case '}':
                Pop(S, c);
                while(c != '{')
                {
                    *suffix ++ = c;
                    Pop(S, c);
                }
                break;

            default:
                while(GetTop(S, c) && (Level(c) >= Level(ch)))
                {
                    if(c!='#')
                        *suffix ++ = c;
                    else
                        *suffix = 0;
                    Pop(S, c);
                }
                if(ch != '#')
                    Push(S, ch);
                break;
            }
        }

        if(ch != '#')
        {
            ch = *exp++;
            if(ch == 0) ch = '#';
        }
        else
        {
            *suffix = 0;
            break;
        }
    }
    DestroyStack(S);
}

int Cacl(char* suffix, char& value)
{
    CharStack S;
    char *p = suffix;
    char ch;
    char v1, v2;
    InitStack(S);
    DestroyStack(S);
    return true;
}

int main()
{
    char buf[200], suf[200];
    gets(buf);
    if(Matching(buf))
    {
        printf("∆•≈‰≥…π¶\n");
        TransSuf(suf, buf);
        puts(suf);
    }
    else printf("∆•≈‰ ß∞‹\n");
    system("pause");
    
    return 0;
}

