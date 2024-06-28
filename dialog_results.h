#ifndef DIALOG_RESULTS_H
#define DIALOG_RESULTS_H

#include <QDialog>
#include <mainwindow.h>
#include <QStringList>
#include <QColor>
#include <QFileDialog>

// #include <QTextStream>

namespace Ui {
class Dialog_Results;
}

class Dialog_Results : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Results(QWidget *parent = nullptr);
    ~Dialog_Results();

    void setResults(int answers[5][2], QString name, QString str, QString d_str, int counter);

    void readBest();

    bool checkBest();

    void setBest();

    void setErrorBest();

    void writeBest();

private:
    Ui::Dialog_Results *ui;
    int score, best_score, best_counter;
    QString best_name;
    QStringList results, best_results;
};

#endif // DIALOG_RESULTS_H
