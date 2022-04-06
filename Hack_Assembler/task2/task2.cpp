//this program simplifies the input file too
#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<algorithm>
using namespace std;
class Symbols{
    string *symbol; //dynamic array to store labels and variables
    int *address;   // dynamic array to store addresses of labels and variables
    int i =0, j = 16;
public:
    //initializing symbol and address array according to line number of input file
    Symbols(const char *f){     
        ifstream fin(f);
        string line;
        int lineNo = 0;
        while(getline(fin,line))
            lineNo++;
            address = new int[lineNo++];
            symbol = new string[lineNo++];
            fin.close();			
    }
    // on encountering a predefined symbol, modifying it to it's value
    void predefined(const char *f){
        ifstream fin(f);
        ofstream temp("temp.asm");
        string line;
        while(getline(fin,line)){
            size_t A = line.find("@");
            if(A != string::npos){
                string pre;
                stringstream numString(line.substr(A + 1));
                numString >> pre;          
                if(pre == "R0"){
                    pre.replace(0,2,"0");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R1"){
                    pre.replace(0,2,"1");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R2"){
                    pre.replace(0,2,"2");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R3"){
                    pre.replace(0,2,"3");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R4"){
                    pre.replace(0,2,"4");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R5"){
                    pre.replace(0,2,"5");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R6"){
                    pre.replace(0,2,"6");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R7"){
                    pre.replace(0,2,"7");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R8"){
                    pre.replace(0,2,"8");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R9"){
                    pre.replace(0,2,"9");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R10"){
                    pre.replace(0,3,"10");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R11"){
                    pre.replace(0,3,"11");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R12"){
                    pre.replace(0,3,"12");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R13"){
                    pre.replace(0,3,"13");
               	    temp << "@" << pre << '\n';
                }
                else if(pre == "R14"){
                    pre.replace(0,3,"14");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "R15"){
                    pre.replace(0,3,"15");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "SCREEN"){
                    pre.replace(0,6,"16384");
               	    temp << "@" << pre << '\n';
                }
                else if(pre == "KBD"){
                    pre.replace(0,3,"24576");
               	    temp << "@" << pre << '\n';
                }
                else if(pre == "SP"){
               	    pre.replace(0,2,"0");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "LCL"){
                    pre.replace(0,3,"1");
                    temp << "@" << pre << '\n';
                }
                else if(pre == "ARG"){
                    pre.replace(0,3,"2");
               	    temp << "@" << pre << '\n';
                }
                else if(pre == "THIS"){
                    pre.replace(0,4,"3");
               	    temp << "@" << pre << '\n';
                }
                else if(pre == "THAT"){
                    pre.replace(0,4,"4");
               	    temp << "@" << pre << '\n';
                }
                else
                    temp << line << '\n';
            }    
            else
                temp << line << '\n';
        }    
        fin.close();
        temp.close();
        remove(f);
        rename("temp.asm",f);
    }
    //storing labels in symbol array and it's address in adrress array
    void labels(const char *f){
        ifstream fin(f);
        string line;
        int lineNo = 0;
        int count = 0;
        while(getline(fin,line)){
            size_t L = line.find("(");
            size_t L1 = line.find(")");
            if(L != string::npos){
                string label;
                stringstream numString(line.substr((L + 1),(L1-1)));   //extracting the exact label name
                numString >> label;
                symbol[i] = label;
                address[i] = lineNo - count;     
                i++;
                count++; 
            }
            lineNo++;
        }
        fin.close();
    }
    //on encountering the label modifying it to it's value
    void labelCheck(const char *f){
        ifstream fin(f);
        ofstream temp("temp.asm");
        string line;
        while(getline(fin,line)){
            int count= 0;
            size_t A = line.find("@");
            if(A != string::npos){
                string lab;
                stringstream numString(line.substr(A + 1));
                numString >> lab;
                for(int n = 0; n < i; n++){           //checking if the value is a label or not
                    if(lab == symbol[n]){
                        temp << "@" << address[n] << '\n';
                        count++;
                    }
                }
                if(count == 0)
                    temp << line << '\n';
            }
            else
                temp << line << '\n';			
        }
        fin.close();
        temp.close();
        remove(f);
        rename("temp.asm",f);
    }
    
