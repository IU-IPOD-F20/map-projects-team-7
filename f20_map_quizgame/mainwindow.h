#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "answerset.h"


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
    void on_nextButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QString> questions;
    std::vector<AnswerSet> a_set;
    unsigned int current_question = 0;
};
#endif // MAINWINDOW_H
