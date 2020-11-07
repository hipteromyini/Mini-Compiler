// This is only the first try of the cpp project of lexical analysis.
#include <bits/stdc++.h>
using namespace std;
//词法分析程序
//首先定义种别码
/*
第一类：标识符   letter(letter | digit)*  无穷集
第二类：常数    (digit)+  无穷集
第三类：保留字(32)
while  for  do  break  continue
switch  case
static  return
char    const
if      else  int   long   unsigned  void
double  enum
struct


第四类：界符  ‘/*’、‘//’、 () { } [ ] " "  '
第五类：运算符 <、<=、>、>=、=、+、-、*、/、^、

对所有定义保留字进行编码：
<int,1>
<unsigned,2>
<long,3>
<float,4>
<double,5>
<char,6>
<string,7>
<const,8>
<struct,9>
*/
struct Word
{
    string type,statement;
    int val;
}ans[100005];
static string wordtype[]={"Int","Unsigned","Long","Float","Double",
                          "Char","String","Const","Struct"};
static string keyword[]={"while","for","do","break","continue",
                         "switch","case","return",
                         "int","char","double","float","long",
                         "const","if","else","struct",};//关键字
int key_siz;
static string operaterWord[36] = {
        "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
        "!=", ";", "(", ")", "^", ",", "#", "&",
        "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
        "}", ".", ":", "!"};//运算符
const int N=1e5+5;
char letter[N],token;
int token_val,sig;
//数值，符号

int len,pos=1,tot;
//源代码长度，当前短语位置，总短语数
int iskeyword(string s)
{
    for(int i=0;i<key_siz;i++)
    {
        if(s==keyword[i])
            return i+1;
    }
    return 0;
}
void next_word()
{
    token=letter[pos];
    while(token==' ')//pass all the ' '
        token=letter[++pos];
    if(token=='#')//we will not support it
    {
        while(token!=0&&token!='\n')
            token=letter[++pos];
        return;
    }
    if(token=='-')
    {
        if(isdigit(letter[pos+1]))//negative integer
        {
            sig=-1;
            next_word();
        }
        else //operater -
        {
            ans[++tot]={"-"};
        }
        return;
    }
    if(isdigit(token))// positive integer
    {
        token_val=0;
        while(isdigit(token))
        {
            token_val=token_val*10+token-'0';
            token=letter[++pos];
        }
        token_val*=sig;
        sig=1;
        ans[++tot]={"Int","",token_val};
        return;
    }
    if(isalpha(token)||token=='_')
    {
        string s;
        while(isalpha(token)||token=='_')
        {
            s+=token;
            token=letter[++pos];
        }
        int id=iskeyword(s);
        if(id) ans[++tot]={keyword[id-1]};
        else 
        {
            ans[++tot]={"String"};
        }
        return;
    }
    
}
int main(int argc,char** argv)
{
    char c;
    freopen("in.txt","r",stdin);
    while(cin>>c)
        letter[++len]=c;
    while(pos<=len)
    {
        next_word();
    }

    return 0;
}
