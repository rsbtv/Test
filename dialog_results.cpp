#include "dialog_results.h"
#include "ui_dialog_results.h"

Dialog_Results::Dialog_Results(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Results) // конструктор
{
    ui->setupUi(this);
    setWindowTitle("Результат");

    //    score = 0;
    QStringList str_list;
    str_list.append("Результат");
    ui->tableWidget->setHorizontalHeaderLabels(str_list);
    best_results.clear();
    ui->label_bestName->clear();
    ui->label_bestScore->clear();
    ui->label_bestCounter->clear();
}

Dialog_Results::~Dialog_Results() // деструктор
{
    delete ui;
}

void Dialog_Results::setResults(int answers[5][2], QString name, QString str, QString d_str, int counter) // функция установки результатов в таблицу
{
    int score = 0;
    for (int i = 0; i < 5; i++)
    {
        if (ui->tableWidget->item(i, 0) == nullptr) // проверка сущ-я ячейки
        {
            QTableWidgetItem * ti = new QTableWidgetItem; // выделение памяти
            //                ti->setFlags(Qt::ItemIsEditable);
            ui->tableWidget->setItem(i, 0, ti); // поместили ячейку в таблицу
        }

        if (answers[i][1] == 0)
        {
            ui->tableWidget->item(i,0)->setText("Не отвечено");
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::gray);
        }

        else if (answers[i][1] == -1)
        {
            ui->tableWidget->item(i,0)->setText("Неверно");
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::red);
        }

        else if (answers[i][1] == 1)
        {
            ui->tableWidget->item(i,0)->setText("Верно");
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::green);
            score++;
        }
    }
    ui->label_Name->setText("Тестируемый: " + name);
    ui->label_Score->setText("Оценка: " + QString::number(score) + "/5");
    ui->label_Passed->setText("Времени прошло:   " + str);
    ui->label_Left->setText("Времени осталось: " + d_str);

    //    QStringList results;
    results.append(name);
    results.append(QString::number(score));
    results.append(QString::number(counter));
    //    checkBest();
    readBest();
    //    setBest();
}

bool Dialog_Results::checkBest()
{

    QString str;
    bool flag;
    str.clear();
    QFile file;
    file.setFileName("C:\\Users\\79021\\Desktop\\test_Sabitov\\best.txt");
    file.open(QIODevice::ReadOnly);

    if (file.size() != 0)
    {
        QByteArray ba;

        ba = file.readLine(0);
        str.append(ba);
        str.remove("\r\n");
        ba.clear();
        if (str.length() < 3)
            return false;
        else
        {
            str.clear();
            ba = file.readLine(2);
            str.append(ba);
            str.remove("\r\n");
            ba.clear();
            if (!str.toInt(&flag))
                return false;
            else
            {
                int score = str.toInt();
                if (score > 5 or score < 0)
                    return false;
                else
                {
                    str.clear();
                    for (int i = 6; i < 8; i++)
                    {
                        ba = file.readLine(i);
                        str.append(ba);
                        str.remove("\r\n");
                    }
                    if (!str.toInt(&flag))
                        return false;
                    else
                    {
                        int counter = str.toInt();
                        if (counter > 6000 or counter <= 0)
                            return false;
                        else
                            return true;
                    }
                }
            }
        }
        file.close();
    }
    else
        return true;
}

void Dialog_Results::readBest()
{
    if (checkBest())
    {
        QString str;
        str.clear();

        QFile file;
        file.setFileName("C:\\Users\\79021\\Desktop\\test_Sabitov\\best.txt");
        file.open(QIODevice::ReadOnly);
        if (file.size() != 0)
        {
            QByteArray ba;

            ba = file.readLine(0);
            str.append(ba);
            str.remove("\r\n");
            best_results.append(str);
            //        ui->label->setText(str);
            str.clear();
            ba.clear();

            ba = file.readLine(2);
            str.append(ba);
            str.remove("\r\n");
            best_results.append(str);
            //        ui->label_2->setText(str);
            str.clear();
            ba.clear();

            for (int i = 6; i < 8; i++)
            {
                ba = file.readLine(i);
                str.append(ba);
                str.remove("\r\n");
            }
            best_results.append(str);
            //        ui->label_3->setText(str);
            str.clear();
            ba.clear();
        }
        file.close();
        setBest();
    }
    else
    {
        QMessageBox::information(this, "Не удалось прочитать файл", "Неверный формата файла", QMessageBox::Ok);
        if (results[1] != "0")
        {
            setErrorBest();
            writeBest();
        }
    }
}

