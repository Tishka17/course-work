#include "..\..\..\Common\H\wndws.h"
#include "commdlg.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "iostream.h"
#include "fstream.h"
#include "conio.h"


#include "..\..\..\Common\H\plugins.h"
#include "..\..\..\Common\H\Approximator.h"
#include "..\H\PluginsUsage.h"
#include "..\H\Logfile.h"

#include "..\H\Script.h"

//does work
void RemoveSpaces(LongString oldstr, LongString newstr)
{
    char *c=oldstr, *cn=newstr;
    if (c==NULL) return;
    while (*c>0 && *c<33) c++;
    while (*c!=0) 
    {
        *cn=*c;
        c++;
        if(*c>32 || *c<0 || *(c-1)<0 || *(c-1)>33) 
             cn++;
    }
    while (cn-1>newstr && *(cn-1)<33 && *(cn-1)>0) cn--;
    if (cn>=newstr) *cn=0;
}
//does work
void RemoveComments(LongString oldstr, LongString newstr)
{
    char *c=oldstr, *cn=newstr;
    if (c==NULL) return;
    while (*c!=0)
    {
        while (*c!=0 && *c!=COMMENT_START)
        {
            *cn=*c;
            c++;
            cn++;
        }
        if (*c==*(c+1) && *c==COMMENT_START) //found ## -> replace with # and ignore as not a comment
        {
            *cn=*c;
            cn++;
            c++;
            c++;
            continue;
        }
        if (*c!=0) c++;
        while (*c!=0 && *c!=COMMENT_END)
            c++;
        if (*c!=0) c++;
    }
    *cn=0;
}

void RemoveQuotes(LongString oldstr, LongString newstr)
{
    char *c=oldstr, *cn=newstr;
    if (c==NULL) return;
    bool in=false;
    while (*c!=0)
    {
        if (*c==STRING_START && *(c+1)==STRING_START || *c==STRING_END && *(c+1)==STRING_END)
        {
            *cn=*c;
            cn++;
            c++;
        }
        else if (in && *c==STRING_END) in=false;
        else if (!in && *c==STRING_START) in=true;
        else 
        {
            *cn=*c;
            cn++;
        }
        c++;
    }
    *cn=0;
}
//does work (returns pointer to '\0' symbol)
char *LastChar(LongString str)
{
    return strchr(str, 0);
}

// does work (does not find symbol in substring between " characters)
char *FindSymbol(LongString str, char ch)
{
    char *c=str;
    while (*c!=0)
    {
        while (*c!=0 && *c!=STRING_START)
        {
            if (*c==ch) return c;
            c++;
        }
        if (*c==*(c+1) && *c==STRING_START) //found "" -> replace with " and ignore as not a substring
        {
            if (*c==ch) return c;
            c++;
            c++;
            continue;
        }
        if (*c!=0) c++;
        while (*c!=0 && (*c!=STRING_END  || (*c==STRING_END && *(c+1)==STRING_END)))
        {
            if (*c==STRING_END) c++;
            c++;
        }
        if (*c!=0) c++;
    }
    return NULL;
}

//does work (separates string "str_without_spaces str" into "str_without_spaces" and "str" stored in newstr1 and newstr2)
bool SeparateString(LongString oldstr, LongString newstr1, LongString newstr2)
{
    char *ch=FindSymbol(oldstr, ' ');
    if (ch==NULL)
    {
        strcpy(newstr1, oldstr);
        newstr2[0]=0;
        return false;
    }
    else
    {
        *ch=0;
        LongString tmp;
        strcpy(tmp, oldstr);
        RemoveSpaces(tmp,newstr1);
        strcpy(tmp,ch+1);
        RemoveSpaces(tmp,newstr2);
        if (newstr2[0]==0) return false;
        else return true;
    }
}

