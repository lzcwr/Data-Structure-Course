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

//字符堆栈
class CharStack
{
public:
    char  *base;
    int  top;
    int  stacksize;
public:
    CharStack()
    {
        base = new char[INIT_SIZE];
        if(!base)
        {
            top = 0;
            stacksize = 0;
        }
        else
        {
            top = 0;
            stacksize = INIT_SIZE;
        }
    }
    ~CharStack()
    {
        delete[]base;
    }
    int IsEmpty()
    {
        if(top == 0) return true;
        return false;
    }
    int Push(char ch)
    {
        if(top >= stacksize)
        {
            char *p;
            int newsize = stacksize + INC_SIZE;
            p = new char[newsize];
            if(!p) return false;

            memcpy(p, base, stacksize);
            delete[] base;
            base = p;
        }
        base[top++] = ch;
        return true;
    }
    int Pop(char &ch)
    {
        if(top <= 0) return false;
        ch = base[--top];
        return true;
    }
    int GetTop(char &ch)
    {
        if(top <= 0) return false;
        ch = base[top - 1];
        return true;
    }
};

//完成如下括弧匹配的判断函数
int Matching(char *exp)
{
    bool state = true;
    CharStack S;
    char ch;

    //...........
    while(state && (ch=*exp++) != 0 )
    {
        switch(ch)
        {
        case '(':
        case '[':
        case '{':
            S.Push(ch);
            break;
        case ')':
            if(S.GetTop(ch) && ch=='(')
                S.Pop(ch);
            else
                state = 0;
            break;
        case ']':
            if(S.GetTop(ch) && ch=='[')
                S.Pop(ch);
            else
                state = 0;
            break;
        case '}':
            if(S.GetTop(ch) && ch=='{')
                S.Pop(ch);
            else
                state = 0;
            break;
        }
    }

    if(state && S.IsEmpty()) return true;
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

//完成中缀式到后缀式的转换函数
void TransSuf(char* suffix, char* exp)
{
    CharStack S;
    char ch,c;

    S.Push('#');
    ch = *exp++;
    while(!S.IsEmpty())
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
                S.Push(ch);
                break;

            case ')':
                S.Pop(c);
                while(c != '(')
                {
                    *suffix ++ = c;
                    S.Pop(c);
                }
                break;

            case ']':
                S.Pop(c);
                while(c != '[')
                {
                    *suffix ++ = c;
                    S.Pop(c);
                }
                break;

            case '}':
                S.Pop(c);
                while(c != '{')
                {
                    *suffix ++ = c;
                    S.Pop(c);
                }
                break;

            default:
                while(S.GetTop(c) && (Level(c) >= Level(ch)))
                {
                    if(c!='#')
                        *suffix ++ = c;
                    else
                        *suffix = 0;
                    S.Pop(c);
                }
                if(ch != '#')
                    S.Push(ch);
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
}

int main()
{
    char buffer[200], suffix[200];
    gets(buffer);
    if(Matching(buffer))
    {
        printf("匹配成功\n");
        TransSuf(suffix, buffer);
        puts(suffix);
    }
    else printf("匹配失败\n");
    system("pause");

    return 0;
}

