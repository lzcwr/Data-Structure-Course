#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxn = 205;
const int maxm = 1e5 + 5;
const int mod = 10000;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;

struct CharWeight
{
    char ch;
    unsigned int weight;
    CharWeight(){}
    CharWeight(char a, unsigned int b)
    {
        ch = a; weight = b;
    }
};

struct HTNode
{
    char ch;
    unsigned int weight;
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
    HTNode(){}
    HTNode(char a, unsigned int w, unsigned int p, unsigned int l, unsigned int r)
    {
        ch = a; weight = w; parent = p; lchild = l; rchild = r;
    }
    HTNode(unsigned int w, unsigned int p, unsigned int l, unsigned int r)
    {
        weight = w; parent = p; lchild = l; rchild = r;
    }
};
typedef HTNode *HuffmanTree;

struct HCodeNode
{
    char ch;
    char *code;
};
typedef HCodeNode *HuffmanCode;

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, CharWeight *w, int n)
{
    if(n <= 1) return;
    HT = new HTNode[n << 1];
    int i, j;
    for(i = 1; i <= n; i++)
        HT[i] = HTNode(w[i - 1].ch, w[i - 1].weight, 0, 0, 0);
    for(; i < (n << 1); i++)
        HT[i] = HTNode(0, 0, 0, 0);
    for(i = n + 1; i < (n << 1); i++)
    {
        int s1 = 0, s2 = 0;
        for(int k = 1; k < i; k++)
        {
            if(HT[k].parent != 0)
                continue;
            if(s1 == 0) s1 = k;
            else if(s2 == 0)
            {
                if(HT[k].weight < HT[s1].weight)
                {
                    s2 = s1;
                    s1 = k;
                }
                else s2 = k;
            }
            else
            {
                if(HT[k].weight < HT[s1].weight)
                {
                    s2 = s1;
                    s1 = k;
                }
                else if(HT[k].weight < HT[s2].weight)
                {
                    s2 = k;
                }
            }
        }
        if(s2 == 0) break;
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    HC = new HCodeNode[n];
    char *code = new char[n];
    code[n - 1] = 0;
    for(i = 1; i  <=  n; i++)
    {
        int start = n - 1, child, parent;
        for(child = i, parent = HT[i].parent; parent != 0; child = parent,  parent = HT[parent].parent)
        {
            if( HT[parent].lchild == child )
                code[--start] = '0';
            else
                code[--start] = '1';
        }

        HC[i - 1].ch = HT[i].ch;
        HC[i - 1].code = new char [n - start];
        strcpy(HC[i - 1].code, code + start);
    }
    delete code;

}
char* Code(char ch, HuffmanCode HC, int n)
{
    for(int i = 0; i  <=  n-1; i++)
        if(ch == HC[i].ch)  return HC[i].code;
    return 0;

}

char Decode(char * str, HuffmanCode HC, int n)
{
    for(int i = 0; i  <=  n-1; i++)
        if(strcmp(HC[i].code, str) == 0)
            return HC[i].ch;
    return 0;
}

void solve()
{
    FILE *fp;
    CharWeight CW[200];
    int cnt;

    if((fp = fopen("频度.txt", "r")) == 0)
    {
        printf("打开“频度.txt”文件失败");
        system("pause");
        return ;
    }
    for(cnt = 0; cnt < 200; cnt++)
    {
        char buf[20];
        int w;

        if(fscanf(fp, "%s%d", buf, &w) == EOF)
            break;

        CW[cnt].ch = buf[0];
        CW[cnt].weight = w;
    }
    fclose(fp);

    HuffmanTree HT;
    HuffmanCode HC;

    HuffmanCoding(HT, HC, CW, cnt) ;
    FILE *fin, *fout;

    if((fin = fopen("源码.txt", "r")) == 0)
    {
        printf("打开“源码.txt”文件失败");
        system("pause");
        return ;
    }
    if((fout = fopen("编码.txt", "w")) == 0)
    {
        printf("创建“编码.txt”文件失败");
        system("pause");
        return ;
    }

    char ch;
    while((ch = fgetc(fin)) != EOF)
    {
        if(ch >= 'a' && ch  <=  'z')
            ch += 'A' - 'a';
        else if(ch < 'A' || ch > 'Z')
            ch = '#';
        char *p = Code(ch, HC, cnt);
        if(p) fprintf(fout, "%s", p);
    }
    fclose(fin);
    fclose(fout);

    if((fin = fopen("编码.txt", "r")) == 0)
    {
        printf("打开“编码.txt”文件失败");
        system("pause");
        return ;
    }
    if((fout = fopen("解码.txt", "w")) == 0)
    {
        printf("创建“解码.txt”文件失败");
        system("pause");
        return ;
    }

    int i = 0;
    char buf[200];
    while((ch = fgetc(fin)) != EOF)
    {
        buf[i++] = ch;
        if(i >= 200) i = 0;
        buf[i] = 0;

        ch = Decode(buf, HC, cnt);
        if(ch)
        {
            if(ch < 'A' || ch > 'Z') ch = ' ';
            fputc(ch, fout);
            i = 0;
        }
    }
    fclose(fin);
    fclose(fout);

    system("pause");

    return ;
}

int main()
{
    solve();
    return 0;
}