//does work
bool CorrectIdentifer(LongString str)
{
    char *c=str;
    if (*c==0) return false;
    if (*c>='0' && *c<='9') return false;
    while (*c!=0) 
    {
        if (*c>0 && *c<33 || 
            *c==STRING_START || 
            *c==STRING_END || 
            *c==VARIABLE_START || 
            *c==COMMENT_START || 
            *c==COMMENT_END ||
            *c==BRACKET_OPEN ||
            *c==BRACKET_CLOSE ||
            *c==MODIFER ||
            *c==ARRAY_OPEN ||
            *c==ARRAY_CLOSE ||
            *c==DO_NOT_ECHO) 
        {
            return false;
        }
        else 
        {
            c++;
        }
    }
    return true;
}

//does work
bool CorrectInt(LongString str)
{
    char *c=str;
    if (*c==0) return false;
    while (*c!=0)
    {
        if (*c<'0' || *c>'9') return false;
        c++;
    }
    return true;
}

//does work
bool GetLabels(ifstream &fin, CList &LabelList)
{
    int start=fin.tellg();
    bool res=true;
    String str,newstr,newstr2;
    char *ch;
    char *sh;

    while (!fin.eof())
    {
        str[0]=0;
        fin.getline(str, 1000);

        RemoveSpaces(str, newstr);
        RemoveComments(newstr,newstr2);
        RemoveSpaces(newstr2, str);

        //if it is label definition
        ch=str;
        if (*ch==LABEL_DEFINE)
        {
            *ch=0;
            sh=ch+1;
            RemoveSpaces(sh,newstr);
            if (CorrectIdentifer(newstr)) 
            {
                CLabel *l=(CLabel*)LabelList.GetFirst();
                while (l!=NULL)
                {
                    if (!strcmp(l->name,newstr))
                    {
                        if (fin.tellg()!=l->position)
                        cout<<"[ERROR] Redifinition of label \""<<newstr2<<"\""<<endl;
                        return 0;
                    }
                    l=(CLabel*)(l->GetNext());
                }
                CLabel *label=new CLabel(newstr,fin.tellg());
                LabelList.Add((CListItem*)(label));
                //cout<<"\t Label \""<<newstr<<"\" added"<<endl;
            }
            else
            {
                cout<<"[ERROR] Incorrect label name: \""<<str<<"\""<<endl;
                res=false;
            }
        }
        if (fin.peek()==EOF) break;
    }

    CLabel *label=new CLabel("EOF",fin.tellg());
    LabelList.Add((CListItem*)(label));    

    fin.seekg(start);
    //cout<<"Moving to beginning of file"<<endl;
    return res;
}

//does work exept -e option
bool Test(LongString str, CList &varlist1, CList &varlist2)
{
    LongString oldstr, newstr, newstr2, newstr3;
    LongString method;
    strcpy(method, str);
    if (str[0]==0) return false;
    if (!SeparateString(method, newstr, newstr2))
    {
        return true;
    }
    if (!SeparateString(newstr2, oldstr, newstr3))
    {
        if (!strcmp(method, "-e"))//if file exists ???
        {
            return false;
        }
        else if (!strcmp(method,"-n"))
        {
            if (newstr3[0]!=0) return true;
            else return false;
        }
        else return false;
    }
    strcpy(method, oldstr);
    if (!strcmp(method, "=="))
    {
        return (strcmp(newstr, newstr3)==0);
    }
    else if (!strcmp(method, "!="))
    {
        return (strcmp(newstr, newstr3)!=0);
    }
    else if (!strcmp(method, ">="))
    {
        return (strcmp(newstr, newstr3)>=0);
    }
    else if (!strcmp(method, "<="))
    {
        return (strcmp(newstr, newstr3)<=0);
    }
    else if (!strcmp(method, ">"))
    {
        return (strcmp(newstr, newstr3)>0);
    }
    else if (!strcmp(method, "<"))
    {
        return (strcmp(newstr, newstr3)<0);
    }
    else if (CorrectInt(newstr) && CorrectInt(newstr2))
    {
        if (!strcmp(method, "-eq"))
        {
            return atoi(newstr)==atoi(newstr2);
        }
        else if (!strcmp(method, "-ne"))
        {
            return atoi(newstr)!=atoi(newstr2);
        }
        else if (!strcmp(method, "-le"))
        {
            return atoi(newstr)<=atoi(newstr2);
        }
        else if (!strcmp(method, "-ge"))
        {
            return atoi(newstr)>=atoi(newstr2);
        }
        else if (!strcmp(method, "-lt"))
        {
            return atoi(newstr)<atoi(newstr2);
        }
        else if (!strcmp(method, "-gt"))
        {
            return atoi(newstr)>atoi(newstr2);
        }
        else return false;
    }
    else return false;
}

