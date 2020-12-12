#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QStringLiteral>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>
#include <QJsonValue>
#include <QCoreApplication>

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

    // Button groups
    registerGroup.addButton(ui->radio_button_as_admin, 0);
    registerGroup.addButton(ui->radio_button_as_user, 1);

    // Configure UI elements
    ui->label_title_of_the_game->setGraphicsEffect(shadowEffect);
    ui->label_title_of_the_game_2->setGraphicsEffect(shadowEffect);
    ui->label_title_of_the_game_3->setGraphicsEffect(shadowEffect);
    ui->label_title_of_the_game_4->setGraphicsEffect(shadowEffect);
    ui->label_title_of_the_game_5->setGraphicsEffect(shadowEffect);
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
    ui->stackedWidget->setCurrentIndex(quizzes_page_index); // To the Quiz list page
}

void MainWindow::on_button_attempt_quiz_clicked()
{
    // -- Setup the quiz questions --
    Quiz* quiz = findQuizByName(ui->list_quizzes->currentItem()->text());
    setUpQuizPage(quiz->getNextQuestion());

    ui->stackedWidget->setCurrentIndex(main_page_index); // To the Quiz page
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

    ui->stackedWidget->setCurrentIndex(finish_page_index); // To the Results page
}

void MainWindow::on_button_back_to_quiz_list_clicked()
{
    ui->button_finish->setVisible(false);
    ui->button_next->setVisible(true);
    ui->stackedWidget->setCurrentIndex(quizzes_page_index); // To the Quiz list page
}

void MainWindow::on_button_register_clicked()
{
    // To the Registration
    ui->line_edit_login_reg->setText("");
    ui->line_edit_password_reg->setText("");
    ui->stackedWidget->setCurrentIndex(registration_page_index);
}

void MainWindow::on_button_login_clicked()
{
    // Check credentials
    QString login = ui->line_edit_login->text();
    QString password = ui->line_edit_password->text();

    if (checkCredentials(login, password)) {
        if (localUser->isAdmin()) {
            ui->stackedWidget->setCurrentIndex(quiz_create_page_index);
        } else {
            ui->stackedWidget->setCurrentIndex(start_page_index);
        }
    }
    else {
        // LOGIN ERROR
    }
}

void MainWindow::on_button_finish_registeration_clicked()
{
    bool isAdmin = registerGroup.button(0)->isChecked();
    if (isAdmin) {
        localUser = new User(true);
    }
    else {
        localUser = new User(false);
    }

    QFile savedFile("users.json");
    if (!savedFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Couldn't open save file.";
    }
    QByteArray savedData = savedFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(savedData));
    QJsonArray users = loadDoc.array();
    QJsonObject newUser;
    newUser.insert("login", ui->line_edit_login_reg->text());
    newUser.insert("password", ui->line_edit_password_reg->text());
    newUser.insert("is_admin", isAdmin);
    users.append(newUser);
    savedFile.close();

    QFile savedFile2("users.json");
    if (!savedFile2.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Couldn't open save file.";
    }
    savedFile2.write(QJsonDocument(QJsonDocument(users)).toJson());
    savedFile2.close();

    ui->stackedWidget->setCurrentIndex(login_page_index);
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

bool MainWindow::checkCredentials(QString login, QString password)
{
    QFile savedFile("users.json");

    if (!savedFile.open(QIODevice::ReadOnly)) {
        qDebug() << "NO";
        return false;
    }

    QByteArray savedData = savedFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(savedData));
    QJsonArray users = loadDoc.array();
    for (int i = 0; i < users.size(); i++) {
        QJsonObject user = users[i].toObject();
        if (user["login"] == login && user["password"] == password) {
            savedFile.close();
            localUser = new User(user["is_admin"].toBool());
            return true;
        }
    }

    qDebug() << "NO SUCH USER!";
    return false;
}
