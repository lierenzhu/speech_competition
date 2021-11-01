#include <iostream>
#include "SpeechManager.h"
#include <iterator>
#include "Speaker.h"

using namespace std;

int main() {
//    std::cout << "Hello, World!" << std::endl;
    SpeechManager speechManager;
//    for(map<int,Speaker>::iterator it=speechManager.getSpeaker().begin();it!=speechManager.getSpeaker().end();it++)
//    {
//        cout << "num" <<it->first<<"name"<<it->second.getName() << "score" << it->second.getScore()[0]<<endl;
//    }
    int choice = 0;
    while (true)
    {
        speechManager.showMenu();
        cout << "请输入你的选择：" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                speechManager.startSpeech();
                break;
            case 2:
                speechManager.showRecord();
                break;
            case 3:
                break;
            case 0:
                speechManager.exitSystem();
                break;
            default:
                system("clear");
                break;
        }
    }
    getchar();
    return 0;

}
