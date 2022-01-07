#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <bitset> // for converting to binary

using namespace std;

unsigned long long ParsePacket(string & input, unsigned long long & version_sum)
{
    unsigned long version =  bitset<32>(input.substr(0,3)).to_ulong();
    unsigned long typeID =  bitset<32>(input.substr(3,3)).to_ulong();
    
    version_sum = version_sum + version;
    
    //cout << "version is " << version << endl;
    //cout << "typeID is " << typeID << endl;
    
    input.erase(input.begin(), input.begin()+6);
    
    if(typeID==4)
    {
        string val = "";
        bool exit = 0;
        
        do
        {
            if(input[0]=='1')
            {
                input.erase(input.begin(), input.begin()+1);
                val = val + input.substr(0,4);
                input.erase(input.begin(), input.begin()+4);
            }
            else
            {
                input.erase(input.begin(), input.begin()+1);
                val = val + input.substr(0,4);
                input.erase(input.begin(), input.begin()+4);
                exit = 1;
            }
        } while(!exit);
        return bitset<64>(val).to_ulong();
    }
    else
    {
        vector<unsigned long long int> sub_packets_val;
        char lengthID = input.substr(0,1)[0];
        input.erase(input.begin(), input.begin()+1);
        if(lengthID=='0')
        {
            unsigned long length =  bitset<32>(input.substr(0,15)).to_ulong();
            input.erase(input.begin(), input.begin()+15);
            
            unsigned long curr_input_len = input.length();
            do
            {
                sub_packets_val.push_back(ParsePacket(input, version_sum));
            } while(curr_input_len - input.length()<length);
        }
        else
        {
            unsigned long nSubpackets =  bitset<32>(input.substr(0,11)).to_ulong();
            input.erase(input.begin(), input.begin()+11);
            for(int i=0;i<nSubpackets;i++)
            {
                sub_packets_val.push_back(ParsePacket(input, version_sum));
            }
        }
        
        if(typeID==0)
        {
            unsigned long long answer = 0;
            for(int s=0;s<sub_packets_val.size();s++)
            {
                answer = answer + sub_packets_val[s];
            }
            return answer;
        }
        else if(typeID==1)
        {
            unsigned long long answer = 1;
            for(int s=0;s<sub_packets_val.size();s++)
            {
                answer = answer * sub_packets_val[s];
            }
            return answer;
        }
        else if(typeID==2)
        {
            return *min_element(sub_packets_val.begin(), sub_packets_val.end());
        }
        else if(typeID==3)
        {
            return *max_element(sub_packets_val.begin(), sub_packets_val.end());
        }
        else if(typeID==5)
        {
            return (sub_packets_val[0]>sub_packets_val[1]);
        }
        else if(typeID==6)
        {
            return(sub_packets_val[0]<sub_packets_val[1]);
        }
        else if (typeID==7)
        {
            return(sub_packets_val[0]==sub_packets_val[1]);
        }
        else
        {
            cout << "Something is wrong\n";
            return -1;
        }
    }
}

int main()
{
    ifstream file("input.txt");
    string line;
    
    map<char, string> hex_to_bin;
    
    while(getline(file,line))
    {
        // hex to bin key read in
        hex_to_bin.insert(pair<char, string>(line.substr(0,1)[0], line.substr(4,4)));
    }
            
    string hex = "420D74C3088043390499ED709E6EB49A5CC4A3A3898B7E0F44011C4CC48AC0119D049B0C500265EB8F615900180910C88129B2F0007C61C4B7F74ED7396B20020A44A4C014D005E5A72E274B4E5C4B96CC3793410078C01D82F1DA08180351661AC1920042A3CC578BA6008F802138D93352B9CFCEF61D3009A7D2268D254925569C02A92D62BF108D52C1B3E4B257B57FAE5C54400A84840267880311D23245F1007A35C79848200C4288FF0E8C01194A4E625E00A4EFEF5F5996486C400C5002800BFA402D3D00A9C4027B98093D602231C00F001D38C009500258057E601324C00D3003D400C7003DC00A20053A6F1DBDE2D4600A6802B37C4B9E872B0E44CA5FF0BFB116C3004740119895E6F7312BCDE25EF077700725B9F2B8F131F333005740169A7F92EFEB3BC8A21998027400D2CDF30F927880B4C62D6CDFFD88EB0068D2BF019A8DAAF3245B39C9CFA1D2DF9C3DB9D3E50A0164BE2A3339436993894EC41A0D10020B329334C62016C8E7A5F27C97D0663982D8EB23C5282529CDD271E8F100AE1401AA80021119E3A4511006E1E47689323585F3AEBF900AEB2B6942BD91EE8028000874238AB0C00010B8D913220A004A73D789C4D54E24816301802538E940198880371AE15C1D1007638C43856C00954C25CD595A471FE9D90056D60094CEA61933A9854E9F3801F2BBC6131001F792F6796ACB40D036605C80348C005F64F5AC374888CA42FD99A98025319EB950025713656F202200B767AB6A30E802D278F81CBA89004CD286360094FC03A7E01640245CED5A3C010100660FC578B60008641C8B105CC017F004E597E596E633BA5AB78B9C8F840C029917C9E389B439179927A3004F003511006610C658A200084C2989D0AE67BD07000606154B70E66DC0C01E99649545950B8AB34C8401A5CDA050043D319F31CB7EBCEE14";
    
    //string hex = "9C0141080250320F1802104A08";
    string input = "";
    for(int i=0;i<hex.length();i++)
    {
        for (map<char, string>::iterator it = hex_to_bin.begin(); it != hex_to_bin.end(); ++it)
        {
            if(hex[i]==it->first)
            {
                input = input + it->second;
            }
        }
    }
    
    unsigned long long version_sum = 0;
    unsigned long long val_expression = ParsePacket(input, version_sum);
    
    cout << "Total version sum: " << version_sum << endl;
    cout << "Value of expression: " << val_expression << endl;
    return 0;
}
