#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QVector>
#include <QButtonGroup>

#include "logic/quiz.h"
#include "logic/user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    const int login_page_index = 0;
    const int registration_page_index = 1;
    const int quiz_create_page_index = 2;
    const int question_create_page_index = 3;
    const int start_page_index = 4;
    const int quizzes_page_index = 5;
    const int main_page_index = 6;
    const int finish_page_index = 7;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_to_quiz_list_clicked();

    void on_button_attempt_quiz_clicked();

    void on_button_next_clicked();

    void on_button_finish_clicked();

    void on_button_back_to_quiz_list_clicked();

    void on_button_register_clicked();

    void on_button_login_clicked();

    void on_button_finish_registeration_clicked();

    void on_button_add_answer_clicked();

    void on_button_remove_answer_clicked();

    void on_button_finish_question_creation_clicked();

    void on_button_finish_quiz_creation_clicked();

    void on_button_add_question_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Quiz> quizSet;
    Quiz* findQuizByName(QString name);
    void setUpQuizPage(Question q);
    QVector<QRadioButton*> rbRefs;
    bool checkCredentials(QString login, QString password);
    User* localUser;
    QButtonGroup registerGroup;
    QVector<Question> createQuestions;
};
#endif // MAINWINDOW_H
