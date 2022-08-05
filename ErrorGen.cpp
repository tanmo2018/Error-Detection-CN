#include<bits/stdc++.h>
using namespace std;

void  errorGen(string &s){
    srand(time(0));
    int n=rand()%(s.size());
    if(s[n]=='0')s[n]='1';
    else s[n]='0';
    return ;
}

int main(){
ifstream readCode;string s="",temp;int sl;
vector<string>vectSring;
readCode.open("channel.txt",ios::in);

cout<<endl;
    cout<<" ------ Enter the specific serial number to generate that type of error ------ "<<endl;
    cout<<"1. Error generation for VRC."<<endl;
    cout<<"2. Error generation for LRC."<<endl;
    cout<<"3. Error generation for CheckSum"<<endl;
    cout<<"4. Error generation for CRC."<<endl;
    cout<<endl;
    cout<<"Enter the Sl. No. : ";
    cin>>sl;

    switch (sl)
    {
    case 1:{
        // file read,frame for vrc.
             while(getline(readCode,temp)) s+=temp;
             readCode.close();

        //one bit error for vrc
             errorGen(s);

        //Error bit stream | file write.
             ofstream writeCode;writeCode.open("channel.txt",ios::out);
              int i=0;
              while(i<s.length()){
                      for(int j=0;j<8;j++){
                          if(i>=s.length())break;
                      writeCode<<s[i];i++;
                      }
                      writeCode<<endl;
              }  
              writeCode.close();
              cout<<"Error is introduced !"<<endl;
              
             break;
    }
     
    case 2:{
        // file read,frame size is 8 for lrc.
             while(getline(readCode,temp))
             vectSring.push_back(temp);
             readCode.close();

        // one error bit per line except lastline (lrc)
              s="";
              for(int j=0;j<vectSring.size()-1;j++){
                  if(j==1)errorGen(vectSring[j]);
                  s+=vectSring[j];
              }
              s+=vectSring[vectSring.size()-1];
              vectSring.clear();  

        //Error bit stream | file write,frame size is 8.
              ofstream writeCode;writeCode.open("channel.txt",ios::out);
              int i=0;
              while(i<s.length()){
                      for(int j=0;j<8;j++){
                          if(i>=s.length())break;
                      writeCode<<s[i];i++;
                      }
                      writeCode<<endl;
              }  
              writeCode.close();
              cout<<"Error is introduced !"<<endl;


        break;
    }
        
    case 3:{
        // file read,frame size s 8 for CheckSum.
             while(getline(readCode,temp))
             vectSring.push_back(temp);
             readCode.close();

        // one error bit per line except lastline (CheckSum)
             s="";
             for(int j=0;j<vectSring.size()-1;j++){
                 if(j==1)errorGen(vectSring[j]);
                 s+=vectSring[j];
             }
             s+=vectSring[vectSring.size()-1];
             vectSring.clear(); 

        //Error bit stream | file write,frame size is 8.
             ofstream writeCode;writeCode.open("channel.txt",ios::out);
             int i=0;
             while(i<s.length()){
                     for(int j=0;j<8;j++){
                         if(i>=s.length())break;
                     writeCode<<s[i];i++;
                     }
                     writeCode<<endl;
                 }
             writeCode.close();
             cout<<"Error is introduced !"<<endl;

        break;
    }
    case 4:{
        // file read,frame size s 8 for CRC.
              while(getline(readCode,temp))
              vectSring.push_back(temp);
              readCode.close();

        // one error bit per line except First line (CRC)
              s=""; string div=vectSring[0];
              for(int j=1;j<vectSring.size();j++){
                  if(j==1)errorGen(vectSring[j]); //Error gen posision in vector is represented by j;
                  s+=vectSring[j];
              }
              vectSring.clear();

        // error bit stream | file write for CRC
              ofstream writeCode;writeCode.open("channel.txt",ios::out);
              writeCode<<div<<endl;
              int i=0;
             while(i<s.length()){
                     for(int j=0;j<8;j++){
                         if(i>=s.length())break;
                     writeCode<<s[i];i++;
                     }
                     writeCode<<endl;
                 }  
              writeCode.close();
              cout<<"Error is introduced !"<<endl;
              

        break;
    }
    default:{
        cout<<" Invalid input !"<<endl;
        break;
    }
    }

// file read,frame size is 8 for vrc.
    // while(getline(readCode,temp)) s+=temp;
    // readCode.close();

// file read,frame size is 8 for lrc.
    // while(getline(readCode,temp))
    // vectSring.push_back(temp);
    // readCode.close();

// file read,frame size s 8 for CheckSum.
    // while(getline(readCode,temp))
    // vectSring.push_back(temp);
    // readCode.close();

// file read,frame size s 8 for CRC.
    // while(getline(readCode,temp))
    // vectSring.push_back(temp);
    // readCode.close();



//one bit error for vrc
//    errorGen(s);

// one error bit per line except lastline (lrc)
    // s="";
    // for(int j=0;j<vectSring.size()-1;j++){
    //     if(j==1)errorGen(vectSring[j]);
    //     s+=vectSring[j];
    // }
    // s+=vectSring[vectSring.size()-1];
    // vectSring.clear();

// one error bit per line except lastline (CheckSum)
    // s="";
    // for(int j=0;j<vectSring.size()-1;j++){
    //     if(j==1)errorGen(vectSring[j]);
    //     s+=vectSring[j];
    // }
    // s+=vectSring[vectSring.size()-1];
    // vectSring.clear();

// one error bit per line except First line (CRC)
    // s=""; string div=vectSring[0];
    // for(int j=1;j<vectSring.size();j++){
    //     if(j==1)errorGen(vectSring[j]); //Error gen posision in vector is represented by j;
    //     s+=vectSring[j];
    // }
    // vectSring.clear();

// error bit stream | file write for CRC
    // ofstream writeCode;writeCode.open("channel.txt",ios::out);
    // writeCode<<div<<endl;
    // writeCode<<s;
    
// ofstream writeCode;writeCode.open("channel.txt",ios::out);
// writeCode<<s;

//error bit stream | file write,frame size is 8. except CRC
// ofstream writeCode;writeCode.open("channel.txt",ios::out);
// int i=0;
// while(i<s.length()){
//         for(int j=0;j<8;j++){
//             if(i>=s.length())break;
//         writeCode<<s[i];i++;
//         }
//         writeCode<<endl;
//     }


//   writeCode.close();
    return 0;
}