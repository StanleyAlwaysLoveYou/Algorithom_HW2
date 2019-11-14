#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class node
{
    public:
        int value = 0;
        map<int,int> chord = {};
};
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
    map<int,int>::iterator it;
    it = chords.begin();
    for(map<int,int>::iterator i=chords.begin();i!=chords.end();i++)
    {
        // cout<<i->first<<" "<<i->second<<endl;
    }
    // cout<<"----------------------"<<endl;
    
    node** MIS = new node*[number];
    for(int i=0;i<number;i++)
    {
        MIS[i] = new node[number];
    }


    for(int l=1;l<number;l++)
    {
        for(int i=0;i<number-l;i++)
        {
            int j = i+l;
            it = chords.find(j);
            int k = it->second;
            // cout<<"(i,j) = "<<i<<","<<j<<endl;
            // cout<<"(j,k) = "<<j<<","<<k<<endl;
            if(k<j and k>i)
            {
                MIS[i][j].value = MIS[i][k-1].value + MIS[k+1][j-1].value + 1;
                MIS[i][j].chord = MIS[i][k-1].chord;    
                for(map<int,int>::iterator m=MIS[k+1][j-1].chord.begin();m!=MIS[k+1][j-1].chord.end();m++)
                {
                    MIS[i][j].chord.insert(pair<int,int>(m->first,m->second));
                }
                MIS[i][j].chord.insert(pair<int,int>(k,j));
            }
            else if(k == i)
            {
                MIS[i][j].value = MIS[i+1][j-1].value+1;
                MIS[i][j].chord = MIS[i+1][j-1].chord;
                MIS[i][j].chord.insert(pair<int,int>(i,j));
            }
            else
            {
                MIS[i][j].value = MIS[i][j-1].value;
                MIS[i][j].chord = MIS[i][j-1].chord;
            }
            // cout<<MIS[i][j].value<<endl;
            // cout<<"---------------------------"<<endl;
        }
    }
    

    fstream output_file;
    output_file.open(outputfile,ios::out);
    if(!output_file)    return 0;
    // cout<<"create file:"<<outputfile<<endl;
    output_file<<MIS[0][number-1].value<<" \n";
    map<int,int> mps = MIS[0][number-1].chord;
    for(map<int,int>::iterator i=mps.begin();i!=mps.end();i++)
    {
        output_file<<i->first<<" "<<i->second<<endl;
    }
    output_file.close();
    input_file.close();
    return 0;
}