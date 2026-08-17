#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->display->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    setWindowFlags(Qt::Window);
    resize(400, 500);

    setWindowIcon(QIcon(":/assets/icon/logo.png"));

    // =========================
    // Numbers
    // =========================

    QPushButton *buttons[] = {
        ui->btn0,
        ui->btn1,
        ui->btn2,
        ui->btn3,
        ui->btn4,
        ui->btn5,
        ui->btn6,
        ui->btn7,
        ui->btn8,
        ui->btn9
    };

    for (QPushButton *button : buttons){
        connect(button, &QPushButton::clicked, this, [this, button](){

            QString number = button->text();

            if (waitSecondNumber){
                ui->display->setText(number);
                waitSecondNumber = false;
            }
            else if (ui->display->text() == "0"){
                ui->display->setText(number);
            }
            else{
                ui->display->setText(
                    ui->display->text() + number
                );
            }
        });
    }

    // =========================
    // Decimal dot
    // =========================

    connect(ui->btnDot, &QPushButton::clicked, this, [this](){
        dot();
    });

    // =========================
    // Operations
    // =========================


    connect(ui->btnPlus, &QPushButton::clicked, this, [this](){
        defineOperation("+");
    });

    connect(ui->btnMinus, &QPushButton::clicked, this, [this](){
        defineOperation("-");
    });

    connect(ui->btnMultiply, &QPushButton::clicked, this, [this](){
        defineOperation("*");
    });

    connect(ui->btnDivide, &QPushButton::clicked, this, [this](){
        defineOperation("/");
    });
    connect(ui->btnPercentage, &QPushButton::clicked, this, [this](){
        double percentage = ui->display->text().toDouble();
        double percentageResult = percentage / 100;
        ui->display->setText(
            QString::number(percentageResult)
        );
        
    });

    // =========================
    // Equal
    // =========================

    connect(ui->btnEquals, &QPushButton::clicked, this, [this](){
        equal();
    });


    // =========================
    // Clean
    // =========================

    connect(ui->btnClear, &QPushButton::clicked, this, [this](){

        ui->display->setText("0");

        firstNumber= 0;
        operation.clear();
        waitSecondNumber = false;
    });

    // =========================
    // Backspace
    // =========================

    connect(ui->btnDel, &QPushButton::clicked, this, [this](){
        deleteNumber();
    });
}

    void MainWindow::defineOperation(const QString &op){  
        firstNumber = ui->display->text().toDouble();
        operation = op;
        waitSecondNumber = true;
}

void MainWindow::addNumber(const QString &number){
    if (waitSecondNumber){
        ui->display->setText(number);
        waitSecondNumber = false;
    }
    else if (ui->display->text() == "0"){
        ui->display->setText(number);
    }
    else {
        ui->display->setText(
            ui->display->text() + number
        );
    }
}

    // =========================
    // Keyboard keys
    // =========================

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_0){
        addNumber("0");
    }
    else if (event->key() == Qt::Key_1){
        addNumber("1");
    }
    else if (event->key() == Qt::Key_2){
        addNumber("2");
    }
    else if (event->key() == Qt::Key_3){
        addNumber("3");
    }
    else if (event->key() == Qt::Key_4){
        addNumber("4");
    }
    else if (event->key() == Qt::Key_5){
        addNumber("5");
    }
    else if (event->key() == Qt::Key_6){
        addNumber("6");
    }
    else if (event->key() == Qt::Key_7){
        addNumber("7");
    }
    else if (event->key() == Qt::Key_8){
        addNumber("8");
    }
    else if (event->key() == Qt::Key_9){
        addNumber("9");
    }
    else {
        calculateKeyboard(event);
    }
}

void MainWindow::calculateKeyboard(QKeyEvent *event){

    if (event->key() == Qt::Key_Plus) {
        defineOperation("+");
    }
    else if (event->key() == Qt::Key_Minus){
        defineOperation("-");
    }
    else if (event->key() == Qt::Key_Slash){
        defineOperation("/");
    }
    else if (event->key() == Qt::Key_Asterisk){
        defineOperation("*");
    }
    else if (event->key() == Qt::Key_Backspace){
        deleteNumber();
    }
    else if (event->key() == Qt::Key_Comma || event->key() == Qt::Key_Period){
        dot();
    }
    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        equal();
    }
    
}

void MainWindow::dot(){
    if (!ui->display->text().contains(".")){
            ui->display->setText(
                ui->display->text() + "."
            );
        }
}

void MainWindow::deleteNumber(){
    QString text = ui->display->text();

    if (text.length() <= 1) {
        ui->display->setText("0");
    }
    else {
        text.chop(1);
        ui->display->setText(text);
    }
}

void MainWindow::equal(){
        double secondNumber =
            ui->display->text().toDouble();

        double result = 0;

        if (operation == "+"){
            result = firstNumber + secondNumber;
        }
        else if (operation == "-"){
            result = firstNumber - secondNumber;
        }
        else if (operation == "*"){
            result = firstNumber * secondNumber;
        }
        else if (operation == "/"){

            if (secondNumber == 0){
                ui->display->setText("Error");
                return;
            }

            result = firstNumber / secondNumber;
        }
        ui->display->setText(
            QString::number(result)
        );

        waitSecondNumber = true;
}

MainWindow::~MainWindow(){
    delete ui;
}