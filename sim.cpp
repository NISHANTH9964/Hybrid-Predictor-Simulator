#include <iostream>
#include<math.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <sstream>
#include <bitset>
#include <string>
using namespace std;
int miss = 0;
string xor_str(string a, string b) {
       string str = "";
       for(int i=0;i<a.length();i++) {
           char temp1 = a.at(i);
           char temp2 = b.at(i);
           str += to_string((int) temp1 ^ (int) temp2);
       }
       return str;
       }


string hextobin(string z) {
    int i = 0;
    string binary = "";
    while (z[i]) {
        switch (z[i]) {
            case '0' :
                binary += "0000";
                break;
            case '1' :
                binary += "0001";
                break;
            case '2' :
                binary += "0010";
                break;
            case '3' :
                binary += "0011";
                break;
            case '4' :
                binary += "0100";
                break;
            case '5' :
                binary += "0101";
                break;
            case '6' :
                binary += "0110";
                break;
            case '7' :
                binary += "0111";
                break;
            case '8' :
                binary += "1000";
                break;
            case '9' :
                binary += "1001";
                break;
            case 'a' :
                binary += "1010";
                break;
            case 'b' :
                binary += "1011";
                break;
            case 'c' :
                binary += "1100";
                break;
            case 'd' :
                binary += "1101";
                break;
            case 'e' :
                binary += "1110";
                break;
            case 'f' :
                binary += "1111";
                break;
            default :
                binary += "\n Invalid Hexadecimal Digit... ";
        }
        i++;
    }
    return binary;
}

int bin_to_decimal(string tag) {
    int i = tag.length() - 1;
    int j = 0;
    int dec = 0;
    while (i >= 0) {
        if (tag[i] == '1') {
            dec += pow(2, j);
        }
        j++;
        i--;
    }
    return dec;
}
void gshr(string bin, int m, int n, char actual, string shift_reg, int array[]) {
    string tag = bin.substr(bin.size() - 2 - m, m);// lowermost m bits of given bin
    string updated_tag = tag.substr(0, m - n);//m-n bits
    string car = tag.substr(tag.size() - n, n);
    string xor_final = xor_str(shift_reg, car);
    string m_index = updated_tag + xor_final;
    char predict;
    int decimal_address = bin_to_decimal(m_index);

    if (array[decimal_address] < 4) {
        predict = 'n';
    }
    if (array[decimal_address] >= 4) {
        predict = 't';
    }
    if (actual == 'n') {
        if (array[decimal_address] > 0) {
            array[decimal_address]--;
        }
    }
    else {
            if (array[decimal_address] < pow(2, 3) - 1) {
                array[decimal_address]++;
            }
    }
    if (actual != predict) {
        miss++;
    }
}

char gshr_check(string bin, int m, int n, char actual, string shift_reg, int array[]) {
    string tag = bin.substr(bin.size() - 2 - m, m);// lowermost m bits of given bin
    string updated_tag = tag.substr(0, m - n);//m-n bits
    string car = tag.substr(tag.size() - n, n);
    string xor_intermediate = xor_str(shift_reg, car);
    string xor_final = xor_intermediate.substr(xor_intermediate.size() - n, n);
    string m_index = updated_tag + xor_final;
    char predict;
    int decimal_address = bin_to_decimal(m_index);
    //cout<<"z"<<decimal_address<<endl;
    if (array[decimal_address] < 4) {
        predict = 'n';
    }
    if (array[decimal_address] >= 4) {
        predict = 't';
    }
    return predict;
}