    bool isNumber(string s){
        for(int a = 0; a < s.length(); a++)
            if (isdigit(s[a]) == false)
                return false;
        return true;
    }
    //storing variables in the symbol array and there address in address array
    void variable(const char *f){
        ifstream fin(f);
        string line;
        while(getline(fin,line)){
            int count = 0;
            size_t A = line.find("@");
            if(A != string::npos){
                string var;
                stringstream numString(line.substr(A + 1));
                numString >> var;
                if(isNumber(var))     //if the in question string is a number it can not be a variable
                    continue;
                else{
                    for(int n = 0; n < i; n++){  //checking if the variable already exists
                        if(var == symbol[n])
                            count++;
                    } 
                    if(count == 0){         //if variable do not already exist, store it
                        symbol[i] = var;
                        address[i] = j;
                        i++;
                        j++;
                    }
                }
            }
        }
        fin.close();
    }
    // on encountering a variable modify its value
    void variableCheck(const char *f){
        ifstream fin(f);
        ofstream temp("temp.asm");
        string line;
        while(getline(fin,line)){
            int count = 0;
            size_t A = line.find("@");
            if(A != string::npos){
                string vari;
                stringstream numString(line.substr(A + 1));
                numString >> vari;
                for(int n = 0; n < i; n++){
                    if(vari == symbol[n]){
                        temp << "@" << address[n] << '\n';
                        count++;
                    }
                }
                if(count == 0)
                    temp << line << '\n';
            }
            else
                    temp << line << '\n';
        }
        fin.close();
        temp.close();
        remove(f);
        rename("temp.asm",f);
    }
    //delete arrays
    ~Symbols(){
        delete address;
        delete []symbol;
    }
};				
//removing whitespace           
void empty(const char *f){
    ifstream fin(f);
    ofstream temp("temp.asm");
    string line;
    while(getline(fin,line)){
        int counter = 0;
        if(line.length() != 0){
            for(int i = 0; line[i] != '\0'; i++){
                if(line[i] == ' ')
                    continue;
                else if(line[i] == '/')
                    break;
                else if(line[i] == '\n')
                    break;
                else{
                    counter ++;
                    temp << line[i];
                }
            }
        }
        if(counter > 0)
            temp << '\n';
    }
    fin.close();
    temp.close();
    remove(f);
    rename("temp.asm",f);
}


