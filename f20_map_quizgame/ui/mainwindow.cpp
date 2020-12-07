#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // -- Setup the UI --

    // Effects
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(5);
    shadowEffect->setOffset(2, 2);

    // Configure UI elements
    ui->label_title_of_the_game->setGraphicsEffect(shadowEffect);
    ui->button_finish->setVisible(false);

    // Add sample quizzes to quiz set
    quizSet.append(*Quiz::getSampleQuiz1());
    quizSet.append(*Quiz::getSampleQuiz2());

    // Add available quizzes to the list
    for (auto quiz : quizSet) {
        ui->list_quizzes->addItem(quiz.getName());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_to_quiz_list_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // To the Quiz list page
}

void MainWindow::on_button_attempt_quiz_clicked()
{
    // -- Setup the quiz questions --
    Quiz* quiz = findQuizByName(ui->list_quizzes->currentItem()->text());
    setUpQuizPage(quiz->getNextQuestion());

    ui->stackedWidget->setCurrentIndex(2); // To the Quiz page
}


void MainWindow::on_button_next_clicked()
{
    // Determine whether the user has answered correctly or not
    int answer = 1;
    for (int i = 0; i < rbRefs.size(); i++) {
        if (rbRefs[i]->isChecked()) {
            answer = i + 1;
        }
    }

    // Switch to the next question
    Quiz* quiz = findQuizByName(ui->list_quizzes->currentItem()->text());
    if (quiz->isAnswerCorrect(answer)) {
        quiz->increaseScore();
    }
    setUpQuizPage(quiz->getNextQuestion());

    if (quiz->isLastQuestion()) {
        ui->button_finish->setVisible(true);
        ui->button_next->setVisible(false);
    }
}

void MainWindow::on_button_finish_clicked()
{
    // Determine whether the user has answered correctly or not
    int answer = 1;
    for (int i = 0; i < rbRefs.size(); i++) {
        if (rbRefs[i]->isChecked()) {
            answer = i + 1;
        }
    }

    Quiz* quiz = findQuizByName(ui->list_quizzes->currentItem()->text());
    if (quiz->isAnswerCorrect(answer)) {
        quiz->increaseScore();
    }

    ui->label_quiz_score->setText(
                QString("Your score: %1 of %2")
                .arg(QString::number(quiz->getScore())
                     , QString::number(quiz->maxScore()))
                );
    quiz->reset();

    ui->stackedWidget->setCurrentIndex(3); // To the Results page
}

void MainWindow::on_button_back_to_quiz_list_clicked()
{
    ui->button_finish->setVisible(false);
    ui->button_next->setVisible(true);
    ui->stackedWidget->setCurrentIndex(1); // To the Quiz list page
}


Quiz* MainWindow::findQuizByName(QString name)
{
    for(int i = 0; i < quizSet.size(); i++) {
        if (quizSet[i].getName() == name){
            return &quizSet[i];
        }
    }
    return NULL;
}

void MainWindow::setUpQuizPage(Question q)
{
    ui->label_question_number->setText(QString("Question #%1").arg(QString::number(q.getQuestionNumber())));
    ui->label_question->setText(q.getQuestion());

    // Refresh answers
    for (auto rb : rbRefs) {
        ui->layout_answers->removeWidget(rb);
        delete rb;
    }
    rbRefs.clear();

    for (auto ans : q.getAnswers()) {
        QRadioButton* rb = new QRadioButton();
        rbRefs.append(rb);
        rb->setFont(QFont("Sylfaen", 14));
        rb->setText(ans);
        ui->layout_answers->addWidget(rb);
    }
}
