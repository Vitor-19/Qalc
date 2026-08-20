#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void calculateKeyboard(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    double firstNumber = 0;
    double lastSecondNumber = 0;
    QString operation;
    bool waitSecondNumber = false;
    bool isRepeatingEqual = false;

    void defineOperation(const QString &op);
    void addNumber(const QString &number);
    void deleteNumber();
    void dot();
    void equal();
};

#endif