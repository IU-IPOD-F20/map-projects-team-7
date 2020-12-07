#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QVector>

#include "logic/quiz.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_to_quiz_list_clicked();

    void on_button_attempt_quiz_clicked();

    void on_button_next_clicked();

    void on_button_finish_clicked();

    void on_button_back_to_quiz_list_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Quiz> quizSet;
    Quiz* findQuizByName(QString name);
    void setUpQuizPage(Question q);
    QVector<QRadioButton*> rbRefs;
};
#endif // MAINWINDOW_H