#define BRACKET_OPEN '('
#define BRACKET_CLOSE ')'

char ReadNumber(char *&str, double &x, char &t, char JustSign=0)
{
    /*returns 
    1 - +
    2 - -
    3 - *
    4 - /
    5 - %
    6 - function is going, 
    0 - end of string, 
    -1 - error*/
    char start = 0;
    char end = 0;
    char point = 0;
    char minus = 0;
    double y = 1;
    t = 0;
    if (!JustSign) x=0;
    if (str==NULL) return -1;
    while(*str!=0)
    {
        if (*str>='0' && *str<='9') //next number symbol
        {
            if (end || JustSign) return -1;
            start = 1;
            if (point)
            {
                y/=10;
                x = x + (*str-'0') * y;
            }
            else 
            {
                x = x * 10 + (*str-'0');
            }
        }
        else if (*str=='.' || *str ==',')//floating point
        {
            t = 1;
            if (end || JustSign) return -1;
            start = 1;
            if (point) return -1;
            else point = 1;
        }
        else if (*str=='-' || *str=='+' && !start && !JustSign)//unary minus
        {
            start = 1;
            minus = (*str == '-');
        }
        else if (start || JustSign)
        {
            if (!JustSign) x = (minus)?-x:x;
            if (*str>0 && *str<33)//space or other separator - end of number
            {
                end = 1;
            }//binary operators
            else if (*str=='+') {str++;return 1;}
            else if (*str=='-') {str++;return 2;}
            else if (*str=='*') {str++;return 3;}
            else if (*str=='/') {str++;return 4;}
            else if (*str=='%') //avaliable only with integer values
            {
                str++;
                if (point) return -1;
                else return 5;
            }
            else if(*str==BRACKET_CLOSE) {str++;return 7;}//closing bracket
            else return -1;
        }
        else if (*str==0) return 0;//end of string
        else if(*str==BRACKET_OPEN && !JustSign) {str++;return 6;}//opening bracket
        else if (*str<0 || *str>32) return -1;
        str++;
    }
    return 0;
}

