#include <QtTest>

#include "../f20_map_quizgame/logic/quiz.h"
#include "../f20_map_quizgame/logic/question.h"

class QuizGame : public QObject
{
    Q_OBJECT

public:
    QuizGame();
    ~QuizGame();

private slots:
    void question_test_case1();
    void question_test_case2();
    void question_test_case3();
    void question_test_case4();

    void quiz_test_case1();
    void quiz_test_case2();
    void quiz_test_case3();
    void quiz_test_case4();
};

QuizGame::QuizGame()
{

}

QuizGame::~QuizGame()
{

}

void QuizGame::question_test_case1()
{
    const char* qtext = "Question text";
    Question q(qtext);
    QCOMPARE(q.getQuestion(), qtext);
}

void QuizGame::question_test_case2()
{
    Question q("Question text", 1);
    QCOMPARE(q.getQuestionNumber(), 1);
}

void QuizGame::question_test_case3()
{
    Question q("Question text", 1);
    q.addAnswer("Answer text");
    QCOMPARE(q.ansNum(), 1);
}

void QuizGame::question_test_case4()
{
    Question q("Question text", 1);
    q.setRightAnswer(2);
    QCOMPARE(q.getRightAnswer(), 2);
}



void QuizGame::quiz_test_case1()
{
    const char* name = "Quiz name";
    Quiz q(name);
    QCOMPARE(q.getName(), name);
}

void QuizGame::quiz_test_case2()
{
    const char* questoin_text = "Question text";
    const char* quiz_name = "Quiz name";
    Quiz q(quiz_name);
    q.addQuestion(Question(questoin_text));
    q.getNextQuestion();
    QVERIFY(q.isLastQuestion());
}

void QuizGame::quiz_test_case3()
{
    const char* questoin_text = "Question text";
    const char* quiz_name = "Quiz name";
    Quiz q(quiz_name);
    Question q1(questoin_text);
    q1.setRightAnswer(2);
    q.addQuestion(q1);
    q.getNextQuestion();
    QVERIFY(q.isAnswerCorrect(2));
}

void QuizGame::quiz_test_case4()
{
    const char* quiz_name = "Quiz name";
    Quiz q(quiz_name);
    q.increaseScore();
    q.increaseScore();
    q.increaseScore();
    QCOMPARE(q.getScore(), 3);
}

QTEST_APPLESS_MAIN(QuizGame)
#include "tst_quizgame.moc"
