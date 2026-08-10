#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    setWindowFlags(Qt::Window);
    resize(400, 500);

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

    for (QPushButton *button : buttons) {
        connect(button, &QPushButton::clicked, this, [this, button]() {

            QString number = button->text();

            if (waitSecondNumber) {
                ui->display->setText(number);
                waitSecondNumber = false;
            }
            else if (ui->display->text() == "0") {
                ui->display->setText(number);
            }
            else {
                ui->display->setText(
                    ui->display->text() + number
                );
            }
        });
    }

    // =========================
    // Decimal dot
    // =========================

    connect(ui->btnDot, &QPushButton::clicked, this, [this]() {

        if (!ui->display->text().contains(".")) {
            ui->display->setText(
                ui->display->text() + "."
            );
        }
    });

    // =========================
    // Operations
    // =========================

    auto defineOperation = [this](QString op) {

        firstNumber= ui->display->text().toDouble();
        operation = op;
        waitSecondNumber = true;
    };

    connect(ui->btnPlus, &QPushButton::clicked, this, [defineOperation]() {
        defineOperation("+");
    });

    connect(ui->btnMinus, &QPushButton::clicked, this, [defineOperation]() {
        defineOperation("-");
    });

    connect(ui->btnMultiply, &QPushButton::clicked, this, [defineOperation]() {
        defineOperation("*");
    });

    connect(ui->btnDivide, &QPushButton::clicked, this, [defineOperation]() {
        defineOperation("/");
    });
    connect(ui->btnPercentage, &QPushButton::clicked, this, [this]() {
        double percentage = ui->display->text().toDouble();
        double percentageResult = percentage / 100;
        ui->display->setText(
            QString::number(percentageResult)
        );
        
    });

    // =========================
    // Equal
    // =========================

    connect(ui->btnEquals, &QPushButton::clicked, this, [this]() {

        double secondNumber =
            ui->display->text().toDouble();

        double result = 0;

        if (operation == "+") {
            result = firstNumber + secondNumber;
        }
        else if (operation == "-") {
            result = firstNumber - secondNumber;
        }
        else if (operation == "*") {
            result = firstNumber * secondNumber;
        }
        else if (operation == "/") {

            if (secondNumber == 0) {
                ui->display->setText("Error");
                return;
            }

            result = firstNumber / secondNumber;
        }
        ui->display->setText(
            QString::number(result)
        );

        waitSecondNumber = true;
    });


    // =========================
    // Clean
    // =========================

    connect(ui->btnClear, &QPushButton::clicked, this, [this]() {

        ui->display->setText("0");

        firstNumber= 0;
        operation.clear();
        waitSecondNumber = false;
    });

    // =========================
    // Backspace
    // =========================

    connect(ui->btnDel, &QPushButton::clicked, this, [this]() {

        QString text = ui->display->text();

        if (text.length() <= 1) {
            ui->display->setText("0");
        }
        else {
            text.chop(1);
            ui->display->setText(text);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}