//
// Created by lierenzhu on 2021/10/27.
//

#include "SpeechManager.h"
#include <iostream>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>

using namespace std;

SpeechManager::SpeechManager()
{
    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();

}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::showMenu()
{

    cout << "**************************" << endl;
    cout << "1.开始比赛" << endl;
    cout << "2.查看往届记录" << endl;
    cout << "3.清空比赛记录" << endl;
    cout << "0.退出比赛程序" << endl;
    cout << "**************************" << endl;

}

void SpeechManager::exitSystem()
{

    cout << "再见..." << endl;
    exit(0);

}

void SpeechManager::initSpeech()
{
    this->v1.clear();
    this->v2.clear();
    this->vWin.clear();
    this->speaker.clear();
    this->index = 1;
    this->record.clear();
}

void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); ++i)
    {
        string name = "选手";
        name += nameSeed[i];

        Speaker sp;
        sp.setName(name);
        sp.initScore();
        this->v1.push_back(10001 + i);
        this->speaker.insert(make_pair(10001 + i, sp));

    }

}

void SpeechManager::startSpeech()
{
    speechDraw();
    speechContest();
    showScore();
    this->index++;
    speechDraw();
    speechContest();
    showScore();
    saveRecord();
    initSpeech();
    createSpeaker();
    loadRecord();
    cout << "本届比赛圆满闭幕" << endl;
}