bool Calc(LongString str, LongString res)
{
    double x[256];//number
    char   t[256];//types (0- int, 1 - float
    char   op[512];//operations
    
    int nx=0;//number of numbers
    int nop=0;//number of separators/operations
    char *s=str;
    int i,j=0;
    char start=1;
    op[nop]=ReadNumber(s, x[nx], t[nx]);
    while(nop>0 || start)
    {
        if (op[nop]==-1) 
        {
            strcpy(res,"[Error]");
            return -1;
        }
        if (op[nop]==6)//open bracket
        {
            nop++;
            op[nop]=ReadNumber(s, x[nx], t[nx]);
        }
        if (op[nop]==7)//close bracket
        {
            i=nop-1;
            j=nx-1;
            while(op[i]!=6 && i>0 && j>=0)
            {
                if (op[i]==1) {x[j]=x[j+1]+x[j];t[j]=t[j]|t[j+1];op[i]=op[i+1];}
                else if (op[i]==1) {x[j]=x[j+1]+x[j];t[j]=t[j]|t[j+1];op[i]=op[i+1];}
                else if (op[i]==2) {x[j]=x[j]-x[j+1];t[j]=t[j]|t[j+1];op[i]=op[i+1];}
                else if (op[i]==3) {x[j]=x[j]*x[j+1];t[j]=t[j]|t[j+1];op[i]=op[i+1];}
                else if (op[i]==4) 
                {
                    if (t[j]==t[j+1] && t[j]==0) x[j]=int(x[j]/x[j+1]);
                    else x[j]=x[j]/x[j+1];
                    t[j]=t[j]|t[j+1];
                    op[i]=op[i+1];
                }
                else if (op[i]==5) 
                {
                    if (t[j]==t[j+1] && t[j]==0) x[j]=int(x[j]) % int(x[j+1]);
                    else     
                    {
                        strcpy(res,"[Error]");
                        return -1;
                    }
                    t[j]=0;
                    op[i]=op[i+1];
                }
                j--;
                i--;
            }
            if (op[i]!=6) 
            {
                strcpy(res,"[Error]");
                return -1;
            }
            nop=i;
            nx=j+1;
            op[nop]=ReadNumber(s, x[nx], t[nx],1);
            if (op[nop]<6 && *s!=0) start=1;
            //nop++;
        }
        else if((op[nop]==1 || op[nop]==2 || op[nop]==0) && nx>0 && nop>0)//+ - end
        {
            if (op[nop-1]==1) //+
            {
                x[nx-1]=x[nx-1]+x[nx];
                t[nx-1]=t[nx-1]|t[nx];
                op[nop-1]=op[nop];
                if (op[nop]==0) {nop--;nx--;}
                else op[nop]=ReadNumber(s, x[nx], t[nx]);
            }
            else if (op[nop-1]==2) //-
            {
                x[nx-1]=x[nx-1]-x[nx];
                t[nx-1]=t[nx-1]|t[nx];
                op[nop-1]=op[nop];
                if (op[nop]==0) {nop--;nx--;}
                else op[nop]=ReadNumber(s, x[nx], t[nx]);
            }
            else if (op[nop-1]==3) //*
            {
                x[nx-1]=x[nx-1]*x[nx];
                t[nx-1]=t[nx-1]|t[nx];
                op[nop-1]=op[nop];
                nx--;nop--;
            }
            else if (op[nop-1]==4) // /
            {
                if (t[nx-1]==t[nx] && t[nx-1]==0) x[nx-1]=int(x[nx-1]/x[nx]);
                else x[nx-1]=x[nx-1]/x[nx];
                t[nx-1]=t[nx-1]|t[nx];
                op[nop-1]=op[nop];
                nx--;nop--;
            } 
            else if (op[nop-1]==5) // %
            {
                if (t[nx-1]==t[nx] && t[nx-1]==0) x[nx-1]=int(x[nx-1]) % int(x[nx]);
                else     
                {
                    strcpy(res,"[Error]");
                    return -1;
                }
                t[nx-1]=t[nx-1]|t[nx];
                op[nop-1]=op[nop];
                nx--;nop--;
            }  
            else if (op[nop]!=0)
            {
                nop++;
                nx++;
                op[nop]=ReadNumber(s, x[nx], t[nx]);
            }
        }
        else if((op[nop]==3 || op[nop]==4 || op[nop]==5) && nx>0 && nop>0)// * / %
        {
            if (op[nop-1]==1) //+
            {
                nop++;
                nx++;
                op[nop]=ReadNumber(s, x[nx], t[nx]);
            }
            else if (op[nop-1]==2) //-
            {
                nop++;
                nx++;
                op[nop]=ReadNumber(s, x[nx], t[nx]);
            }
            else if (op[nop-1]==3) //*
            {
                x[nx-1]=x[nx-1]*x[nx];
                t[nx-1]=t[nx-1]|t[nx];
                op[nop-1]=op[nop];
                op[nop]=ReadNumber(s, x[nx], t[nx]);
            }
            else if (op[nop-1]==4) // /
            {
                if (t[nx-1]==t[nx] && t[nx-1]==0) x[nx-1]=int(x[nx-1]/x[nx]);
                else x[nx-1]=x[nx-1]/x[nx];
                t[nx-1]=t[nx-1]|t[nx];
                op[nop-1]=op[nop];
                op[nop]=ReadNumber(s, x[nx], t[nx]);
            } 
            else if (op[nop-1]==5) // %
            {
                if (t[nx-1]==t[nx] && t[nx-1]==0) x[nx-1]=int(x[nx-1]) % int(x[nx]);
                else     
                {
                    strcpy(res,"[Error]");
                    return -1;
                }
                t[nx-1]=t[nx-1]|t[nx];
                op[nop-1]=op[nop];
                op[nop]=ReadNumber(s, x[nx], t[nx]);
            }  
            else if (op[nop]!=0)
            {
                nop++;
                nx++;
                op[nop]=ReadNumber(s, x[nx], t[nx]);
            }
        }
        if (nx>255 || nop>511) return 0;
        if (start)
        {
            start=0;
            nop++;
            nx++;
            op[nop]=ReadNumber(s, x[nx], t[nx]);
        }
    }

    if (nop>0) 
    {
        strcpy(res,"[Error]");
        return -1;
    }

    if (t[0]) sprintf(res, "%f", float(x[0]));
    else sprintf(res, "%i", int(x[0]));
    return true;
}
//add modifers, add extracting array indexes from vars
bool ResolveVariables(LongString oldstr, LongString newstr, CList &LocalVariableList, CList &VariableList)
{
    char *c=oldstr, *cn=newstr, *start, *end, *arrb, *arrend, *comm;
    LongString modifer, result;
    int Nstart, Ncount;
    CVariable *v;
    while (*c!=0)
    {
        arrb=NULL;
        arrend=NULL;
        comm=NULL;
        start=NULL;
        end=NULL;
        while (*c!=VARIABLE_START && *c!=0)
        {
            *cn=*c;
            c++;
            cn++;
        }
        if (*c==0) break;
        if (*(c+1)==VARIABLE_START) {*cn=*c;cn++;c++;c++;continue;}
        start=strchr(c, BRACKET_OPEN);
        if (start==NULL) {*cn=0;return false;}
        end=strchr(start+1, BRACKET_CLOSE);
        if (end==NULL) {*cn=0;return false;}
        arrb=strchr(start+1, ARRAY_OPEN);
        if (arrb!=NULL)
        {
            comm=strchr(arrb+1,COMMA);
            arrend=strchr(arrb, ARRAY_CLOSE);
        }
        else 
        {
            comm=NULL;
            arrend=NULL;
        }
        *start=0;
        *end=0;
        strcpy(modifer, c+1);

        if (arrb>end) arrb=NULL;
        if (arrend>end) arrend=NULL;
        if (arrb!=NULL && arrend==NULL || arrb==NULL && arrend!=NULL){*cn=0;return false;}
        if (arrend+1>end) {*cn=0;return false;}
        if (comm>end) comm=NULL;
        if (arrend!=NULL) 
        {
            if (arrb+1==arrend) {*cn=0;return false;}
            *arrb=0;
            *arrend=0;
            if (comm!=NULL) 
            {
                *comm=0;
            }
            if (!CorrectInt(arrb+1)) {*cn=0;return false;}
            Nstart=atoi(arrb+1);
            if (comm!=NULL)
            {
                if (!CorrectInt(comm+1)) {*cn=0;return false;}
                Ncount=atoi(comm+1);
            }
        }
        v=Search(start+1, LocalVariableList);
        LongString somestr;
        if (v) strcpy(somestr, v->value);
        else 
        {
            v=Search(start+1, VariableList);
            if (v) strcpy(somestr, v->value);
            else {somestr[0]=0;}
        }
        //apply modifers
        if (!strcmp(modifer, "")) {strcpy(result,somestr);}
        else if(!strcmp(modifer,"resolve")) 
        {
            ResolveVariables(somestr, result, LocalVariableList, VariableList);
        }
        else {*cn=0;return false;}
        //separate string
        if (arrend!=NULL)
        {
            if (Nstart-strlen(result)>0) Nstart=strlen(result);
            if (Nstart+Ncount-strlen(result)>0) Ncount=strlen(result)-Nstart;
            if (comm!=NULL) result[Nstart+Ncount]=0;
            strcpy(cn,result+Nstart);
            cn+=Ncount;
        }
        else 
        {
            strcpy(cn, result);
            cn+=strlen(result);
        }
        c=end+1;
    }
    *cn=0;
    return true;
}
//does work
CVariable *Search(LongString str, CList &varlist)
{
    CVariable *v=(CVariable*)varlist.GetFirst();
    while (v!=NULL)
    {
        if (!strcmp(v->name,str)) return v;
        v=(CVariable*)v->GetNext();
    }
    return NULL;
}

