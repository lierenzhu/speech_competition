//
// Created by lierenzhu on 2021/10/27.
//

#ifndef SPEECH_COMPETITION_SPEAKER_H
#define SPEECH_COMPETITION_SPEAKER_H

#include <iostream>
#include <string>

using namespace std;

class Speaker {
public:
    const string &getName() const;

    void setName(const string &name);

    const double *getScore() const;

    void initScore();

    void setScore(int round, double avg);

private:
    string name;
    double score[2];
};


#endif //SPEECH_COMPETITION_SPEAKER_H
