#include<iostream>
#include<vector>
using namespace std;
int main(){
    int pf;//Number Of Page Frames
    cout<<endl<<"Enter The Number Of Page Frames:"<<endl;
    cin>>pf;
    vector<int> PageRefs;//Page References (User Input)
    cout<<endl<<"Enter The Number Of Page References:"<<endl;
    int N;//Number of Page Refernces (User Input)
    cin>>N;
    cout<<endl<<"Enter "<<N<<" Page References"<<endl;
    for(int i=0;i<N;i++){//Filling the page reference table
        int temp;
        cin>>temp;
        PageRefs.push_back(temp);
    }
    int PageFaults=0;//Number of page faults
    int PageFrames[pf];//Main Memory (Page Frames)
    int X = N;
    cout<<endl<<"Page Frames (as they keep updating) "<<endl;
    int DISTBefore[pf];//Array to calculate Distance Before page reference
    for(int i=0;i<pf;i++){
        PageFrames[i]=-1;//'-1' means empty page frame
    }
    int initialHit = -1;
    for(int i=0;i<pf;i++){
        for(int j=0;j<i;j++){//checking whether HIT occurs
            if(PageRefs[i]==PageFrames[j]){
                initialHit=PageRefs[i];
                break;
            }else{continue;}
        }
        if(initialHit!=PageRefs[i]){//If Hit occurs(Page reference is already in memory, then don't add to PageFrame)
        PageFrames[i]=PageRefs[i];//Filling the empty Page Frames
        PageFaults++;             //Page Faults occure because these frames are empty
        DISTBefore[i]=0;          //Initialise Distance Before array
        }
        cout<<endl;cout<<"[ ";for(int z=0;z<pf;z++){cout<<PageFrames[z]<<" ";}cout<<"]";cout<<endl;
    }
    int HIT=-1;
    for(int i=pf;i<N;i++){//Main loop to traverse over the remaining page references
        for(int j=0;j<pf;j++){//Checking for hit by looping over page frames
            if(PageFrames[j]==PageRefs[i]){//Check for Hit 
                                        //(presence of page reference in memory)
                HIT=PageRefs[i];
                break;
            }else{continue;}
        }
        if(PageRefs[i]!=HIT){//Ignore Page References that already exist in Page Frames
            for(int x=0;x<i;x++){//Iterate on all References before this one
                for(int y=0;y<pf;y++){
                    if(PageFrames[y]==PageRefs[x]){
                        DISTBefore[y]=i-x;//Find Distance of Reference in Frame 
                                        //from Page Reference "i"
                        break;
                    }else{continue;}
                }
            }
            int max=DISTBefore[0];
            int maxI=0;
            for(int u=0;u<pf;u++){//Find Page Reference at Maximum Distance
                if(max < DISTBefore[u]){
                    max=DISTBefore[u];
                    maxI=u;//Index of Page Reference at Maximum Distance
                }
            }
            PageFrames[maxI]=PageRefs[i];//PAGE REPLACEMENT (using LRU approach)
            PageFaults++;
            for(int p=0;p<pf;p++){
                DISTBefore[p]=0;//Reset Distance Array
            }
        }
        cout<<endl;cout<<"[ ";for(int z=0;z<pf;z++){cout<<PageFrames[z]<<" ";}cout<<"]";cout<<endl;
        }
    cout<<endl<<"The Number Of Page Faults Encountered is: "<<PageFaults<<endl;
    return 0;
}