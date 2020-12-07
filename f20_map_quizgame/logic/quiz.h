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
    void increaseScore() { score++; }
    void reset();
    int getScore() { return score; }
    int maxScore() { return questions.size(); }
    Question getNextQuestion();
    QString getName() { return quizName; }
    bool isLastQuestion() { return currentQuestion == questions.size() - 1; }
    bool isAnswerCorrect(int answer) { return answer == questions[currentQuestion].getRightAnswer(); }
    static Quiz* getSampleQuiz1();
    static Quiz* getSampleQuiz2();

private:
    QString quizName;
    QVector<Question> questions;
    int currentQuestion = -1;
    int score = 0;
};

#endif // QUIZ_H