int main(){
    char *filename;
    filename = new char[30];
    cout <<"enter file name:";
    char *outfilename;
    outfilename = new char[36];
    cin >> filename;
    //naming file
    int buff = 0;
    for(int index = 0; filename[index] != '\0' && filename[index] != '.'; ++index){
        outfilename[buff++] = filename[index];
    }
    // Setting extension
    outfilename[buff++] = '.';
    outfilename[buff++] = 'h';
    outfilename[buff++] = 'a';
    outfilename[buff++] = 'c';
    outfilename[buff++] = 'k';
    outfilename[buff++] = '\0';

    empty(filename);    //removing whitespace
    Symbols s(filename);  //constructor calling
    s.predefined(filename); //handling predefined symbols
    s.labels(filename);     //storing labels
    s.labelCheck(filename);  //handling label
    s.variable(filename);    //storing variables
    s.variableCheck(filename);  //handling variables

    ifstream in(filename);
    ofstream out(outfilename, ios :: app);
    string line;
    int i, a[16];

    while(getline(in,line)){
        //A instruction
        size_t A = line.find("@");
        if(A != string::npos){
            int j = 15;
            //initializing array by zero
            for(int i = 0; i < 16; i++)
                a[i] = 0; 
	    int num;
            //typecasting character after "@" from char to int
	    stringstream numString(line.substr(A + 1));
            numString >> num;
            //converting decimal to binary
            for(i = 0; num > 0; i++){
                a[j] = num % 2;
                num = num/2;
                j--;
            }
            //writing machine code of A instruction
            for(i = 0; i < 16; i++)
                out << a[i];
            out << '\n';
        }
        //C instruction
        else{
            a[0] = a[1] = a[2] = 1;  //first three bits of C instruction are 1
            size_t C1 = line.find("=");   //dest = comp
            size_t C2 = line.find(";");   //comp;jump

            if(C1 != string::npos){
                //typecasting C1+1 from char to string
                string C;
                stringstream numString(line.substr(C1 + 1));
                numString >> C;

                int k = 0, l = 0;
                a[15] = a[14] = a[13] = 0;  // In (dest = comp) jump bits are zero 
                while(k <= 0){
                    if(C == "0")
                        a[3] = 0, a[4] = 1, a[5] = 0, a[6] = 1, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if(C == "1")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 1, a[7] = 1, a[8] = 1, a[9] = 1;
                    else if(C == "-1")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 1, a[7] = 0, a[8] = 1, a[9] = 0;   
                    else if(C == "D")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 1, a[7] = 1, a[8] = 0, a[9] = 0;
                    else if(C == "A")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 0;
                    else if(C == "!D")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 1, a[7] = 1, a[8] = 0, a[9] = 1;
                    else if(C == "!A")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 1; 
                    else if(C == "-D")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 1, a[7] = 1, a[8] = 1, a[9] = 1;       
                    else if(C == "-A")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 1;
                    else if(C == "D+1")
                        a[3] = 0, a[4] = 0, a[5] = 1, a[6] = 1, a[7] = 1, a[8] = 1, a[9] = 1;
                    else if(C == "A+1")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 1, a[8] = 1, a[9] = 1;
                    else if(C == "D-1")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 1, a[7] = 1, a[8] = 1, a[9] = 0;
                    else if(C == "A-1")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if(C == "D+A")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if(C == "D-A")
                        a[3] = 0, a[4] = 0, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 1;
                    else if(C == "A-D")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 1, a[8] = 1, a[9] = 1;
                    else if(C == "D&A")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 0;
                    else if(C == "D|A")
                        a[3] = 0, a[4] = 0, a[5] = 1, a[6] = 0, a[7] = 1, a[8] = 0, a[9] = 1;
                    else if(C == "M")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 0;
                    else if(C == "!M")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 1; 
                    else if(C == "-M")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 1;
                    else if(C == "M+1")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 1, a[8] = 1, a[9] = 1;
                    else if(C == "M-1")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if(C == "D+M")
                        a[3] = 1, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if(C == "D-M")
                        a[3] = 1, a[4] = 0, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 1;  
                    else if(C == "M-D")
                        a[3] = 1, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 1, a[8] = 1, a[9] = 1;  
                    else if(C == "D&M")
                        a[3] = 1, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 0; 
                    else if(C == "M-D")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;  
                    else if(C == "D|M")
                        a[3] = 1, a[4] = 0, a[5] = 1, a[6] = 0, a[7] = 1, a[8] = 0, a[9] = 1;
                    else;
                    k++;
                }
                while(l <= 0){
                    if((line.substr(0,C1)) == "M")
                        a[10] = 0, a[11] = 0, a[12] = 1;
                    else if((line.substr(0,C1)) == "D")
                        a[10] = 0, a[11] = 1, a[12] = 0;
                    else if((line.substr(0,C1)) == "MD")
                        a[10] = 0, a[11] = 1, a[12] = 1;
                    else if((line.substr(0,C1)) == "A")
                        a[10] = 1, a[11] = 0, a[12] = 0;
                    else if((line.substr(0,C1)) == "AM")
                        a[10] = 1, a[11] = 0, a[12] = 1;
                    else if((line.substr(0,C1)) == "AD")
                        a[10] = 1, a[11] = 1, a[12] = 0;
                    else if((line.substr(0,C1)) == "AMD")
                        a[10] = 1, a[11] = 1, a[12] = 1;
                    else;
                    l++;
                }
            }
            else if(C2 != string::npos){
                string C0;
                stringstream numString(line.substr(C2 + 1));
                numString >> C0;
                a[10] = a[11] = a[12] = 0; //in (comp;jump) dest bits are zero
                int k = 0, l = 0;
                while(k <= 0){
                    if((line.substr(0,C2)) == "0")
                        a[3] = 0, a[4] = 1, a[5] = 0, a[6] = 1, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if((line.substr(0,C2)) == "1")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 1, a[7] = 1, a[8] = 1, a[9] = 1;          
                    else if((line.substr(0,C2)) == "-1")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 1, a[7] = 0, a[8] = 1, a[9] = 0; 
                    else if((line.substr(0,C2)) == "D")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 1, a[7] = 1, a[8] = 0, a[9] = 0;
                    else if((line.substr(0,C2)) == "A")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 0;   
                    else if((line.substr(0,C2)) == "!D")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 1, a[7] = 1, a[8] = 0, a[9] = 1;         
                    else if((line.substr(0,C2)) == "!A")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 1; 
                    else if((line.substr(0,C2)) == "-D")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 1, a[7] = 1, a[8] = 1, a[9] = 1;      
                    else if((line.substr(0,C2)) == "-A")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 1;
                    else if((line.substr(0,C2)) == "D+1")
                        a[3] = 0, a[4] = 0, a[5] = 1, a[6] = 1, a[7] = 1, a[8] = 1, a[9] = 1; 
                    else if((line.substr(0,C2)) == "A+1")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 1, a[8] = 1, a[9] = 1;
                    else if((line.substr(0,C2)) == "D-1")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 1, a[7] = 1, a[8] = 1, a[9] = 0; 
                    else if((line.substr(0,C2)) == "A-1")
                        a[3] = 0, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if((line.substr(0,C2)) == "D+A")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if((line.substr(0,C2)) == "D-A")
                        a[3] = 0, a[4] = 0, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 1;
                    else if((line.substr(0,C2)) == "A-D")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 1, a[8] = 1, a[9] = 1;
                    else if((line.substr(0,C2)) == "D&A")
                        a[3] = 0, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 0;
                    else if((line.substr(0,C2)) == "D|A")
                        a[3] = 0, a[4] = 0, a[5] = 1, a[6] = 0, a[7] = 1, a[8] = 0, a[9] = 1;
                    else if((line.substr(0,C2)) == "M")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 0;
                    else if((line.substr(0,C2)) == "!M")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 1;
                    else if((line.substr(0,C2)) == "-M")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 1;
                    else if((line.substr(0,C2)) == "M+1")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 1, a[8] = 1, a[9] = 1;
                    else if((line.substr(0,C2)) == "M-1")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if((line.substr(0,C2)) == "D+M")
                        a[3] = 1, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;
                    else if((line.substr(0,C2)) == "D-M")
                        a[3] = 1, a[4] = 0, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 1;  
                    else if((line.substr(0,C2)) == "M-D")
                        a[3] = 1, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 1, a[8] = 1, a[9] = 1; 
                    else if((line.substr(0,C2)) == "D&M")
                        a[3] = 1, a[4] = 0, a[5] = 0, a[6] = 0, a[7] = 0, a[8] = 0, a[9] = 0;
                    else if((line.substr(0,C2)) == "M-D")
                        a[3] = 1, a[4] = 1, a[5] = 1, a[6] = 0, a[7] = 0, a[8] = 1, a[9] = 0;   
                    else if((line.substr(0,C2)) == "D|M")
                        a[3] = 1, a[4] = 0, a[5] = 1, a[6] = 0,  a[7] = 1, a[8] = 0, a[9] = 1;
                    else;
                    k++;
                }
                while(l<=0){
                    if(C0 == "JGT")
                        a[13] = 0, a[14] = 0, a[15] = 1;
                    else if(C0 == "JEQ")
                        a[13] = 0, a[14] = 1, a[15] = 0;
                    else if(C0 == "JGE")
                        a[13] = 0, a[14] = 1, a[15] = 1;
                    else if(C0 == "JLT")
                        a[13] = 1, a[14] = 0, a[15] = 0;
                    else if(C0 == "JNE")
                        a[13] = 1, a[14] = 0, a[15] = 1;
                    else if(C0 == "JLE")
                        a[13] = 1, a[14] = 1, a[15] = 0;
                    else if(C0 == "JMP")
                        a[13] = 1, a[14] = 1,  a[15] = 1;
                    l++;
                }
            }
            else
                continue;
            for(i = 0; i < 16; i++)   //writing machine code of C instruction
                out << a[i];
            out << '\n';
           
        }
    }  
    in.close();
    out.close();
                                                                                                                                  
    return 0;
} 
