#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <stack>
#include <algorithm>
using namespace std;




vector<char> character={'k','i','l','c','#','o'};//���������
struct lr_action
{
    int state;
    char input;//����
    string action;//����
};
struct generate_change
{
    string entirety_left;  //��Ŀ��ĳ����ʽ����
    string point_left;  //��Ŀ��ĳ����ʽ�Ҳ���С������󲿷�
    string point_right;;  //��Ŀ��ĳ����ʽ�Ҳ���С������Ҳ���   �������ֹ�ͬȷ����С�����λ��
    string fsc; // ǰ�������
};
struct event_relation
{
    char input ;  //
    string name_next; //��һ����Ŀ������
};
struct event  //��Ŀ
{
    string name;  //��Ŀ���  I1�� I2��......
    vector<generate_change> generate;  //����ʽ
    vector<event_relation> relation;
};


//����������޹��ķ�����չ�ķ�
void GetExpendedGrammar(ifstream &f, vector<string> &g){
    //g.push_back("S*->S");
    while(!f.eof()){
        char temp_string[100];
        while(f.getline(temp_string,100)){
            g.push_back(temp_string);
        }
    }
}
//��ӡstring��������
void PrintVectorString(vector<string> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<endl;
    }
}
//��ӡ��Ŀ��
void PrintEventGroup(vector<event> e){
    for(int i=0;i<e.size();i++){
        cout<<"---------------"<<endl;
        cout<<"��Ŀ"<<e[i].name+":"<<endl;
        for(int j=0; j<e[i].generate.size();j++){
            cout<<""+e[i].generate[j].entirety_left+"->"+e[i].generate[j].point_left+"��"+e[i].generate[j].point_right+","+e[i].generate[j].fsc<<endl;
        }
    }
     cout<<"---------------"<<endl;
}        
//�ж�������Ŀ������ʽ�Ƿ����
bool IsEventEqual(event a, event b){
    if(!a.generate.size()==b.generate.size()){
        return false;
    }
    else {
        int mark = 0;
        for(int i=0;i<a.generate.size();i++){
            for(int j=0;j<b.generate.size();j++){
                if(a.generate[i].entirety_left==b.generate[j].entirety_left&&
                    a.generate[i].point_left==b.generate[j].point_left&&
                    a.generate[i].point_right==b.generate[j].point_right&&
                    a.generate[i].fsc==b.generate[j].fsc){
                    mark++;
                }
            }
        }
        if(mark==a.generate.size()){
            return true;
        }
        else{
            return false;
        }
    }
}
//�ж���Ŀ�����Ƿ��Ѿ���һ�����ݵ���Ŀ
bool ISEventRepeat(vector<event> e_g,event e){ //�ظ�����true δ�ظ�����false
    for(int i=0 ;i<e_g.size();i++){
        if(IsEventEqual(e_g[i],e)){
            return true;
        }
    }
    return false;
}
//�����Ѿ��ظ�����Ŀ��
string GetRepeatName(vector<event> e_g,event e){
    for(int i=0 ;i<e_g.size();i++){
        if(IsEventEqual(e_g[i],e)){
            return e_g[i].name;
        }
    }
    return "error";
    
}
//�ж�����ʽ�����Ƿ��Ѿ���һ�����ݵ�����ʽ
bool ISGengRepeat(vector<generate_change> v_g,generate_change g){//true��ʾ�Ѿ�����
    int mark =0;
    for(int i=0;i<v_g.size();i++){
        if(v_g[i].fsc==g.fsc&&
        v_g[i].entirety_left==g.entirety_left&&
        v_g[i].point_left==g.point_left&&
        v_g[i].point_right==g.point_right)
        {
            mark=1;
            break;
        }
    }
    if(mark) return true;
    else return false;

}
//������չ�ķ������Ŀ��
void GetEventGroup(vector<event> &e, vector<string> gra){
    event event_temp;
    event_temp.name="I0";
    
    for(int i=0;i<gra.size();i++){
        
        if(gra[i][0]=='H'){
            generate_change temp;
            temp.entirety_left="H";
            temp.point_left="";
            temp.point_right=gra[i].substr(3);
            temp.fsc="#";
            event_temp.generate.push_back(temp);
        }
        if(gra[i][0]=='S'){
            generate_change temp;
            temp.entirety_left="S";
            temp.point_left="";
            temp.point_right=gra[i].substr(3);
            temp.fsc="#";
            event_temp.generate.push_back(temp);
            //cout<<"1"<<endl;
        }
    }
    queue<event> q_event;
    q_event.push(event_temp);
    e.push_back(event_temp);
    //debug
    //cout<<"��Ŀ����"<<event_temp.name<<endl;
    while(!q_event.empty())
    {  
        vector<char>  first_char;
        first_char.clear();
        for(int i=0;i<q_event.front().generate.size();i++){
            int mark =0;
            for(int j=0;j<first_char.size();j++){
                if(q_event.front().generate[i].point_right[0]!='\0'){
                    if(first_char[j]==q_event.front().generate[i].point_right[0]){
                        mark =1;
                    }
                }
                else{
                    continue;
                }
            }
            if(!mark){
                if(q_event.front().generate[i].point_right[0]!='\0'){
                    first_char.push_back(q_event.front().generate[i].point_right[0]);
                }
                
            }
        }//��ӡ���
         /*
        cout<<"-------------"<<endl;
        for(int i=0;i<first_char.size();i++){
            
            cout<<first_char[i]<<endl;
        }
        cout<<"-------------"<<endl;
        */
        if(!first_char.empty()){
           
            for(int i=0;i<first_char.size();i++){
                event_temp.generate.clear(); 
                event_temp.relation.clear();
                event_temp.name="I"+to_string(e.size());            
                for(int j=0;j<q_event.front().generate.size();j++){
                    generate_change gene;
                    event_relation e_rela;
                    if(q_event.front().generate[j].point_right[0]==first_char[i]){
                        //cout<<event_temp.generate[j].entirety_left<<"->"<<event_temp.generate[j].point_left<<"."<<event_temp.generate[j].point_right<<","<<event_temp.generate[j].fsc<<endl;
                        gene.entirety_left=q_event.front().generate[j].entirety_left;
                        gene.fsc=q_event.front().generate[j].fsc;
                        gene.point_left=q_event.front().generate[j].point_left+q_event.front().generate[j].point_right[0];
                        
                        if(q_event.front().generate[j].point_right[1]=='\0'){
                            gene.point_right="";
                            
                        }
                        else{
                            gene.point_right=q_event.front().generate[j].point_right.substr(1);
                        }
                        if(!ISGengRepeat(event_temp.generate,gene)){
                            event_temp.generate.push_back(gene);
                        }
                        else {
                            continue;
                        }
                        if(q_event.front().generate[j].point_right[1]<='Z'&&q_event.front().generate[j].point_right[1]>='A'){
                            for(int z=0;z<gra.size();z++){
                                if(gra[z][0]==q_event.front().generate[j].point_right[1]){
                                    gene.entirety_left=q_event.front().generate[j].point_right[1];
                                    if(q_event.front().generate[j].point_right[2]!='\0'){
                                       gene.fsc=q_event.front().generate[j].point_right[2];
                                    }
                                    else{
                                        gene.fsc=q_event.front().generate[j].fsc;
                                    }
                                    gene.point_left="";
                                    gene.point_right=gra[z].substr(3);
                                    generate_change temp_change;
                                    temp_change.point_right=gene.point_right;
                                    while(temp_change.point_right[0]<='Z'&&temp_change.point_right[0]>='A'){
                                        temp_change.entirety_left=temp_change.point_right[0];
                                        //cout<<temp_change.entirety_left;
                                        if(temp_change.point_right[1]=='\0'){
                                            temp_change.fsc=gene.fsc;
                                        }
                                        else{
                                            temp_change.fsc=gene.point_right[1];
                                        }
                                        temp_change.point_left="";
                                            for(int w=0;w<gra.size();w++){
                                                if(gra[w][0]==temp_change.entirety_left[0])
                                                {
                                                    temp_change.point_right=gra[w].substr(3);
                                                }
                                            }
                                        if(!ISGengRepeat(event_temp.generate,gene)){
                                            event_temp.generate.push_back(temp_change);
                                        }   
                                    }
                                }
                                if(!ISGengRepeat(event_temp.generate,gene)){
                                    event_temp.generate.push_back(gene);
                                }
                                else {
                                    continue;
                                }    
                            }
                        }
                    }
                    e_rela.input=first_char[i];
                    e_rela.name_next=event_temp.name;
                    for(int z=0;z<e.size();z++){
                        if(e[z].name==q_event.front().name){
                            int mark=1;
                            for(int w=0;w<e[z].relation.size();w++){
                                if(e_rela.input==e[z].relation[w].input){
                                    mark=0;
                                }
                            }
                            if(mark){
                                e[z].relation.push_back(e_rela);
                            }
                        }
                    }    
                }     
                /* ��ӡ���
                cout<<event_temp.name<<endl;
                for(int j=0;j<event_temp.generate.size();j++){
                    cout<<event_temp.generate[i].entirety_left<<"->"<<event_temp.generate[i].point_left<<"��"<<event_temp.generate[i].point_right<<","<<event_temp.generate[i].fsc<<endl;
                }
                */
                if(!ISEventRepeat(e,event_temp)){
                    e.push_back(event_temp);       
                    q_event.push(event_temp);//?
                }
                else{
                    for(int j=0;j<e.size();j++){
                        if(q_event.front().name==e[j].name){
                            event_relation temp_re;
                            temp_re.input=first_char[i];
                            temp_re.name_next=GetRepeatName(e,event_temp);
                            e[j].relation.pop_back();
                            e[j].relation.push_back(temp_re);
                        }
                    }
                }   
            }
        }
        q_event.pop();
    }
}
//��ӡ��Ŀ���ϵ
void PrintEventRelation(vector<event> e){
    cout<<"��Ŀ֮���ϵ����:"<<endl;
    for(int i =0 ;i<e.size();i++){
        for(int j=0;j<e[i].relation.size();j++){
            cout<<e[i].name<<"   "<<e[i].relation[j].input<<"   "<<e[i].relation[j].name_next<<endl;
        }
    }
}
//����LR��1��������
void GetLrList(vector<event> e,vector<char> &line_action,vector<char> &line_Goto,vector<lr_action> &l_a,vector<string> gra){    
    for(int i=0;i<e.size();i++){
        for(int j =0;j<e[i].relation.size();j++){
            //action��
            if(e[i].relation[j].input<='z'&&e[i].relation[j].input>='a'){
                int mark =0;
                for(int z=0;z<line_action.size();z++){
                    if(e[i].relation[j].input==line_action[z]){
                        mark=1;
                    }
                    else{
                        continue;
                    }
                }
                if(!mark){
                    line_action.push_back(e[i].relation[j].input);
                }
            }

            //goto��
            if(e[i].relation[j].input<='Z'&&e[i].relation[j].input>='A'){
                int mark =0;
                for(int z=0;z<line_Goto.size();z++){
                    if(e[i].relation[j].input==line_Goto[z]){
                        mark=1;
                    }
                    else{
                        continue;
                    }
                }
                if(!mark){
                    line_Goto.push_back(e[i].relation[j].input);
                }
            }
        }
    }
    sort(line_action.begin(),line_action.end());
    line_action.push_back('#');

    
    for(int i=0;i<e.size();i++){
        for(int j=0;j<e[i].relation.size();j++){
            if(e[i].relation[j].input>='A'&&e[i].relation[j].input<='Z'){
                lr_action temp_l_a;
                temp_l_a.state=i;
                temp_l_a.input=e[i].relation[j].input;
                temp_l_a.action=e[i].relation[j].name_next.substr(1);
                l_a.push_back(temp_l_a);
            }
            else {
                for(int z=0;z<line_action.size();z++){
                    if(e[i].relation[j].input==line_action[z]){
                        lr_action temp_l_a;
                        temp_l_a.state=i;
                        temp_l_a.input=line_action[z];
                        temp_l_a.action="S"+e[i].relation[j].name_next.substr(1);
                        l_a.push_back(temp_l_a);
                    }
                }
            }
        }
        for(int j=0;j<e[i].generate.size();j++){
            if(e[i].generate[j].point_right==""){
                for(int z=0;z<gra.size();z++){
                    if(gra[z].substr(3)==e[i].generate[j].point_left&&gra[z].substr(0,1)==e[i].generate[j].entirety_left){
                        if(e[i].generate[j].fsc=="#"&&e[i].generate[j].point_left=="S"){
                            lr_action temp_l_a;
                            temp_l_a.state=i;
                            temp_l_a.input='#';
                            temp_l_a.action="acc";
                            l_a.push_back(temp_l_a);
                        }
                        else{
                            lr_action temp_l_a;
                            temp_l_a.state=i;
                            temp_l_a.input=e[i].generate[j].fsc[0];
                            temp_l_a.action="r"+to_string(z);
                            l_a.push_back(temp_l_a);
                        }
                    }
                }
            }
        }
    }
}
// ��ӡLR��1����

