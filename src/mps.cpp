#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int,int>> result;

class node
{
    public:
        int value = 0;
        int k = 0;
        bool excep = false;
};
struct myclass
{
    bool operator() (pair<int,int> i,pair<int,int> j) { return (i.first<j.first);}
} myobject;

void generate_result(int i,int j,node** MIS);
int main(int argc,char* argv[])
{
    if(argc != 3)   return 0;
    string inputfile = argv[1];
    string outputfile = argv[2];
    fstream input_file;

    int number = 0;

    input_file.open(inputfile,ios::in);
    if(!input_file.is_open())   return 0;
    // cout<<"open file: "<<inputfile<<endl;
    input_file>>number;
    // cout<<"total point: "<<number<<endl;

    map<int,int> chords;

    while(true)
    {
        int x=0,y=0;
        input_file >> x;
        input_file >> y;
        if(x==0 and y==0)   break;
        // cout<<x<<" "<<y<<endl;
        chords.insert(pair<int,int>(x,y));
        chords.insert(pair<int,int>(y,x));
    }
    // cout<<"complete creating chord map"<<endl;
    map<int,int>::iterator it;
    it = chords.begin();
    // for(map<int,int>::iterator i=chords.begin();i!=chords.end();i++)    cout<<i->first<<" "<<i->second<<endl;
    // cout<<"----------------------"<<endl;
    
    node** MIS = new node*[number];
    for(int i=0;i<number;i++)
    {
        // cout<<"check "<<i<<endl;
        MIS[i] = new node[number];
    }
    // cout<<"complete creating table......"<<endl;

    for(int l=1;l<number;l++)
    {
        // cout<<"l = "<<l<<endl;
        for(int i=0;i<number-l;i++)
        {
            int j = i+l;
            it = chords.find(j);
            int k = it->second;
            // cout<<"(i,j) = "<<i<<","<<j<<endl;
            // cout<<"(j,k) = "<<j<<","<<k<<endl;
            MIS[i][j].k = k;
            if(k<j and k>i)
            {
                int temp1 = MIS[i][k-1].value + MIS[k+1][j-1].value + 1;
                int temp2 = MIS[i][j-1].value;
                if(temp1 > temp2)
                {
                    MIS[i][j].value = temp1;                    
                }
                else
                {
                    MIS[i][j].value = temp2;
                    MIS[i][j].excep = true;
                }
                
            }
            else if(k == i)
            {
                MIS[i][j].value = MIS[i+1][j-1].value+1;
            }
            else
            {
                MIS[i][j].value = MIS[i][j-1].value;
            }
            // cout<<MIS[i][j].value<<endl;
            // cout<<"---------------------------"<<endl;
        }
    }
    // cout<<"complete finding MPS"<<endl;
    generate_result(0,number-1,MIS);

    fstream output_file;
    output_file.open(outputfile,ios::out);
    if(!output_file)    return 0;
    // cout<<"create file:"<<outputfile<<endl;
    output_file<<MIS[0][number-1].value<<" \n";
    // cout<<"after resulting..........."<<endl;
    sort(result.begin(),result.end(),myobject);
    for(int i=0;i<result.size();i++)
    {
        output_file<<result[i].first<<" "<<result[i].second<<endl;
    }
    output_file.close();
    input_file.close();
    return 0;
}
void generate_result(int i,int j,node** MIS)
{
    int k =MIS[i][j].k;
    if(i<j)
    {
        if(k<j and k>i)
        {
            if(MIS[i][j].excep == true)
            {
                generate_result(i,j-1,MIS);
            }
            else
            {
                result.push_back(pair<int,int>(k,j));
                generate_result(i,k-1,MIS);
                generate_result(k+1,j-1,MIS);
            }
        }
        else if(k == i)
        {
            result.push_back(pair<int,int>(i,j));
            generate_result(i+1,j-1,MIS);
        }
        else
        {
            generate_result(i,j-1,MIS);
        }
    }
}
