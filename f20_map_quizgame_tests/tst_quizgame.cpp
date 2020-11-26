#include <QtTest>

// add necessary includes here

class QuizGame : public QObject
{
    Q_OBJECT

public:
    QuizGame();
    ~QuizGame();

private slots:
    void test_case1();
    void test_case2();

};

QuizGame::QuizGame()
{

}

QuizGame::~QuizGame()
{

}

void QuizGame::test_case1()
{
    QString test = "Hello, Tests!!!";
    QCOMPARE(test, "Hello, Tests!!!");
}

void QuizGame::test_case2()
{
    QString test = "Hello, New Tests!!!";
    QCOMPARE(test, "Hello, New Tests!!!");
}

QTEST_APPLESS_MAIN(QuizGame)

#include "tst_quizgame.moc"