char bimoda_check(string bin, int m, char actual, int array[]){
    string tag = bin.substr(bin.size() - 2 - m, m);
    int decimal_address = bin_to_decimal(tag);
    char predict;
    if (array[decimal_address] < 4) {
        predict = 'n';
    }
    if (array[decimal_address] >= 4) {
        predict = 't';
    }
    return predict;
}
void bimoda(string bin, int m, char actual, int array[]) {
    string tag = bin.substr(bin.size() - 2 - m, m);
    int decimal_address = bin_to_decimal(tag);
    char predict;
    if (array[decimal_address] < 4) {
        predict = 'n';
    }
    if (array[decimal_address] >= 4) {
        predict = 't';
    }
    //return b.predict;
    if (actual == 'n') {
        if (array[decimal_address] > 0) {
            array[decimal_address]--;
        }
    }
    else {
            if (array[decimal_address] < pow(2, 3) - 1) {
                array[decimal_address]++;
            }
        }

    if (actual != predict) {
        miss++;
    }
}
int main (int argc, char* argv[]) {
//y.gshr(stoi(argv[1]),stoi(argv[2]),argv[3]);
//z.bimoda(stoi(argv[1]),argv[2]);
//x.hy(stoi(argv[2]),argv[6]);
int counter = 0;

        string model = argv[1];
          if(argc != 7 and model != "hybrid") {
              cout << "Invalid entry" << endl;
              exit (0);
          }
        int k = stoi(argv[2]);
        int m1 = stoi(argv[3]);
        int n = stoi(argv[4]);
        int m2 = stoi(argv[5]);
        const char *trace1 =  argv[6];


    int v = pow(2, k);
    int content[v];
    for (int i = 0; i < v; i++) {
        content[i] = 1;
    }
    int bi_size = pow(2, m2);
    int bimodalar[bi_size];
    for (int i = 0; i < bi_size; i++) {
        bimodalar[i] = 4;
    }
    int gs_size = pow(2, m1);
    int gsharear[gs_size];
    for (int i = 0; i < gs_size; i++) {
        gsharear[i] = 4;
    }
    string shift_reg = "";
    for (int i = 0; i < n; i++){
        shift_reg += "0";
    }
        ifstream file(trace1);
        string str;
        string addr1;
        char actual, l, c;
        while (getline(file, str)) {
            counter++;
            string a = str.substr(7);
            actual = a[0];
            string address = str.substr(0, 6);
            string bin_address = (hextobin(address));
            string tag = bin_address.substr(bin_address.size() - 2 - k, k);
            int decimal_address = bin_to_decimal(tag);




            l = bimoda_check(bin_address, m2, actual, bimodalar);
            c =gshr_check(bin_address, m1, n, actual, shift_reg, gsharear);

            if(content[decimal_address] < 2){
                bimoda(bin_address, m2, actual, bimodalar);
                if(actual == 'n'){
                    shift_reg = "0" + shift_reg;
                    shift_reg = shift_reg.substr(0, shift_reg.size() - 1);
                }
                else if(actual == 't'){
                    shift_reg = "1" + shift_reg;
                    shift_reg = shift_reg.substr(0, shift_reg.size() - 1);
                }
            }
            else if(content[decimal_address] >=2) {
                gshr(bin_address, m1, n, actual, shift_reg, gsharear);
                if(actual == 'n'){
                    shift_reg = "0" + shift_reg;
                    shift_reg = shift_reg.substr(0, shift_reg.size() - 1);
                }
                else if(actual == 't'){
                    shift_reg = "1" + shift_reg;
                    shift_reg = shift_reg.substr(0, shift_reg.size() - 1);
                }

            }
            if(l != actual && c == actual) {
                if (content[decimal_address] < 3) {
                    content[decimal_address]++;
                }
            }
            if(l == actual && c != actual) {
                if (content[decimal_address] > 0) {
                    content[decimal_address]--;
                }
            }




        }
    cout<<"COMMAND"<<endl;
    printf("./sim hybrid %d %d %d %d %s\n",k,m1,n,m2,trace1);
    cout<<"OUTPUT"<<endl;
    cout<<"number of predictions:\t\t"<<counter<<endl;
    cout<<"number of mispredictions:\t"<<miss<<endl;
    float missrate = floor((((float)miss / counter) * 100) * 100 + 0.5) / 100;
    cout<<"misprediction rate:\t\t"<<missrate<<"%"<<endl;

    cout<<"FINAL CHOOSER CONTENTS"<<endl;
    for(int i=0;i<v;i++)
    {
        cout<<i<<"\t"<<content[i]<<endl;
    }

  cout<<"FINAL GSHARE CONTENTS"<<endl;
    for(int i=0;i<gs_size;i++)
    {
        cout<<i<<"\t"<<gsharear[i]<<endl;
    }

    cout<<"FINAL BIMODAL CONTENTS\t"<<endl;
    for(int i=0;i<bi_size;i++)
    {
        cout<<i<<"\t"<<bimodalar[i]<<endl;
    }
    }






