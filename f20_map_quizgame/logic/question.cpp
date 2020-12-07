#include "question.h"

Question::Question(const char* question) : question(QString(question)) {}

QString Question::getRightAnswer() {
    return answers[indexOfRightAnswer];
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
    indexOfRightAnswer = index - 1;
}

size_t Question::ansNum()
{
    return answers.size();
}
