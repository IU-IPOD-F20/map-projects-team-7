#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    questions.push_back("What is 2 + 2?");
    questions.push_back("What is black?");

    AnswerSet ans1;
    ans1.addAnswer("7");
    ans1.addAnswer("6");
    ans1.addAnswer("4");
    ans1.addAnswer("98");
    a_set.push_back(ans1);

    AnswerSet ans2;
    ans2.addAnswer("A car");
    ans2.addAnswer("A color");
    ans2.addAnswer("A house");
    ans2.addAnswer("A bird");
    a_set.push_back(ans2);

    on_nextButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nextButton_clicked()
{
    // Set question
    ui->questionText->setText(questions[current_question]);

    // Set answers
    ui->radioButton_1->setText(a_set[current_question].answers[0]);
    ui->radioButton_2->setText(a_set[current_question].answers[1]);
    ui->radioButton_3->setText(a_set[current_question].answers[2]);
    ui->radioButton_4->setText(a_set[current_question].answers[3]);
    // Reset answers
    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);

    // Increase 'current_questoin'
    current_question++;

    // Set question # label
    QString qNum = "Question #%1";
    ui->questionNumber->setText(qNum.arg(current_question));

    if (current_question >= questions.size()) {
        ui->nextButton->setDisabled(true);
    }
}
