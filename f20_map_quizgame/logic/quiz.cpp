#include "quiz.h"

Quiz::Quiz(const char* name) : quizName(QString(name)) {}

void Quiz::addQuestion(Question q)
{
    questions.push_back(q);
}

void Quiz::addQuestion(std::vector<Question> vec)
{
    questions = vec;
}

Question Quiz::getNextQuestion()
{
    return questions[currentQuestion++];
}

Quiz Quiz::getSampleQuiz()
{
    Question q1("What is 2 + 2?");
    q1.addAnswer("7");
    q1.addAnswer("4");
    q1.addAnswer("19");
    q1.addAnswer("0");
    q1.setRightAnswer(2);

    Question q2("What cheese is made of?");
    q2.addAnswer("Wood");
    q2.addAnswer("Stone");
    q2.addAnswer("Milk");
    q2.addAnswer("Water");
    q2.setRightAnswer(3);

    Question q3("Who is the greates russian of all times?");
    q3.addAnswer("Peter the Great");
    q3.addAnswer("Vladimir Putin");
    q3.addAnswer("Mikhail Gorbachev");
    q3.addAnswer("Ivan the Terrible");
    q3.setRightAnswer(2);

    Question q4("Who killed John Kennedy?");
    q4.addAnswer("Nikita Khrushchev");
    q4.addAnswer("Lee Harvey Oswald");
    q4.addAnswer("CIA");
    q4.addAnswer("FBI");
    q4.setRightAnswer(3);

    Quiz sampleQuiz("Sample quiz");
    sampleQuiz.addQuestion(QVector<Question>{q1, q2, q3, q4});

    return sampleQuiz;
}
