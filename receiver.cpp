#include<bits/stdc++.h>
using namespace std;

//number of 1 is present in the stream
int noOfOne(string s){
    int count=0;
    for(int i=0;i<s.length();i++){
        if(s[i]=='1')count++;
    }
    return count;
}

//Binary addition 
string addB(string a, string b){
   string result = "";
   int temp = 0;
   int size_a = a.size() - 1;
   int size_b = b.size() - 1;
   while (size_a >= 0 || size_b >= 0 || temp == 1){
      temp += ((size_a >= 0)? a[size_a] - '0': 0);
      temp += ((size_b >= 0)? b[size_b] - '0': 0);
      result = char(temp % 2 + '0') + result;
      temp /= 2;
      size_a--; size_b--;
   }
   return result;
}

//Inverse
  string invertString(string s){
    for(int i=0;i<s.length();i++){
        if(s[i]=='0')s[i]='1';
        else if(s[i]=='1') s[i]='0';
    }
    return s;
  }

//Xor operation
  string xorBit(string s1,string s2){
    string s="";
    for(int i=0;i<s1.length();i++){
        if(s1[i]==s2[i])s+='0';
        else s+='1';
    }
    return s;
  }

//  Divide and Xor operation 
  
     string crcStream(string div_dend,string div_sor){
        string s="";
        int i=0;
        while(div_dend[i]!='1' && i<div_dend.length()){
            i++;
        }
         div_dend=div_dend.substr(i);
         if(div_dend.length()<div_sor.length()){
            if(div_dend.length()==0)div_dend="0";
            return div_dend;
        }
        s=xorBit(div_dend.substr(0,div_sor.length()),div_sor);
        div_dend=s+div_dend.substr(div_sor.length());
        return crcStream(div_dend,div_sor);
     }  

int main(){
    ifstream myChannel;
    myChannel.open("channel.txt");
    string s="",temp;int sl;
    
    cout<<endl;
    cout<<" ------ Enter the specific serial number to do that type of checking ------ "<<endl;
    cout<<"1. Error Detection in VRC method."<<endl;
    cout<<"2. Error Detection in LRC method."<<endl;
    cout<<"3. Error Detection in CheckSum method."<<endl;
    cout<<"4. Error Detection in CRC method."<<endl;
    cout<<endl;
    cout<<"Enter the Sl. No. : ";
    cin>>sl;

    switch (sl)
    {
    case 1:{
        // VRC - even parity Checker
             while(getline(myChannel,temp))
             {s+=temp;}
             int One=noOfOne(s);
             cout<<endl;
             cout<<"<<< STATUS >>>"<<endl;
             (One%2==0)?cout<<"PASS"<<endl:cout<<"FAIL"<<endl;
           break;
    }
     
    case 2:{
        //LRC - Longitudinal Redundency Check
          //read
                while(getline(myChannel,temp)){
                s+=temp;
                }
                 myChannel.close();
          //lRC calculation in receiver side
                vector<string>vecString;string lString="";int i=0;
                for(int j=0;j<8;j++){
                i=j;
                while(i<(s.length()-8)){
                    lString+=s[i];
                     i+=8;
                 }
                vecString.push_back(lString);
                lString="";
                }
                char lrc[8];
                for(i=0;i<8;i++){
                int One=noOfOne(vecString[i]);                              
                if(One%2==0)lrc[i]='0';
                else lrc[i]='1';
                }

          // // LRC Output
                cout<<endl;
                cout<<"<<< STATUS >>>"<<endl;
                for(i=0;i<8;i++){
                if(s[s.size()-8+i]!=lrc[i]){
                    cout<<"FAIL"<<endl;
                    return 0;
                    }
                }
                 cout<<"PASS"<<endl;

        break;
    }
        
    case 3:{
        //CheckSum
                 vector<string>vecString;string lString="",bitString="";
                 while(getline(myChannel,temp)){
                     vecString.push_back(temp);
                     }

                 for(int idx=0;idx<vecString.size();idx++){
                     lString="";
                     lString=addB(bitString,vecString[idx]);
                     if(lString.length()>8){
                             lString=lString.substr(1);
                             bitString=addB(lString,"1");
                         }
                        else bitString=lString;    
                 }
                
                 cout<<endl;
                 cout<<"<<< STATUS >>>"<<endl;
                 s=invertString(bitString);
                 if(stoi(s)==0)cout<<"PASS"<<endl;
                 else cout<<"FAIL"<<endl;
    
        break;
    }
    case 4:{
        //CRC
                s="";
                string div=temp;int flag=0;
                while(getline(myChannel,temp)){
                    if(flag==0){div=temp; flag++;}
                    else s+=temp;
                }
                cout<<endl;
                cout<<"<<< STATUS >>>"<<endl;
                (stoi(crcStream(s,div))==0)?cout<<"PASS"<<endl:cout<<"FAIL"<<endl;
           

        break;
    }
    default:{
        cout<<" Invalid input !"<<endl;
        break;
    }
    }
// VRC - even parity Checker
    // while(getline(myChannel,temp))
    // {s+=temp;}
    // int One=noOfOne(s);
    // (One%2==0)?cout<<"PASS"<<endl:cout<<"FAIL"<<endl;

//LRC - Longitudinal Redundency Check
    //read
    //     while(getline(myChannel,temp)){
    //     s+=temp;
    //     }
    //      myChannel.close();
    // //lRC calculation in receiver side
    //     vector<string>vecString;string lString="";int i=0;
    //     for(int j=0;j<8;j++){
    //     i=j;
    //     while(i<(s.length()-8)){
    //         lString+=s[i];
    //          i+=8;
    //      }
    //     vecString.push_back(lString);
    //     lString="";
    //     }
    //     char lrc[8];
    //     for(i=0;i<8;i++){
    //     int One=noOfOne(vecString[i]);                              
    //     if(One%2==0)lrc[i]='0';
    //     else lrc[i]='1';
    //     }

    // // LRC Output
    //     for(i=0;i<8;i++){
    //     if(s[s.size()-8+i]!=lrc[i]){
    //         cout<<"FAIL"<<endl;
    //         return 0;
    //         }
    //     }
    //      cout<<"PASS"<<endl;

// //CheckSum
//     vector<string>vecString;string lString="",bitString="";
//     while(getline(myChannel,temp)){
//         vecString.push_back(temp);
//         }

//     for(int idx=0;idx<vecString.size();idx++){
//         lString="";
//         lString=addB(bitString,vecString[idx]);
//         if(lString.length()>8){
//                 lString=lString.substr(1);
//                 bitString=addB(lString,"1");
//             }
//            else bitString=lString;    
//     }

//     s=invertString(bitString);
//     if(stoi(s)==0)cout<<"PASS"<<endl;
//     else cout<<"FAIL"<<endl;

//CRC
    // s="";
    // string div=temp;int flag=0;
    // while(getline(myChannel,temp)){
    //     if(flag==0){div=temp; flag++;}
    //     else s+=temp;
    // }
   
    // (stoi(crcStream(s,div))==0)?cout<<"PASS"<<endl:cout<<"FAIL"<<endl;
    
    



    myChannel.close();
    return 0;
}