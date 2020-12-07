#ifndef QUIZ_H
#define QUIZ_H

#include <QVector>
#include "question.h"

class Quiz
{
public:
    Quiz(const char* name);
    void addQuestion(Question q);
    void addQuestion(QVector<Question> vec);
    Question getNextQuestion();
    static Quiz getSampleQuiz();

private:
    QString quizName;
    QVector<Question> questions;
    unsigned int currentQuestion = 0;
};

#endif // QUIZ_H
