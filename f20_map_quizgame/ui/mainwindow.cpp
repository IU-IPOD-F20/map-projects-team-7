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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_to_quiz_list_clicked()
{
    quizSet.clear();

    // Add sample quizzes to quiz set
    quizSet.append(*Quiz::getSampleQuiz1());
    quizSet.append(*Quiz::getSampleQuiz2());

    // Add stored quizzes to quiz set
    QFile savedFile("quizzes.json");
    if (!savedFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Couldn't open quizzes file.";
    }
    QByteArray savedData = savedFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(savedData));
    QJsonArray quizzes = loadDoc.array();
    for (int i = 0; i < quizzes.size(); i++) {
        QJsonObject quiz = quizzes[i].toObject();
        Quiz q(quiz["title"].toString().toLocal8Bit().data());
        QJsonArray questions = quiz["questions"].toArray();
        for (int j = 0; j < questions.size(); j++) {
            QJsonObject question = questions[j].toObject();
            Question* qst = new Question(question["title"].toString().toLocal8Bit().data(), question["id"].toInt());
            qst->setRightAnswer(question["right_answer"].toInt());
            QJsonArray answers = question["answers"].toArray();
            for (int k = 0; k < answers.size(); k++) {
                qst->addAnswer(answers[k].toString().toLocal8Bit().data());
            }
            q.addQuestion(qst);
        }
        quizSet.append(q);
    }
    savedFile.close();

    // Add available quizzes to the list
    for (int i = 0; i < ui->list_quizzes->count(); i++) {
        delete ui->list_quizzes->takeItem(i);
    }
    for (auto quiz : quizSet) {
        ui->list_quizzes->addItem(quiz.getName());
    }

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
        ui->line_edit_login->setText("");
        ui->line_edit_password->setText("");
    }
    else {
        qDebug() << "LOGIN ERROR!";
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
    savedFile2.write(QJsonDocument(users).toJson());
    savedFile2.close();

    ui->stackedWidget->setCurrentIndex(login_page_index);
}

void MainWindow::on_button_add_answer_clicked()
{
    ui->button_remove_answer->setEnabled(true);
    ui->list_view_question_answers->addItem(ui->line_edit_answer_text->text());
    ui->line_edit_answer_text->setText("");
}

void MainWindow::on_button_remove_answer_clicked()
{
    for (auto ans : ui->list_view_question_answers->selectedItems()) {
        delete ui->list_view_question_answers->takeItem(ui->list_view_question_answers->row(ans));
    }
    ui->line_edit_answer_text->setText("");
    if (ui->list_view_question_answers->count() == 0) {
        ui->button_remove_answer->setEnabled(false);
    }
}

void MainWindow::on_button_finish_question_creation_clicked()
{
    Question q(ui->line_edit_question_text->text().toLocal8Bit().data());
    for (int i = 0; i < ui->list_view_question_answers->count(); i++) {
        QListWidgetItem* item = ui->list_view_question_answers->item(i);
        q.addAnswer(item->text().toLocal8Bit().data());
    }
    for (int i = 0; i < ui->list_view_question_answers->count(); i++) {
        delete ui->list_view_question_answers->takeItem(i);
    }
    ui->list_view_question_answers->clear();
    q.setRightAnswer(ui->spin_correct_answer->value());
    createQuestions.append(q);
    ui->spin_correct_answer->setValue(1);
    ui->list_quiz_questions->addItem(ui->line_edit_question_title->text());
    ui->line_edit_question_text->setText("");
    ui->line_edit_question_title->setText("");
    ui->stackedWidget->setCurrentIndex(quiz_create_page_index);
}

void MainWindow::on_button_finish_quiz_creation_clicked()
{
    Quiz q(ui->line_edit_quiz_title->text().toLocal8Bit().data());
    q.addQuestion(createQuestions);
    quizSet.append(q);

    QFile savedFile("quizzes.json");
    if (!savedFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Couldn't open quizzes file.";
    }
    QByteArray savedData = savedFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(savedData));
    QJsonArray quizzes = loadDoc.array();
    QJsonObject newQuiz;
    newQuiz.insert("title", ui->line_edit_quiz_title->text());
    QJsonArray questions;
    int i = 1;
    for (auto qst : createQuestions) {
        QJsonObject qstJson;
        qstJson.insert("id", i++);
        qstJson.insert("title", qst.getQuestion());
        qstJson.insert("right_answer", qst.getRightAnswer());
        QJsonArray answers;
        for (auto ans : qst.getAnswers()) {
            qDebug() << "FFF " << qst.getAnswers().size();
            answers.append(ans);
        }
        qstJson.insert("answers", answers);
        questions.append(qstJson);
    }
    createQuestions.clear();
    newQuiz.insert("questions", questions);
    quizzes.append(newQuiz);
    savedFile.close();

    QFile savedFile2("quizzes.json");
    if (!savedFile2.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Couldn't open save file.";
    }
    savedFile2.write(QJsonDocument(quizzes).toJson());
    savedFile2.close();

    ui->stackedWidget->setCurrentIndex(login_page_index);
}

void MainWindow::on_button_add_question_clicked()
{
    if (ui->list_view_question_answers->count() == 0) {
        ui->button_remove_answer->setEnabled(false);
    }
    ui->stackedWidget->setCurrentIndex(question_create_page_index);
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
