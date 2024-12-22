#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;
void dzialanie(queue<string> onp);
int priority(string oper)
{
    if(oper==",")
        return 0;
    if(oper=="+" || oper=="-")
        return 1;
    if(oper=="*" || oper=="/")
        return 2;
    if(oper=="IF" || oper=="MIN" || oper=="MAX" || oper=="N")
        return 3;
    return 4;
}
void wypisz(queue<string> q) // tu bedzie moje wypisz po
{ //wystarczy tylko przejsc po liscie
    while(!q.empty())
    {
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;
}
void wyp(queue <int> q)
{
    while(!q.empty())
    {
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;
}
void wypstack (stack <string> s)
{
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    cout<<endl;
}
void wypintstack (stack <int> s)
{
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    cout<<endl;
}
void test()
{
    queue <string> onp;
    stack <string> operatory;
    string wejscie;
    while(cin>>wejscie)
    {
        if(wejscie[0]=='.')
            break;
        if(wejscie[0]>='0' && wejscie[0]<='9')
            onp.push(wejscie);
        else if (wejscie=="(")
            operatory.push(wejscie);
        else if (wejscie==")")
        {
            while(!operatory.empty())
            {
                string token=operatory.top();
                operatory.pop();
                int liczprzecinki=1;
                if(token=="(")
                {
                    break;
                }
                else
                {
                    if(token!=",")
                    {
                        if(token=="MAX" || token=="MIN")
                            token=token+"1";
                        onp.push(token);
                    }

                    while(token==",")
                    {
                        //cout<<"TU"<< liczprzecinki<<endl;
                        liczprzecinki++;
                        token=operatory.top();
                        operatory.pop();
                    }
                    if(liczprzecinki>1)
                    {
                        string a=operatory.top();
                        if(a=="MAX" || a=="MIN" || a=="IF")
                        {
                            operatory.pop();
                            string help=to_string(liczprzecinki);
                            if(a!="IF")
                                a=a+help;
                            onp.push(a);
                            liczprzecinki=1;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            int priorytetIn=priority(wejscie); //priorytet wchodzacego
            while(!operatory.empty())
            {
                string top=operatory.top(); //top to ten na gorze
                operatory.pop();
                if(top=="(" || priority(top)<priorytetIn || (wejscie=="," && top==",") ||
                   (priority(wejscie)==3 && priority(top)==3))
                {
                    operatory.push(top); //jezeli wchodzacy ma wiekszy priorytet
                    break; //to on idzie na stack
                }
                if(top=="MAX" || top=="MIN")
                    top=top+"1";
                onp.push(top); // jezeli wchodzacy ma nizszy lub ten sam to wypychamy top
            }
            operatory.push(wejscie); // i wsadzamy wejscie
        }
        //wypisz(onp);
        //wypstack(operatory);
    }
    //wypstack(operatory);
    while(!operatory.empty())
    {
        string op=operatory.top();
        operatory.pop();
        if(op=="MAX" || op=="MIN")
            op=op+"1";
        onp.push(op);
    }
    wypisz(onp);
    dzialanie(onp);
}
void dzialanie(queue <string> onp)
{
    stack<int>liczby;
    bool czydziel0=0;
    while(!onp.empty())
    {
        string token=onp.front();
        onp.pop();
        if(token[0]>='0' && token[0]<='9')
        {
            int liczba=stoi(token);
            liczby.push(liczba);
        }
        else
        {
            cout<<token<<" ";
            wypintstack(liczby);
            if(token=="+" || token == "-" || token=="/" || token=="*")
            {
                int operand2=liczby.top();
                liczby.pop();
                int operand1=liczby.top();
                liczby.pop();
                int wynik=0;
                if(token=="+")
                    wynik=operand1+operand2;
                else if(token=="-")
                    wynik=operand1-operand2;
                else if(token=="*")
                    wynik=operand1*operand2;
                else
                {
                    if(operand2==0)
                    {
                        cout<<"ERROR"<<endl;
                        czydziel0=1;
                        break;
                    }
                    else
                        wynik=operand1/operand2;
                }
                liczby.push(wynik);
            }
            else if(token=="N")
            {
                int operand=liczby.top();
                liczby.pop();
                operand*=(-1);
                liczby.push(operand);
            }
            else if(token=="IF")
            {
                int operand3=liczby.top();
                liczby.pop();
                int operand2=liczby.top();
                liczby.pop();
                int operand1=liczby.top();
                liczby.pop();
                if(operand1>0)
                    liczby.push(operand2);
                else
                    liczby.push(operand3);
            }
            else
            {
                string k=token.substr(3);
                if(token[1]=='A')//max
                {
                    int ile=stoi(k);
                    int maxi=-1e9;
                    for(int i=0;i<ile;i++)
                    {
                        int operand=liczby.top();
                        liczby.pop();
                        if(operand>maxi)
                            maxi=operand;
                    }
                    liczby.push(maxi);
                }
                else
                {
                    int ile=stoi(k);
                    int mini=1e9;
                    for(int i=0;i<ile;i++)
                    {
                        int operand=liczby.top();
                        liczby.pop();
                        if(operand<mini)
                            mini=operand;
                    }
                    liczby.push(mini);
                }
            }
        }
    }
    if(czydziel0==0)
        wypintstack(liczby);
}
int main()
{
    int testy;
    cin>>testy;
    while(testy--)
    {
        test();
    }
    return 0;
}
