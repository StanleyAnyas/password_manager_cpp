#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm> 
// #include <bits/stdc++.h> 
using namespace std;

class Television{
    private:
        bool isTvOn;
        int volume;
        int channel;
        bool isSilence;

    public:
        Television(){
            isTvOn = false;
            volume = 5;
            channel = 1;
            isSilence = false;
        }
        ~Television(){}
        bool getTvOn(){
            return isTvOn;
        }
        void redButton(){
            isTvOn = !isTvOn;
        }
        int getVolume(){
            return volume;
        }
        int getChannel(){
            return channel;
        }
        bool getSilence(){
            return isSilence;
        }
        void nextChannel(){
            channel == 99 ? channel = 1 : channel++;
        }
        void previousChannel(){
            channel == 1 ? channel = 99 : channel--;
        }
        void increaseVolume(){
            volume < 10 && volume++;
        }
        void decreaseVolume(){
            volume > 0 && volume--;
        }

        void setChannel(int channelNum){
            if(channelNum <= 99 && channelNum > 0){
                channel = channelNum;
            }
        }

        void setSilence(){
            if(isSilence){
                isSilence = false;
            }else{
                isSilence = true;
                volume = 0;
            }
        }
};  
int main() {
    Television myTv;
    myTv.redButton();
    myTv.nextChannel();
    myTv.increaseVolume();
    int volume = myTv.getVolume();
    int channel = myTv.getChannel();
    cout << "il volume e' " << volume << endl; // 6
    cout << "il canale e' " << channel << endl; // 2
    myTv.setChannel(99);
    int channel2 = myTv.getChannel();
    cout << "il canale e' " << channel2 << endl; // 99
    return 0;
} 