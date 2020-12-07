#include "quiz.h"

Quiz::Quiz(const char* name) : quizName(QString(name)) {}

void Quiz::addQuestion(Question* q)
{
    questions.push_back(*q);
}

void Quiz::addQuestion(QVector<Question> vec)
{
    questions = vec;
}

void Quiz::reset()
{
    score = 0;
    currentQuestion = -1;
}

Question Quiz::getNextQuestion()
{
    return questions[++currentQuestion];
}

Quiz* Quiz::getSampleQuiz1()
{
    Question q1("What is 2 + 2?", 1);
    q1.addAnswer("7");
    q1.addAnswer("4");
    q1.addAnswer("19");
    q1.addAnswer("0");
    q1.setRightAnswer(2);

    Question q2("What cheese is made of?", 2);
    q2.addAnswer("Wood");
    q2.addAnswer("Stone");
    q2.addAnswer("Milk");
    q2.setRightAnswer(3);

    Question q3("Who is the greates russian of all times?", 3);
    q3.addAnswer("Peter the Great");
    q3.addAnswer("Vladimir Putin");
    q3.addAnswer("Mikhail Gorbachev");
    q3.addAnswer("Ivan the Terrible");
    q3.setRightAnswer(2);

    Question q4("Who killed John Kennedy?", 4);
    q4.addAnswer("Nikita Khrushchev");
    q4.addAnswer("Lee Harvey Oswald");
    q4.addAnswer("CIA");
    q4.addAnswer("FBI");
    q4.setRightAnswer(3);

    Quiz* sampleQuiz1 = new Quiz("Sample quiz 1");
    sampleQuiz1->addQuestion(QVector<Question>{q1, q2, q3, q4});

    return sampleQuiz1;
}

Quiz *Quiz::getSampleQuiz2()
{
    Question q1("What is 2 * 3?", 1);
    q1.addAnswer("7");
    q1.addAnswer("6");
    q1.addAnswer("19");
    q1.addAnswer("0");
    q1.setRightAnswer(2);

    Question q2("What a tree is made of?", 2);
    q2.addAnswer("Wood");
    q2.addAnswer("Stone");
    q2.addAnswer("Milk");
    q2.setRightAnswer(1);

    Question q3("Who is not the greates russian of all times?", 3);
    q3.addAnswer("Peter the Great");
    q3.addAnswer("Vladimir Putin");
    q3.addAnswer("Mikhail Gorbachev");
    q3.addAnswer("Ivan the Terrible");
    q3.setRightAnswer(3);

    Question q4("Who killed John Kennedy?", 4);
    q4.addAnswer("Nikita Khrushchev");
    q4.addAnswer("Lee Harvey Oswald");
    q4.addAnswer("CIA");
    q4.addAnswer("FBI");
    q4.setRightAnswer(4);

    Quiz* sampleQuiz2 = new Quiz("Sample quiz 2");
    sampleQuiz2->addQuestion(QVector<Question>{q1, q2, q3, q4});

    return sampleQuiz2;
}
