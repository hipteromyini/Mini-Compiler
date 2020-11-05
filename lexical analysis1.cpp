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

对所有可数符号进行编码：
<$,0>
<auto,1>
...
<while,32>
<+，33>
<-,34>
<*,35>
</,36>
<<,37>
<<=,38>
<>,39>
<>=,40>
<=,41>
<==,42>
<!=,43>
<;,44>
<(,45>
<),46>
<^,47>
<,,48>
<",49>
<',50>
<#,51>
<&,52>
<&&,53>
<|,54>
<||,55>
<%,56>
<~,57>
<<<,58>左移
<>>,59>右移
<[,60>
<],61>
<{,62>
<},63>
<\,64>
<.,65>
<?,66>
<:,67>
<!,68>
"[","]","{","}"
<常数99  ,数值>
<标识符100 ，标识符指针>


*/
enum {
  Num = 64, Fun, Sys, Glo, Loc, Id,
  Char, Else, Enum, If, Int, Return, Sizeof, While,
  Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};
static char reserveWord[32][20] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum",
     "for", "goto", "if", "int",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
static char operaterWord[36][10] = {
    "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
    "!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
    "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
    "}", "\\", ".", "\?", ":", "!"
};
const int N=1e5+5;
char letter[N],token;
char cur_word[N];
int token_val,sig;
int len,pos=1,tot;

void next_word()
{
    token=letter[pos];
    if(token=='#')//we will not support it
    {
        while(token!=0&&token!='\n')
            token=s[++pos];
        return;
    }
    if(token=='-')
    {
        if(isdigit(s[pos+1])//negative integer
        {
           sig=-1;
           next();
        }
        else //operater
        {

        }
        return;
    }
    if(isdigit(token))// positive integer
    {
        token_val=0;
        while(isdigit(token))
        {
            token_val=token_val*10+token-'0';
            token=s[++pos];
        }
        token=Num;
        token_val*=sig;
        sig=1;
        return;
    }

}
int main(int argc,char argv[])
{
    char c;
    freopen("in.txt",'r',stdin);
    while(cin>>w)
    {
        if(w!=' ') letter[++len]=w;
    }
    while(pos<=len)
    {
        next_word();
    }

    return 0;
}
