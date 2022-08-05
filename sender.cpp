#include<bits/stdc++.h>
using namespace std;
//count the number of one is there in the stream
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
        while(div_dend[i]!='1'){
            i++;
        }
         div_dend=div_dend.substr(i);
         if(div_dend.length()<div_sor.length()){
            return div_dend;
        }
        s=xorBit(div_dend.substr(0,div_sor.length()),div_sor);
        div_dend=s+div_dend.substr(div_sor.length());
        return crcStream(div_dend,div_sor);
     }



int main(){
    string s;int i=0,sl;
    ofstream myChannel;
    myChannel.open("channel.txt");
    cout<<endl;
    cout<<"Enter the bit streams : ";
    cin>>s;

    cout<<endl;
    cout<<" ------ Enter the specific serial number to do that type of checking ------ "<<endl;
    cout<<"1. Vertical Redundancy Check (VRC) or Parity Check."<<endl;
    cout<<"2. Longitudinal Redundancy Check (LRC)/2-D Parity Check."<<endl;
    cout<<"3. CheckSum."<<endl;
    cout<<"4. Cyclic Redundancy Rheck (CRC)."<<endl;
    cout<<endl;
    cout<<"Enter the Sl. No. : ";
    cin>>sl;

    switch (sl)
    {
    case 1:{
        //Even parity (vcr)
           int One=noOfOne(s);
           if(One%2==0)s+="0";
           else s+="1";

        //file write ,frame size is 8.  not for crc
            i=0;
              while(i<s.length()){
                  for(int j=0;j<8;j++){
                      if(i>=s.length())break;
                  myChannel<<s[i];i++;
                  }
                  myChannel<<endl;
              }     
               cout<<"Executed!"<<endl;
           break;
    }
     
    case 2:{
        //Longitudinal Redundency Check
             vector<string>vecString;string lString="";
             for(int j=0;j<8;j++){
                 i=j;
                 while(i<s.length()){
                 lString+=s[i];
                 i+=8;
                 }
                 vecString.push_back(lString);
                 lString="";
             }
             //Redundant bits generation
             for(i=0;i<8;i++){
                 int One=noOfOne(vecString[i]);
                 if(One%2==0)s+="0";
                 else s+="1";
             }

        //file write ,frame size is 8.  not for crc
              i=0;
              while(i<s.length()){
                  for(int j=0;j<8;j++){
                      if(i>=s.length())break;
                  myChannel<<s[i];i++;
                  }
                  myChannel<<endl;
              }     
               cout<<"Executed!"<<endl;

        break;
    }
        
    case 3:{
        //CheckSum
              vector<string>vecString;string lString="",bitString="";
              i=0;
              while(i<s.length()){
               for(int j=0;j<8;j++){
               lString+=s[i];i++;
               }
               vecString.push_back(lString);
               lString="";
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
              s+=invertString(bitString);

        //file write ,frame size is 8.  not for crc
             i=0;
             while(i<s.length()){
                 for(int j=0;j<8;j++){
                     if(i>=s.length())break;
                 myChannel<<s[i];i++;
                 }
                 myChannel<<endl;
             }
              cout<<"Executed!"<<endl;

        break;
    }
    case 4:{
        //CRC 
             string div;
             cout<<"Divisor - ";
             cin>>div;
             for(int ind=0;ind<div.length()-1;ind++){
                 s+='0';
             }

             s=addB(s,crcStream(s,div));
             myChannel<<div<<endl;
        //file write ,frame size is 8.  not for crc
             i=0;
             while(i<s.length()){
                 for(int j=0;j<8;j++){
                     if(i>=s.length())break;
                 myChannel<<s[i];i++;
                 }
                 myChannel<<endl;
             }
              cout<<"Executed!"<<endl;

        break;
    }
    default:{
        cout<<" Invalid input !"<<endl;
        break;
    }
    }
//Even parity (vcr)

    // int One=noOfOne(s);
    // if(One%2==0){
    //     s+="0";
    // }
    // else s+="1";
   
//Longitudinal Redundency Check
    // vector<string>vecString;string lString="";
    // for(int j=0;j<8;j++){
    //     i=j;
    //     while(i<s.length()){
    //     lString+=s[i];
    //     i+=8;
    //     }
    //     vecString.push_back(lString);
    //     lString="";
    // }
    // //Redundant bits generation
    // for(i=0;i<8;i++){
    //     int One=noOfOne(vecString[i]);
    //     if(One%2==0)s+="0";
    //     else s+="1";
    // }


// //CheckSum
//     vector<string>vecString;string lString="",bitString="";
//     i=0;
//     while(i<s.length()){
//     for(int j=0;j<8;j++){
//       lString+=s[i];i++;
//     }
//     vecString.push_back(lString);
//     lString="";
//     }
    

//     for(int idx=0;idx<vecString.size();idx++){
//         lString="";
//         lString=addB(bitString,vecString[idx]);
//         if(lString.length()>8){
//                 lString=lString.substr(1);
//                 bitString=addB(lString,"1");
//             }
//            else bitString=lString;    
//     }
//     s+=invertString(bitString);

//CRC 
    // string div;
    // cout<<"Divisor - ";
    // cin>>div;
    // for(int ind=0;ind<div.length()-1;ind++){
    //     s+='0';
    // }

    // s=addB(s,crcStream(s,div));
    // myChannel<<div<<endl;
    // myChannel<<s;


//file write ,frame size is 8.  not for crc
    // i=0;
    // while(i<s.length()){
    //     for(int j=0;j<8;j++){
    //         if(i>=s.length())break;
    //     myChannel<<s[i];i++;
    //     }
    //     myChannel<<endl;
    // }
    

    myChannel.close();
    return 0;
}