void PrintLrList(vector<char> line_action,vector<char> line_Goto,vector<lr_action> l_a,vector<event> e){
    cout<<"     ";
    for(int i=0;i<line_action.size();i++){
        cout<<line_action[i]<<"      ";
    }
    for(int i=0;i<line_Goto.size();i++){
       
        cout<<line_Goto[i]<<"      ";
    }
    cout<<endl;
    for(int i=0;i<e.size();i++){
        cout<<i<<"   ";
        if(i<10){
            cout<<" ";
        }
        for(int j=0;j<line_action.size();j++){
            int mark=0;
            string out_action;
            for(int z=0;z<l_a.size();z++){
                if(l_a[z].state==i&&l_a[z].input==line_action[j]){
                    mark=1;
                    out_action=l_a[z].action;
                }
            }
            if(mark){
                cout<<out_action;
                for(int z=0;z<7-out_action.size();z++){
                    cout<<" ";
                }
            }
            else{
                cout<<"       ";
            }
        }
        for(int j=0;j<line_Goto.size();j++){
            int mark=0;
            string out_action;
            for(int z=0;z<l_a.size();z++){
                if(l_a[z].state==i&&l_a[z].input==line_Goto[j]){
                    mark=1;
                    out_action=l_a[z].action;
                }
            }
            if(mark){
                cout<<out_action;
                for(int z=0;z<7-out_action.size();z++){
                    cout<<" ";
                }
            }
            else{
                cout<<"       ";
            }
        }
        cout<<endl;
    }
}
// �������
int GetLine(string token_line){
    char str[2]={'0','\0'};
    int line;
    for(int i=0;i<token_line.size();i++){
        str[i]=token_line[i];
        if(token_line[i]==' '){
            break;
        }
    }
    line =atoi(str) ;
    return line;
}
// �������
char GetClass(string token_line){ 
    char str;
    int start;
    for(int i=0;i<token_line.size();i++){
        if(token_line[i]==' '){
            start=i;
            break;
        }
    }
    int i=start+1;
    return token_line[i];
}