void SpeechManager::speechContest()
{
    cout << "第" << this->index << "轮比赛开始" << endl;
    cout << "----------------------------------" << endl;
    multimap<double, int, greater<double> > groupScore;
    int num = 0;

    vector<int> currentRound;
    if (this->index == 1)
    {
        currentRound = v1;
    }
    else
    {
        currentRound = v2;
    }

    for (vector<int>::iterator it = currentRound.begin(); it != currentRound.end(); it++)
    {
        num++;
        deque<double> d;
        cout << "评委对" << *it << "号选手的评分为" << endl;
        for (int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f;
            cout << score << " ";
            d.push_back(score);
        }
        cout << endl;

        sort(d.begin(), d.end(), greater<double>());
        d.pop_front();
        d.pop_back();

        double sum = accumulate(d.begin(), d.end(), 0);
        double avg = sum / (double) d.size();

        this->getSpeaker()[*it].setScore(this->index, avg);
        groupScore.insert(make_pair(avg, *it));
        if (num % 6 == 0)
        {
            cout << "第" << num / 6 << "组的比赛名次为" << endl;
            for (multimap<double, int, greater<double> >::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                cout << "编号：" << it->second << " 成绩：" << it->first << endl;
            }
            cout << endl;
            int count = 0;
            for (multimap<double, int, greater<double> >::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
            {
                if (this->index == 1)
                {
                    v2.push_back(it->second);
                }
                else
                {
                    vWin.push_back(it->second);
                }
            }
            groupScore.clear();
        }
    }
    cout << "第" << this->index << "轮比赛结束" << endl;
//    cout << "选手的最后得分为" << endl;
//    cout << "----------------------------------" << endl;
//    for (map<int, Speaker>::iterator it = this->getSpeaker().begin(); it != this->getSpeaker().end(); it++) {
//        cout << it->first << "号选手的得分为" << it->second.getScore()[this->index - 1] << endl;
//    }

}

void SpeechManager::speechDraw()
{

    cout << "第" << this->index << "轮选手正在抽签" << endl;
    cout << "-----------------------------------" << endl;
    cout << "抽签结果如下" << endl;

    if (this->index == 1)
    {
        random_shuffle(v1.begin(), v1.end());
        for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        random_shuffle(v2.begin(), v2.end());
        for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------------" << endl;
    cout << endl;

}

void SpeechManager::showScore()
{

    cout << "晋级选手为:" << endl;
    vector<int> v;
    if (this->index == 1)
    {
        v = v2;
    }
    else
    {
        v = vWin;
    }
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "第" << *it << "号选手" << endl;
    }

}

void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("../speech.csv", ios::out | ios::app);
    for (vector<int>::iterator it = vWin.begin(); it != vWin.end(); it++)
    {
        ofs << *it << "," << this->speaker[*it].getScore()[1] << ",";
    }
    ofs << endl;
    ofs.close();
    cout << "本次记录已写入" << endl;
    this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
    ifstream ifs("../speech.csv", ios::in);
    if (!ifs.is_open())
    {
        this->fileIsEmpty = true;
//        cout << "文件不存在..." << endl;
        ifs.close();
        return;
    }

    char c;
    ifs >> c;
    if (ifs.eof())
    {
//        cout << "文件为空..." << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    fileIsEmpty = false;

    ifs.putback(c);

    string data;
    int index = 0;
    while (ifs >> data)
    {
        cout << data << endl;
        int pos = -1;
        int start = 0;
        vector<string> v;

        while (true)
        {
            pos = data.find(',', start);
            if (pos == -1)
            {
                break;
            }
            string temp = data.substr(start, pos - start);
//            cout << temp << endl;
            v.push_back(temp);
            start = pos + 1;
        }
        this->setRecord(make_pair(index, v));
        index++;
    }
    ifs.close();
    for (map<int, vector<string> >::iterator it = record.begin(); it != record.end(); it++)
    {
        cout << it->first << "冠军:" << it->second[0] << " 分数：" << it->second[1] << endl;
    }
}

void SpeechManager::showRecord()
{
    if (this->fileIsEmpty)
    {
        cout << "文件为空或不存在..." << endl;
    }
    else
    {
        for (int i = 0; i < this->record.size(); ++i)
        {
            cout << "第" << i + 1 << "届" << \
        "冠军编号：" << this->record[i][0] << "得分：" << this->record[i][1] << " " \
        "亚军编号：" << this->record[i][2] << "得分：" << this->record[i][3] << " " \
        "季军编号：" << this->record[i][4] << "得分：" << this->record[i][5] << endl;
        }
    }
}

void SpeechManager::cleanRecord()
{
    cout << "确认清空？" << endl;
    cout << "1.确认" << endl;
    cout << "2.取消" << endl;

    int select = 0;
    cin >> select;

    if (select == 1)
    {
        ofstream ofs("../speech.csv", ios::trunc);
        ofs.close();
        this->initSpeech();
        this->createSpeaker();
        this->loadRecord();
        cout << "清空成功..." << endl;
    }
    system("clear");
}

const vector<int> &SpeechManager::getV1() const
{
    return v1;
}

void SpeechManager::setV1(const vector<int> &v1)
{
    SpeechManager::v1 = v1;
}

const vector<int> &SpeechManager::getV2() const
{
    return v2;
}

void SpeechManager::setV2(const vector<int> &v2)
{
    SpeechManager::v2 = v2;
}

const vector<int> &SpeechManager::getVWin() const
{
    return vWin;
}

void SpeechManager::setVWin(const vector<int> &vWin)
{
    SpeechManager::vWin = vWin;
}

map<int, Speaker> &SpeechManager::getSpeaker()
{
    return speaker;
}

void SpeechManager::setSpeaker(const map<int, Speaker> &speaker)
{
    SpeechManager::speaker = speaker;
}

int SpeechManager::getIndex() const
{
    return index;
}

void SpeechManager::setIndex(int index)
{
    SpeechManager::index = index;
}

bool SpeechManager::isFileIsEmpty() const
{
    return fileIsEmpty;
}

void SpeechManager::setFileIsEmpty(bool fileIsEmpty)
{
    SpeechManager::fileIsEmpty = fileIsEmpty;
}

const map<int, vector<string>> &SpeechManager::getRecord() const
{
    return record;
}

void SpeechManager::setRecord(map<int, vector<string>> &record)
{
    SpeechManager::record = record;
}

void SpeechManager::setRecord(pair<int, vector<string>> record)
{
    SpeechManager::record.insert(record);
}
