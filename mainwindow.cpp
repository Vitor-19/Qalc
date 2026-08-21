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
            addNumber(button->text());
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
        percentage();
        
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

        firstNumber = 0;
        lastSecondNumber = 0;
        operation.clear();

       waitSecondNumber = false;
      isRepeatingEqual = false;
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
    isRepeatingEqual = false;
}

void MainWindow::addNumber(const QString &number){
    isRepeatingEqual = false;
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
    int key = event->key();

    if (key >= Qt::Key_0 && key <= Qt::Key_9) {
        addNumber(event->text());
    }else {
        calculateKeyboard(event);
    }
}

void MainWindow::calculateKeyboard(QKeyEvent *event){

    switch (event->key())
    {
    case Qt::Key_Plus: defineOperation("+"); break;
    case Qt::Key_Minus: defineOperation("-"); break;
    case Qt::Key_Slash: defineOperation("/"); break;
    case Qt::Key_Asterisk: defineOperation("*"); break;
    case Qt::Key_Percent: percentage(); break;
    case Qt::Key_Backspace: deleteNumber(); break;
    case Qt::Key_Comma: case Qt::Key_Period: dot(); break;
    case Qt::Key_Enter: case Qt::Key_Return: equal(); break;
    default:
        break;
    }
}

void MainWindow::dot(){
    isRepeatingEqual = false;
    if(waitSecondNumber){
        ui->display->setText("0.");
        waitSecondNumber = false;
    }
    else if (!ui->display->text().contains(".")){
            ui->display->setText(ui->display->text() + "."
            );
        }
}

void MainWindow::percentage(){
    double percentage = ui->display->text().toDouble();
        double percentageResult = percentage / 100;
        ui->display->setText(
            QString::number(percentageResult)
        );
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

    if (operation.isEmpty())
        return;

    double secondNumber;

    if (isRepeatingEqual){
        firstNumber = ui->display->text().toDouble();
        secondNumber = lastSecondNumber;
    }
    else{
        secondNumber = ui->display->text().toDouble();
        lastSecondNumber = secondNumber;
        isRepeatingEqual = true;
    }

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