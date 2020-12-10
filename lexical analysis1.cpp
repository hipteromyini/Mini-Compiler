// This is the fifth try of the cpp project of lexical analysis.
#include "bits/stdc++.h"
using namespace std;
#define K_DIGIT       3      //整数
#define K_CHAR        4      //字符
#define K_STRING      5      //字符串
#define K_TYPE        6      //数据类型
#define K_KEYWORDS    7      //关键字
#define K_OPERATOR    8      //运算符
#define K_IDENTIFIER  9      //标识符
#define K_BRACKET     10     //括号

using namespace std;

//存储分词类型
struct IDwords
{
    int       id;     //标志
    string    word;   //单词
};

//字符转字符串
string char_to_str(char c)
{
    char s[2] = " ";
    s[0] = c;
    return string(s);
}

//是否为运算操作符
int is_operator(char c)
{
    if(c == '+' || c=='-'||c=='*'||c=='/'||c==','||c=='=' ||c=='>' || c=='<')
        return 1;
    else
        return 0;
}

//是否为大括号、小括号、分号
int is_bracket(char c)
{
    if(c=='{' || c=='}' || c=='(' || c==')' ||c==';')
        return 1;
    else
        return 0;
}

//是否为换行符
int is_blank(char c)
{
    if(c=='\n' || c=='\t' || c==' ' || c=='\r')
        return 1;
    else
        return 0;
}

//判断单词类型（保留字|标识符）
int word_token(string s)
{
    int  size = s.size();
    //字符数据
    if(s[0]=='\'')
    {
        if(s[size-1] == '\'')
            return K_CHAR;
        else
        {
            cout<<"错误的字符串数据："<<s<<endl;
            exit(-1);
        }
    }
        //字符串数据
    else if(s[0]=='\"')
    {
        if(s[size-1]=='\"')
            return K_STRING;
        else
        {
            cout<<"错误的字符串数据："<<s<<endl;
            exit(-1);
        }
    }
        //整数
    else if(isdigit(s[0]))
    {
        for(int i=1;i<size;i++)
        {
            if(!isdigit(s[i]))
            {
                cout<<"不合法的标识符："<<s<<endl;
                exit(-1);
            }
        }
        return K_DIGIT;
    }
    else
    {
        for(int i=0;i<size;i++)
        {
            if(!isalnum(s[i]) && s[i]!='_')
            {
                cout<<"不合法的标识符："<<s<<endl;
                exit(-1);
            }
        }
        //数据类型
        if(s=="int" || s=="char")
            return K_TYPE;
            //关键字
        else if(s=="if" || s=="else" || s=="printf" || s=="main")
            return K_KEYWORDS;
            //自定义标识符
        else
            return K_IDENTIFIER;
    }
}

//添加分词结果
void add_keywords(vector<IDwords> &v,int id,string word)
{
    v.push_back({id,word});
}

//词法分析
void lexical_analysis(string source,vector<IDwords> &AnalysisResults)
{
    char   ch;
    ifstream   rfile(source.c_str());
    if(!rfile.is_open())
    {
        cout<<"无法打开源文件"<<endl;
        exit(-1);
    }
    rfile>>noskipws;   //不过滤空格
    while(rfile>>ch)
    {
        int state=0;        //判断状态
        string tmp;       //字符串缓存
        char        try_ch;         //探测前面的字符
        switch(state)
        {
            case 0:
                if(ch=='/') //可能是注释
                {
                    rfile>>try_ch;
                    if(try_ch=='/')
                    {
                        while(rfile>>try_ch)
                        {
                            if(try_ch=='\n')
                                break;   //单行注释
                        }
                        break;
                    }
                    else if(try_ch=='*')
                    {
                        while(rfile>>try_ch)
                        {
                            if(try_ch=='*')
                            {
                                rfile>>try_ch;
                                if(try_ch=='/')
                                    break; //多行注释
                            }
                        }
                        break;
                    }
                    else
                    {
                        add_keywords(AnalysisResults,K_OPERATOR,char_to_str(ch));
                        ch = try_ch;  //继续状态1
                    }
                }
            case 1:
                if(is_operator(ch)) //判断操作符
                {
                    add_keywords(AnalysisResults,K_OPERATOR,char_to_str(ch));
                    break;
                }
            case 2:
                if(is_bracket(ch)) //大括号、小括号
                {
                    add_keywords(AnalysisResults,K_BRACKET,char_to_str(ch));
                    break;
                }
            case 3:
                if(is_blank(ch)) //换行符
                    break;
            case 4:
                if(ch=='#') //跳过预处理
                {
                    while(rfile>>ch)
                    {
                        if(is_blank(ch))
                        {
                            break;
                        }
                    }
                    break;
                }
            default://判断单词类型
                tmp += char_to_str(ch);
                while(rfile>>try_ch)
                {
                    if(try_ch == '\"')
                    {
                        tmp += char_to_str(try_ch);
                        if(ch == '\"')
                        {
                            add_keywords(AnalysisResults,word_token(tmp),tmp);
                            break;
                        }
                        else
                        {
                            cout<<"不合法的标识符："+tmp<<endl;
                            exit(-1);
                        }
                    }
                    else if(is_blank(try_ch) )//换行符
                    {
                        if(ch != '\'' && ch != '\"')
                        {
                            add_keywords(AnalysisResults,word_token(tmp),tmp);
                            break;
                        }
                        else
                            tmp += char_to_str(try_ch);
                    }
                    else if(is_operator(try_ch) )
                    {
                        if(ch !='\'' && ch != '\"' )
                        {
                            add_keywords(AnalysisResults,word_token(tmp),tmp);
                            add_keywords(AnalysisResults,K_OPERATOR,char_to_str(try_ch));
                            break;
                        }
                        else
                            tmp  += char_to_str(try_ch);
                    }
                    else if(is_bracket(try_ch))
                    {
                        add_keywords(AnalysisResults,word_token(tmp),tmp);
                        add_keywords(AnalysisResults,K_BRACKET,char_to_str(try_ch));
                        break;
                    }
                    else
                        tmp  += char_to_str(try_ch);
                }
        }
    }
    rfile.close();
}

//输出词法分析结果
void print_lexical(vector<IDwords> &v)
{

    for(auto i:v)
        cout<<i.id<<" "<<i.word<<endl;
}

int main()
{

    return 0;
}
