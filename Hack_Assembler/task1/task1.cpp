//this program simplifies the input file too
#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<algorithm>
using namespace std; 
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
    char *outfilename;
    outfilename = new char[36];
    cout <<"enter file name:";
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
    //removing whitespace
    empty(filename);
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
