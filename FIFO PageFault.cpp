#include<iostream>
#include<vector>
#include<queue>
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
    for(int i=0;i<pf;i++){
        PageFrames[i]=-1;//'-1' Means Empty Page Frame
    }
    queue<int> FIFOq;//Queue to check FIFO approach of Page Replacement
    cout<<endl<<"Page Frames (as they keep updating) "<<endl;
    int initialHit=-1;
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
        FIFOq.push(PageRefs[i]);  //Pushing these into queue
        }
        cout<<endl;cout<<"[ ";for(int z=0;z<pf;z++){cout<<PageFrames[z]<<" ";}cout<<"]";cout<<endl;

    }
    int HIT=-1;
    for(int i=pf;i<N;i++){//Main loop to traverse over the remaining page references
        for(int j=0;j<pf;j++){//Check for Hit by Looping over page frames
            if(PageFrames[j]==PageRefs[i]){//Check for Hit 
                                          //(presence of page reference in memory)
                HIT=PageRefs[i];
                break;
            }else{continue;}
        }
        for(int j=0;j<pf;j++){//Using FIFO approach for Page Replacement
            if(PageRefs[i]!=HIT){//Removing case with already HIT
            if(PageFrames[j]==FIFOq.front()){//First In First Out Approach used by Queue
                PageFrames[j]=PageRefs[i];//PAGE REPLACEMENT (using FIFO approach)
                FIFOq.pop();            //Popping the replaced Reference
                FIFOq.push(PageRefs[i]);//Adding new page reference to queue
                PageFaults++;
                break;
            }else{continue;}
            }else{HIT=-1;break;}
        }
    cout<<endl;cout<<"[ ";for(int z=0;z<pf;z++){cout<<PageFrames[z]<<" ";}cout<<"]";cout<<endl;
    }
    cout<<endl<<"The Number Of Page Faults Encountered is: "<<PageFaults<<endl;
    return 0;
}