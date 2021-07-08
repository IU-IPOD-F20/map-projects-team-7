#include "question.h"

Question::Question()
{

}

Question::Question(const char* question, int num) :
    question(QString(question)),
    questionNum(num)
{}

int Question::getRightAnswer() {
    return indexOfRightAnswer;
}

void Question::addAnswer(const char* answer)
{
    answers.push_back(QString(answer));
}

QVector<QString> Question::getAnswers()
{
    return answers;
}

void Question::setRightAnswer(const unsigned int &index)
{
    indexOfRightAnswer = index;
}

size_t Question::ansNum()
{
    return answers.size();
}

Question::~Question()
{

}
