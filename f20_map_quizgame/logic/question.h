#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QVector>

// Up to 4 answers allowed
class Question
{
public:
    Question(const char* question, int num = 0);
    QString getQuestion() { return question; }
    int getRightAnswer();
    void addAnswer(const char* answer);
    QVector<QString> getAnswers();
    void setRightAnswer(const unsigned int & index);
    size_t ansNum();
    int getQuestionNumber() { return questionNum; }

private:
    QString question;
    QVector<QString> answers;
    unsigned int indexOfRightAnswer = 0;
    int questionNum;
};

#endif // QUESTION_H