void Dialog_Results::setErrorBest()
{
    QString cur_name = results[0];
    int cur_score = results[1].toInt();
    int cur_counter = results[2].toInt();

    QString str;
    int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд


    str.clear();

    s_sec = cur_counter % 100;
    sec = cur_counter/100;
    m = sec/60;
    sec = sec % 60;
    h = m/60;
    m = m % 60;

    if (h < 10)
        str.append("0");
    str.append(QString::number(h));
    str.append(":");

    if (m < 10)
        str.append("0");
    str.append(QString::number(m));
    str.append(":");

    if (sec < 10)
        str.append("0");
    str.append(QString::number(sec));
    str.append(".");

    if (s_sec < 10)
        str.append("0");
    str.append(QString::number(s_sec));

    ui->label_bestName->setText("Тестируемый: " + cur_name);
    ui->label_bestScore->setText("Оценка: " + QString::number(cur_score) + "/5");
    ui->label_bestCounter->setText("Время: " + str);
}

void Dialog_Results::setBest()
{

    QFile file;
    file.setFileName("C:\\Users\\79021\\Desktop\\test_Sabitov\\best.txt");
    file.open(QIODevice::ReadOnly);
    QString cur_name, best_name;
    int cur_score, best_score, cur_counter, best_counter;
    if (file.size() != 0)
    {
        cur_name = results[0];
        best_name = best_results[0];
        cur_score = results[1].toInt();
        best_score = best_results[1].toInt();
        cur_counter = results[2].toInt();
        best_counter = best_results[2].toInt();

        if (cur_score >= best_score)
        {
            if (cur_score == best_score and cur_counter >= best_counter)
            {
                QString str;
                int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд


                str.clear();

                s_sec = best_counter % 100;
                sec = best_counter/100;
                m = sec/60;
                sec = sec % 60;
                h = m/60;
                m = m % 60;

                if (h < 10)
                    str.append("0");
                str.append(QString::number(h));
                str.append(":");

                if (m < 10)
                    str.append("0");
                str.append(QString::number(m));
                str.append(":");

                if (sec < 10)
                    str.append("0");
                str.append(QString::number(sec));
                str.append(".");

                if (s_sec < 10)
                    str.append("0");
                str.append(QString::number(s_sec));

                //                QMessageBox::information(this, "false", "no record", QMessageBox::Ok);
                ui->label_bestName->setText("Тестируемый: " + best_name);
                ui->label_bestScore->setText("Оценка: " + QString::number(best_score) + "/5");
                ui->label_bestCounter->setText("Время: " + str);

                str.clear();
            }
            else if (cur_score == best_score and cur_counter < best_counter)
            {
                QString str;
                int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд


                str.clear();

                s_sec = cur_counter % 100;
                sec = cur_counter/100;
                m = sec/60;
                sec = sec % 60;
                h = m/60;
                m = m % 60;

                if (h < 10)
                    str.append("0");
                str.append(QString::number(h));
                str.append(":");

                if (m < 10)
                    str.append("0");
                str.append(QString::number(m));
                str.append(":");

                if (sec < 10)
                    str.append("0");
                str.append(QString::number(sec));
                str.append(".");

                if (s_sec < 10)
                    str.append("0");
                str.append(QString::number(s_sec));

                QMessageBox::information(this, "Поздравляем!", "Вы поставили новый рекорд!", QMessageBox::Ok);
                ui->label_bestName->setText("Тестируемый: " + cur_name);
                ui->label_bestScore->setText("Оценка: " + QString::number(cur_score) + "/5");
                ui->label_bestCounter->setText("Время: " + str);

                str.clear();



                writeBest();
            }
            else if (cur_score > best_score)
            {
                QString str;
                int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд


                str.clear();

                s_sec = cur_counter % 100;
                sec = cur_counter/100;
                m = sec/60;
                sec = sec % 60;
                h = m/60;
                m = m % 60;

                if (h < 10)
                    str.append("0");
                str.append(QString::number(h));
                str.append(":");

                if (m < 10)
                    str.append("0");
                str.append(QString::number(m));
                str.append(":");

                if (sec < 10)
                    str.append("0");
                str.append(QString::number(sec));
                str.append(".");

                if (s_sec < 10)
                    str.append("0");
                str.append(QString::number(s_sec));

                QMessageBox::information(this, "Поздравляем!", "Вы поставили новый рекорд!", QMessageBox::Ok);
                ui->label_bestName->setText("Тестируемый: " + cur_name);
                ui->label_bestScore->setText("Оценка: " + QString::number(cur_score) + "/5");
                ui->label_bestCounter->setText("Время: " + str);

                str.clear();



                writeBest();
            }
        }
        else if (cur_score < best_score)
        {
            QString str;
            int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд


            str.clear();

            s_sec = best_counter % 100;
            sec = best_counter/100;
            m = sec/60;
            sec = sec % 60;
            h = m/60;
            m = m % 60;

            if (h < 10)
                str.append("0");
            str.append(QString::number(h));
            str.append(":");

            if (m < 10)
                str.append("0");
            str.append(QString::number(m));
            str.append(":");

            if (sec < 10)
                str.append("0");
            str.append(QString::number(sec));
            str.append(".");

            if (s_sec < 10)
                str.append("0");
            str.append(QString::number(s_sec));

            //            QMessageBox::information(this, "false", "no record", QMessageBox::Ok);
            ui->label_bestName->setText("Тестируемый: " + best_name);
            ui->label_bestScore->setText("Оценка: " + QString::number(best_score) + "/5");
            ui->label_bestCounter->setText("Время: " + str);

            str.clear();
        }
    }
    else
    {
        if (results[1] != "0")
        {
            QString cur_name = results[0];
            int cur_score = results[1].toInt();
            int cur_counter = results[2].toInt();
            QString str;
            int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд


            str.clear();

            s_sec = cur_counter % 100;
            sec = cur_counter/100;
            m = sec/60;
            sec = sec % 60;
            h = m/60;
            m = m % 60;

            if (h < 10)
                str.append("0");
            str.append(QString::number(h));
            str.append(":");

            if (m < 10)
                str.append("0");
            str.append(QString::number(m));
            str.append(":");

            if (sec < 10)
                str.append("0");
            str.append(QString::number(sec));
            str.append(".");

            if (s_sec < 10)
                str.append("0");
            str.append(QString::number(s_sec));

            QMessageBox::information(this, "Поздравляем!", "Вы поставили новый рекорд!", QMessageBox::Ok);
            ui->label_bestName->setText("Тестируемый: " + cur_name);
            ui->label_bestScore->setText("Оценка: " + QString::number(cur_score) + "/5");
            ui->label_bestCounter->setText("Время: " + str);

            writeBest();

            str.clear();
        }
    }
    file.close();

}

void Dialog_Results::writeBest()
{
    if (results[1] != "0")
    {
        QString str;
        str.clear();

        QFile file;
        file.setFileName("C:\\Users\\79021\\Desktop\\test_Sabitov\\best.txt");
        file.open(QIODevice::WriteOnly);

        //    file.resize(0);
        str.append(results[0]);
        str.append("\r\n");

        str.append(results[1]);
        str.append("\r\n");

        str.append(results[2]);

        QByteArray ba;
        ba.append(str);
        file.write(ba);
        file.close();

        results.clear();
        best_results.clear();

        file.close();
    }
}
