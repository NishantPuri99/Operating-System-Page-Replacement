#include<iostream>
#include<vector>
using namespace std;
int main(){
    int pf;//Number Of Page Frames
    cout<<endl<<"Enter The Number Of Page Frames:"<<endl;
    cin>>pf;
    vector<int> PageRefs;//Vector Array of Page References
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
    int TIMEAfter[pf];//Array to calculate the how far the value in Page Frame
                      //is after the page reference
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
        PageFaults++;             //Page Faults occur because these frames are empty
        TIMEAfter[i]=-2;          //Initialise The Time After array
        }
        cout<<endl;cout<<"[ ";for(int z=0;z<pf;z++){cout<<PageFrames[z]<<" ";}cout<<"]";cout<<endl;

    }
    int HIT=-1;
    for(int i=pf;i<N;i++){//Main loop to traverse over the remaining page references
        for(int j=0;j<pf;j++){//Checking for hits by looping over page frames
            if(PageFrames[j]==PageRefs[i]){//Check for Hit 
                                          //(presence of page reference in memory)
                HIT=PageRefs[i];
                break;
            }else{continue;}
        }
        if(PageRefs[i]!=HIT){//Ignore Page References that already exist in Page Frames
            HIT=-1;
            PageFaults++;
            for(int y=0;y<pf;y++){//Iterate on all Page Frames
                for(int x=i+1;x<N;x++){
                    if(PageFrames[y]==PageRefs[x]){
                        TIMEAfter[y]=x-i;//Find Point at which the 
                                //Reference in Frame is used again after Page Reference "i"
                        break;
                    }else{continue;}
                }
                if(TIMEAfter[y]==-2){
                TIMEAfter[y]=100;
                }
            }
            int max=TIMEAfter[0];
            int maxI=0;
            for(int u=0;u<pf;u++){//Find Page Reference which takes longest time to repeat
                if(max < TIMEAfter[u]){
                    max=TIMEAfter[u];
                    maxI=u;//Index of Page Reference 
                }
            }
            PageFrames[maxI]=PageRefs[i];//PAGE REPLACEMENT (using Optimal approach)
            for(int p=0;p<pf;p++){
                TIMEAfter[p]=-2;//Reset Time Array
            }
        }
        cout<<endl;cout<<"[ ";for(int z=0;z<pf;z++){cout<<PageFrames[z]<<" ";}cout<<"]";cout<<endl;
        }

    cout<<endl<<"The Number Of Page Faults Encountered is: "<<PageFaults<<endl;
    return 0;
}