// ��ȡtoken�ļ�  ���������ͽ���ת��
//o->�����
//i->��ʶ��
//c->����
//l->���
//k->�ؼ���
void GetTokenTurn(ifstream &f_token,vector<string> &token,vector<string> &token_turn){
    while(!f_token.eof()){
        char temp_string[100];
        while(f_token.getline(temp_string,100)){
            token.push_back(temp_string);
        }
    }
    
    int line;
    line=GetLine(token[token.size()-1]);
    for(int i=1;i<=line;i++){
        string str_temp="";
        for(int j=0;j<token.size();j++){
            if(i==GetLine(token[j])){
                str_temp=str_temp+GetClass(token[j]);
            }
        }
        str_temp=str_temp+'#';
        token_turn.push_back(str_temp);
    }
}
//���token_turn�Ƿ񸴺��﷨����ӡ
void TokenTurnanalysis(vector<string> token_turn,vector<lr_action> l_a,vector<string> gra){
    int count=0;
    int step;
    string s_input;
    string action="";
    string Goto="";
    for(int i=0;i<token_turn.size();i++){    
        stack<int> s_state , state_out;
        stack<char> s_sign, sign_out;
        s_state.push(0);
        s_sign.push('#');
        action="";

        step=1;
        s_input=token_turn[i];
        cout<<"Ҫ����ķ��Ŵ�Ϊ��"<<s_input<<endl;
        cout<<"����    ����ջ          ״̬ջ                  ������Ŵ�          ACTION          GOTO"<<endl;
        int mark0=0;
        while (action!="acc"){
            int mark1=0;
            for(int j=0;j<l_a.size();j++){
                if(l_a[j].input==s_input[0]&&l_a[j].state==s_state.top()){  
                    action=l_a[j].action;
                    mark1=1;
                }
            }
            if(!mark1){
                mark0=1;
                break;
            }
            //����
            cout<< step<<"      ";
            sign_out=s_sign;
            state_out=s_state;
            string  temp;
            //����ջ
            while(!sign_out.empty()){
                temp=temp+sign_out.top();
                temp=temp+" ";
                sign_out.pop();
                
            }
            reverse(temp.begin(),temp.end());
            cout<<temp;
            for(int j=0;j<16-2*s_sign.size();j++){
                cout<<" ";
            }
            temp.clear();
            //״̬ջ
            int count1=0; //��������λ��״̬�˴���Ҫ�����޸ģ����ڴ�ӡ����
            while(!state_out.empty()){
                string temp_str;
                temp_str=to_string(state_out.top());
                if(state_out.top()>9){
                    count1++;
                }

                reverse(temp_str.begin(),temp_str.end());
                temp=temp+temp_str;
                temp=temp+" ";
                state_out.pop();
                
            }
            reverse(temp.begin(),temp.end());
            cout<<temp;
            for(int j=0;j<25-2*s_state.size()-count1;j++){
                cout<<" ";
            }
            temp.clear();
            //���Ŵ�
            cout<<s_input;
            for(int j=0;j<20-s_input.size();j++){
                cout<<" ";
            }
            //����
            cout<<action;
            for(int j=0;j<16-action.size();j++){
                cout<<" ";
            }
            if(action=="acc"){
                cout<<endl;
                break;
            }
            else if(action[0]=='S'){
                s_sign.push(s_input[0]);
                s_input=s_input.substr(1);
                s_state.push(atoi(action.substr(1).c_str()));
            }
            else if(action[0]=='r'){

                for(int j=0;j<gra[atoi(action.substr(1).c_str())].size()-3;j++){
                    s_sign.pop();
                    s_state.pop();
                }
                s_sign.push(gra[atoi(action.substr(1).c_str())][0]);
                for(int j=0;j<l_a.size();j++){
                    if(l_a[j].input==s_sign.top()&&l_a[j].state==s_state.top()){
                        Goto=l_a[j].action;
                    }
                }
                s_state.push(atoi(Goto.c_str()));
                cout<<Goto;
                Goto="";
            }
            cout<<endl;
            step++;
        }
        if(mark0){
            break;
        }
        count++;
        cout<<"------------------------------------------";
    }
    cout<<endl;
    if(count==token_turn.size()){
        cout<<"yes!    ��ǰToken�����ķ�����"<<endl;
    }
    else{
        cout<<"no!     ��ǰToken�������ķ�����"<<endl;
        cout<<"��"<<count+1<<"�г���"<<endl;
    }
    
}
int main(){
    vector<string> grammar;  //�������޹��ķ����ع��ķ�
    vector<string> token;  //token �б�
    vector<string> token_turn; //token ת���б�
    vector<event>  event_group; //��Ŀ��
    vector<char> action;//��ͷ
    vector<char> Goto;//��ͷ
    vector<lr_action> L_A;
    ifstream fin_grammar("grammar.txt");
    if(!fin_grammar){
        cout<<"�ķ��ļ���ʧ��!"<<endl;
    }
    else{
        cout<<"�ķ��ļ��򿪳ɹ�!"<<endl;
    //����������޹��ķ�����չ�ķ�
    GetExpendedGrammar(fin_grammar,grammar);    
    }
    fin_grammar.close();
    //���token
    ifstream fin_token("token.txt");
    if(!fin_token){
        cout<<"token�ļ���ʧ��!"<<endl;
    }
    else{
        cout<<"token�ļ��򿪳ɹ�!"<<endl;
    GetTokenTurn(fin_token,token,token_turn);
    }
    //��ӡת����token
    for(int i=0;i<token_turn.size();i++){
        cout<<token_turn[i]<<endl;
    }
    
    //��ӡ������õ���չ�ķ�
    PrintVectorString(grammar);

    //����չ�ķ������Ŀ��
    GetEventGroup(event_group,grammar);
    
    //��ӡ��Ŀ��
    //cout<<event_group.size();
    
    PrintEventGroup(event_group);

    //��ӡ��Ŀ֮��Ĺ�ϵ
    
    PrintEventRelation(event_group);
    //���LR��
    GetLrList(event_group,action,Goto,L_A,grammar);
    //��ӡ���
    /*
    for(int i=0;i<action.size();i++){
        cout<<action[i]<<"   ";
    }
    for(int i=0;i<Goto.size();i++){
        cout<<Goto[i]<<"   ";
    }*/
    //��ӡLR��
    PrintLrList(action,Goto,L_A,event_group);
    //��������
    TokenTurnanalysis(token_turn,L_A,grammar);

    system("pause");
    
    return 0;   

}
