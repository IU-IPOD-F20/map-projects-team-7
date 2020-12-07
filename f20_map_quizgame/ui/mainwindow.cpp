#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

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

    // Add available quizzes to the list


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
    ui->stackedWidget->setCurrentIndex(2); // To the Quiz page
}
