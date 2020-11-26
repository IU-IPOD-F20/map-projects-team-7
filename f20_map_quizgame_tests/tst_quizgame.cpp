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


QTEST_APPLESS_MAIN(QuizGame)

#include "tst_quizgame.moc"
