#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <dialog_results.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    int answers[5];
//    QString name, str, d_str;

private slots:
    void on_pushButton_Start_clicked(); // нажата главная кнопка

    void timer_tick(void); // обработчик таймера

    void on_pushButton_End_clicked();

    void on_pushButton_Answer_clicked();

    void on_radioButton_Q1_clicked();

    void on_radioButton_Q2_clicked();

    void on_radioButton_Q3_clicked();

    void on_radioButton_Q4_clicked();

    void on_radioButton_Q5_clicked();

    void on_pushButton_Name_clicked();

    void on_lineEdit_textChanged();

private:
    Ui::MainWindow *ui;

    QTimer * timer; // указатель на таймер
    QString name, str, d_str;
    int counter, down_counter, time, score;
    int answers[5][2];
};
#endif // MAINWINDOW_H
