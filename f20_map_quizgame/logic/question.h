#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QVector>

// Up to 4 answers allowed
class Question
{
public:
    Question(const char* question);
    QString getRightAnswer();
    void addAnswer(const char* answer);
    QVector<QString> getAnswers();
    void setRightAnswer(const unsigned int & index);
    size_t ansNum();

private:
    QString question;
    QVector<QString> answers;
    unsigned int indexOfRightAnswer = 0;
};

#endif // QUESTION_H
