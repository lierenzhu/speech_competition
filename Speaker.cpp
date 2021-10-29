//
// Created by lierenzhu on 2021/10/27.
//

#include <string>
#include "Speaker.h"

using namespace std;

const string &Speaker::getName() const {
    return name;
}

void Speaker::setName(const string &name) {
    Speaker::name = name;
}

const double *Speaker::getScore() const {
    return score;
}

void Speaker::setScore(int round, double avg){
    score[round-1] = avg;
}

void Speaker::initScore() {

    for (int i = 0; i < 2; ++i) {

        this->score[i] = 0;
    }

}
