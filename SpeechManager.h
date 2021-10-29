//
// Created by lierenzhu on 2021/10/27.
//

//提供菜单界面和用户交互
//演讲比赛的流程控制
//读写文件的交互

#ifndef SPEECH_COMPETITION_SPEECHMANAGER_H
#define SPEECH_COMPETITION_SPEECHMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include "Speaker.h"

using namespace std;

class SpeechManager {

public:
    SpeechManager();
    ~SpeechManager();
    void showMenu();
    void exitSystem();
    void initSpeech();
    void createSpeaker();
    void startSpeech();
    void speechDraw();
    void speechContest();
    void showScore();

private:
    vector<int> v1;
    vector<int> v2;
    vector<int> vWin;
    map<int, Speaker> speaker;
    int index;
public:
    int getIndex() const;

    void setIndex(int index);

public:
    const vector<int> &getV1() const;

    void setV1(const vector<int> &v1);

    const vector<int> &getV2() const;

    void setV2(const vector<int> &v2);

    const vector<int> &getVWin() const;

    void setVWin(const vector<int> &vWin);

    map<int, Speaker> &getSpeaker() ;

    void setSpeaker(const map<int, Speaker> &speaker);
};


#endif //SPEECH_COMPETITION_SPEECHMANAGER_H
