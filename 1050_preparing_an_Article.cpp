/*************************************************************************
  > File Name   : File/code/1050_preparing_an_Article.cpp
  > Author      : liudy
  > Mail        : 787896130@qq.com
  > Created Time: 2016年08月05日 星期五 14时56分13秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
using namespace std;
char Text[20500], Ans[20500];
// 只是注意 \endinput 也算是段尾的标示符
int check_Open(int start, int len){
    for(int i = start + 1; i < len; i++){
        if((Text[i] == 10 && Text[i+1] == 10) || (Text[i] =='\\' && Text[i+1] == 'p' && Text[i+2] == 'a' && Text[i+3] == 'r') || (Text[i] == '\\' && Text[i+1] == 'e' && Text[i+2] == 'n' && Text[i+3] == 'd' && Text[i+4] == 'i' && Text[i+5] == 'n' && Text[i+6] == 'p' && Text[i+7] == 'u' && Text[i+8] == 't'))
            return -1;
        if(Text[i] == '"' && Text[i-1] != '\\'){
            return i;
        }
    }
}
void Copy(int from, int end){
    for(int i = from; i <= end; i++)
        Ans[i] = Text[i];
}
void printAns(int len){
    for(int i = 1; i < len; i++){
        if(Ans[i] == -1)
            continue;
        else if(Ans[i] == -2)
            cout << "``";
        else if(Ans[i] == -3)
            cout << "''";
        else
            cout << Ans[i];
    }
}
bool check_end(char c[], int len){
    char tem[10] = "\\endinput";
    int l = len - 9;
    for(int i = 0; i < 9; i++){
        if(c[l + i] != tem[i])
            return false;
    }
    return true;
}
int main(){
    char c;
    int len = 1;
    while((c = getchar()) != EOF){
        Text[len++] = c;
        if(c == 't' && len >= 9)
            if(check_end(Text, len))
                break;
    }
    
    for(int i = 1; i < len; i++){
        if(Text[i] == '\"'){
            if(Text[i-1] == '\\'){
                Ans[i] = Text[i];
            }else{
                int signal = 0;  //signal = -1 代表open 否则为close 并且signal 代表 匹配" 的位置
                signal = check_Open(i, len);
                if(signal == -1){
                    Ans[i] = -1;     // -1一个标示符 表示 跳过该字符为空
                }else{
                    Ans[i] = -2;  // -2 标示符 表示 ``
                    Ans[signal] = -3; // -3 表示符 表示 ''
                    Copy(i + 1, signal - 1);
                    i = signal;
                }
            }
        }else{
            Ans[i] = Text[i];
        }
    }    

    printAns(len);
    return 0;
}