//we need to update next statements:
//set: make ariphmetic
//
//add elif
//add plugin calls and opening picture
//interpret one line of command (no more than one command in it except if statement)
int Command(ifstream &fin, 
            CList &LabelList, 
            CList &VariableList, 
            CList &LocalVariableList, 
            CList &Plugins, 
            SDLLs Dlls, 
            TImage &Picture, 
            TColorImage &ColorPicture, 
            SApproximation Approximation, 
            CList &Graphics, 
            CList &Layers, 
            LongString str, 
            int previousstate, 
            bool &echo)
{
    String newstr,newstr2,newstr3;
    char *ch;
    bool echonow=true;
    RemoveSpaces(str, newstr);
    RemoveComments(newstr,newstr2);
    RemoveSpaces(newstr2, newstr3);
    ResolveVariables(newstr3, str, LocalVariableList, VariableList);
    if (str[0]==DO_NOT_ECHO)
    {
        newstr[0]=0;
        strcpy(newstr3, str+1);
        RemoveSpaces(newstr3, str);
        echonow=false;
    }
    if (echo && echonow) cout<<str<<endl;
    if (str[0]==0) return previousstate;
    //if it is label definition
    ch=str;
    if (*ch==LABEL_DEFINE)//label have been already defined
    {
    }
    else
    {
        if (SeparateString(str, newstr,newstr2))
        {
            if (!strcmp(newstr,"if"))//if statement
            {
                if (newstr2[0]!=BRACKET_OPEN)
                {
                    cout<<"[ERROR] expression syntax error in if statemnt, opening bracket missing"<<endl;
                }
                else
                {
                    int spacenumber=1;
                    ch=newstr2+1;
                    while(*ch!=0 && spacenumber >0)
                    {
                        if (*ch==BRACKET_OPEN) spacenumber++;
                        else if (*ch==BRACKET_CLOSE) spacenumber--;
                        ch++;
                    }
                    if (*ch==0) 
                    {
                        cout<<"[ERROR] expression syntax error in if statemnt, closing bracket missing"<<endl;
                    }
                    else
                    {
                        *(ch-1)=0;
                        strcpy(newstr, ch+1);
                        if (Test(newstr2+1, VariableList, LocalVariableList))
                        {
                            //cout<<"\t If statement tested"<<endl;
                            RemoveSpaces(newstr, newstr2);
                            if (echo) cout<<"\t";
                            int x=Command(fin, LabelList, VariableList, LocalVariableList, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers, newstr2, 0, echo);
                            if (x==-1) return -1;
                            return 1;
                        }
                        else
                        {
                            //cout<<"\tIf statement test waiting for else..."<<endl;
                            return 2;
                        }
                    }
                }
                cout<<"\t if found"<<endl;
            }
            else if (!strcmp(newstr,"else"))//else 
            {
                if (previousstate!=2 && previousstate!=1)
                {
                    cout<<"[ERROR] Misplaced else"<<endl;
                }
                else if (previousstate==2)
                {
                    int x=Command(fin, LabelList, VariableList, LocalVariableList, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers, newstr2, 0, echo);
                    if (x==-1) return -1;
                    return 0;
                }
            }
            else if(!strcmp(newstr,"goto"))//goto
            {
                if (CorrectIdentifer(newstr))
                {
                    CLabel *l=(CLabel*)LabelList.GetFirst();
                    while (l!=NULL)
                    {
                        if (!strcmp(l->name,newstr2))
                        {
                            fin.seekg(l->position);
                            //cout<<"\t Moving to \""<<newstr2<<"\""<<endl;
                            return 0;
                        }
                        l=(CLabel*)(l->GetNext());
                    }
                    cout<<"[ERROR] Incorrect label name: \""<<newstr2<<"\""<<endl;
                }
                else 
                {
                    cout<<"[ERROR] Incorrect label name: \""<<newstr2<<"\""<<endl;
                }
            }
            else if (!strcmp(newstr,"set"))//set
            {
                ch = FindSymbol(newstr2, '=');
                bool onlyprompt=false;
                if (ch==NULL || *(ch+1)==0)
                {
                    onlyprompt=true;
                    ch=LastChar(newstr2);
                }
                *ch=0;
                if (onlyprompt)
                {
                    newstr3[0]=0;
                }
                else
                {
                    strcpy(newstr,ch+1);
                    RemoveSpaces(newstr, newstr3);//newstr3 is string we need to store
                }
                LongString param;
                bool local=false, global=false, ariphmetic=false, prompt=false;
                long i=0;
                while (SeparateString(newstr2, param, newstr))
                {
                    if (newstr[0]==0) break;
                    if (param[0]==MODIFER)
                    {
                        for (i=1;strlen(param)-i>0;i++)
                        {
                            switch(param[i])
                            {
                                case 'G': global=true;break;
                                case 'L': local=true;break;
                                case 'A': ariphmetic=true;break;
                                case 'P': prompt=true;break;
                                default: cout<<"[ERROR] Unknown modifer \'"<<param[i]<<"\'"<<endl;break;
                            }
                        }
                    }
                    else if (param[0]==0)
                    {
                        break;
                    }
                    else 
                    {
                        cout<<"[ERROR] Syntax error in \'set\' command modifer waiting: \""<<param<<"\""<<endl;
                    }
                    strcpy(newstr2, newstr);
                }
                //in the end newstr2 contains name of variable
                CVariable *var;
                if (onlyprompt && !prompt)
                {
                    cout<<"!\t Syntax error /P waiting"<<endl;
                    return 100;
                }
                if (ariphmetic)
                {
                    Calc(newstr3, newstr);
                }
                else if (prompt)
                {
                    if (newstr3[0]==0) cout<<"Please input value for \""<<newstr2<<"\" variable: ";
                    else cout<<newstr3;
                    cin.getline(newstr,100);
                }
                else
                {
                    strcpy(newstr, newstr3);
                }
                if (!global) local=true;
                if (local)
                {
                    var=Search(newstr2, LocalVariableList);
                    if (var==NULL) 
                    {
                        var=new CVariable(newstr2);
                        //strcpy(var->name, newstr);
                        LocalVariableList.Add(var);
                    }
                    strcpy(var->value, newstr);
                    //cout<<"\t Added Local variable \""<<var->name<<"\" with value \""<<var->value<<"\""<<endl;
                }
                if (global)
                {
                    var=Search(newstr2, VariableList);
                    if (var==NULL) 
                    {
                        var=new CVariable(newstr2);
                        //strcpy(var->name, newstr);
                        VariableList.Add(var);
                    }
                    strcpy(var->value, newstr);
                    //cout<<"\t Added global vatiable \""<<var->name<<"\" with value \""<<var->value<<"\""<<endl;
                }
            }
            else if (!strcmp(newstr,"call"))//call
            {
                //cout<<"\t External script call; \""<<newstr2<<"\""<<endl;
                return Interpret(newstr2, VariableList, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);
            }
            else if (!strcmp(newstr,"echo"))//echo
            {
                if (!strcmp(newstr2, "on"))
                {
                    echo=true;
                }
                else if (!strcmp(newstr2,"off"))
                {
                    echo = false;
                }
                else
                {
                    RemoveQuotes(newstr2, newstr3);
                    cout<<newstr3<<endl;
                }
            }
            else if (!strcmp(newstr,"cd"))//cd
            {
                LongString tmpstr="cd ";
                strcat(tmpstr, newstr2);
                system(tmpstr);
            }
            else if (!strcmp(newstr,"system"))//system
            {
                system(newstr2);
            }
            else if (!strcmp(newstr, "logecho"))
            {
                OpenLog();
                WriteLogFontColor("#004400");
                WriteLog(newstr2);
                WriteLogFontEnd();
                WriteLogNewLine();
                CloseLog();
            }
            else if(!strcmp(newstr,"open"))
            {
                OpenLog();
                //strcat(function, b2);
                //strcat(function, "\", &Picture)");
                WriteLogFunctionCall("ReadData.dll", "ReadData");
                LPSYSTEMTIME Time1 = new _SYSTEMTIME;
                LPSYSTEMTIME Time2 = new _SYSTEMTIME;
                GetLocalTime(Time1);
                LongString str="";
                int a = Dlls.ReadData.ReadData(newstr2, &ColorPicture, str); 
                GetLocalTime(Time2);
                WriteLogFunctionCallTime(Time1, Time2);
                WriteLog(a);
                WriteLogFunctionCallEnd();
                WriteLogFunctionString(str);
                CloseLog();
                if (!a) return 0;
                else return 101;
            }
            else if(!strcmp(newstr,"save"))
            {
                return 0;
            }
            else//probably plugin call
            {
                LongString newstr4;
                if (SeparateString(newstr2, newstr3, newstr4))
                {
                    RunFunctionByName(newstr, newstr3, (CPlugIn*)Plugins.GetFirst(), &Approximation, &Picture, &ColorPicture, &Graphics, &Layers, Dlls.Input.FileInput, true, newstr4);
                }
                else 
                {
                    RunFunctionByName(newstr, newstr3, (CPlugIn*)Plugins.GetFirst(), &Approximation, &Picture, &ColorPicture, &Graphics, &Layers, Dlls.Input.ConsoleInput, true);
                }
			    bool q=RunFunctionByName(newstr, newstr3, (CPlugIn*)Plugins.GetFirst(), &Approximation, &Picture, &ColorPicture, &Graphics, &Layers);
			    if (q) return 0;
			    else 
                {
                    cout<<"[ERROR] Cannot call plugin method \""<<newstr3<<"\" in \""<<newstr<<"\""<<endl;
                    return 102;
                }
            }
        }
        else
        {
            //string is "echo." - just output new line
            if (!strcmp(str, "echo.")) 
            {
                cout<<endl;
            }
            else if(!strcmp(str,"halt") || !strcmp(str,"exit")) 
            {
                return -1;
            }
            else if (!strcmp(str, "ls") || !strcmp(str, "dir"))
            {
                system("dir");
            }
            else cout<<"[ERROR] Unknown command \""<<str<<"\""<<endl;
        }
    }
    return 0;
}

int Interpret(char *fname, CList &VariableList, CList &Plugins, SDLLs Dlls, TImage &Picture, TColorImage &ColorPicture, SApproximation Approximation, CList &Graphics, CList &Layers)
{
    CLabel *label=NULL;
    CVariable *var=NULL;
    bool echo=true;
    LongString str;
    int res=0;
    CList LabelList, LocalVariableList;
    OpenLog();
    WriteLogTableColor("#aaaabb");
    WriteLogRow();
    WriteLogCell();
    WriteLogFontColor("#aa0000");
    WriteLog("Interpreting file: ");
    WriteLog(fname);
    WriteLogFontEnd();
    WriteLogNewLine();
    CloseLog();

    ifstream fin(fname);
    GetLabels(fin, LabelList);
    fin.close();
    fin.open(fname);
    while (fin.good() && res!=-1)
    {
        str[0]=0;
        fin.getline(str, 100);
        res=Command(fin, LabelList, VariableList, LocalVariableList, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers, str, res, echo);
    }
    fin.close();
    OpenLog();
    WriteLogCellEnd();
    WriteLogRowEnd();
    WriteLogTableEnd();
    WriteLogNewLine();
    CloseLog();
    return res;
}