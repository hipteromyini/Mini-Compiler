// This is only the first try of the cpp project of lexical analysis.
#include <bits/stdc++.h>
using namespace std;
//词法分析程序
//首先定义种别码
/*
第一类：标识符   letter(letter | digit)*  无穷集
第二类：常数    (digit)+  无穷集
第三类：保留字(11)
while  for  do  break  continue
return
char int enum void
if  else

第四类：界符  ‘/*’、‘//’、 () { } [ ] " "  '
第五类：运算符 <、<=、>、>=、=、+、-、*、/、^、

对项目支持的保留字进行编码：
*/
enum {
    Num=10086 , Fun, Sys, Glo, Loc, Id, Not , String ,
    Int, Char ,Enum,Void, If , Else , For , While , Continue , Break, Return ,
    Main,Scanf,Printf,
    Assign,Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Inc, Dec
};
static string keyword[]={"int","char","void","string","if","else","for","while","continue","break","return"};//关键字
map<string,int>mp;
const int rev_siz=11;
struct identifier {
    int token;//返回标记
    int hash;//哈希值
    char * name;//本身的字符串
    int clas;
    int type;//标识符的类型
    int value;//标识符的值
};
//struct tbNode
//{
//    char name[20];
//    char type[16];
//    void *addr;
//}lex[100005];
//struct symbolTb
//{
//    struct symbolTb *pre;
//    int width;
//    int counter;
//    struct tbNode * data[200];
//};

int key_siz;
const int N=1e5+5;
char letter[N],token;
int token_val,sig,hash;
int Table[N];
int idmain[N];

int len,pos=1,tot;
//源代码长度，当前短语位置，总短语数
bool iskeyword(string s)
{
    for(int i=0;i<rev_siz-1;i++)
    {
        if(s==keyword[i])
        {
            token=mp[s];
            return true;
        }
    }
    return false;
}
void next_word()
{
    token=letter[pos];
    while(token==' ')//跳过所有空格（' '）
        token=letter[++pos];
    if(token=='#')//跳过宏定义
    {
        while(token!=0&&token!='\n')
            token=letter[++pos];
        return;
    }
    if(isalpha(token)||token=='_')//字符串
    {
        string s;
        while(isalpha(token)||token=='_')
        {
            s+=token;
            token=letter[++pos];
        }
        //判断是否是保留字
        if(!iskeyword(s)) token=String;
        return;
    }
    if(isdigit(token))// 正数
    {
        token_val=0;
        while(isdigit(token))
        {
            token_val=token_val*10+token-'0';
            token=letter[++pos];
        }
        token_val*=sig;
        sig=1;
        token=Num;
        return;
    }
    if(token=='+')
    {
        if(letter[pos+1]=='+')
        {
            pos++;
            token=Inc;
        }
        else // - 运算符
        {
            token=Add;
        }
        return;
    }
    if(token=='-')
    {
        if(letter[pos+1]=='-')
        {
            pos++;
            token=Dec;
        }
        if(isdigit(letter[pos+1]))//负数
        {
            sig=-1;
            next_word();
        }
        else // - 运算符
        {
            token=Sub;
        }
        return;
    }
    if(token=='*')
    {
        token=Mul;
        return;
    }
    if(token=='/')
    {
        if(letter[pos+1]=='/')
        {
            // 单行注释
            token=letter[++pos];
            while(token!=0&&token!='\n')
            {
                token=letter[++pos];
            }
            return;
        }
        else
        {
            // 除运算符
            token=Div;
            return;
        }
    }
    if(token=='=')
    {
        if(letter[pos+1]=='=')
        {
            pos++;
            token=Eq;//==
        }
        else token=Assign;//=
        return;
    }
    if(token=='!')
    {
        if(letter[pos+1]=='=')
        {
            pos++;
            token=Ne;//不等于
        }
        else
        {
            token=Not;//取反
        }
        return;
    }
    if(token=='<')
    {
        if(letter[pos+1]=='<')
        {
            pos++;
            token=Shl;//左移
        }
        else if(letter[pos+1]=='=')
        {
            pos++;
            token=Le;//<=
        }
        else token=Lt;//<
        return;
    }
    if(token=='>')
    {
        if(letter[pos+1]=='>')
        {
            pos++;
            token=Shr;//右移
        }
        else if(letter[pos+1]=='=')
        {
            pos++;
            token=Ge;//>=
        }
        else token=Gt;//>
        return;
    }
    if(token=='|')
    {
        if(letter[pos+1]=='|')
        {
            pos++;
            token=Lor;//||
        }
        else token=Or;//|运算
        return;
    }
    if(token=='&')
    {
        if(letter[pos+1]=='&')
        {
            pos++;
            token=Lan;//&&
        }
        else token=And;//&
        return;
    }
    if(token=='^')
    {
        token=Xor;
        return;
    }

}

int main(int argc,char** argv)
{
    char c;
//    freopen("in.txt","r",stdin);
    len=0;
    while(cin>>c)
        letter[++len]=c;
    while(pos<=len)
    {
        next_word();
    }

    return 0;
}

