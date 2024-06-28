#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // конструктор
{
    ui->setupUi(this);

    timer = new QTimer(this); // создали таймер
    counter = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_tick()));
    time = 6000;

    ui->pushButton_End->hide();
    ui->groupBox->hide();
    ui->groupBox_2->hide();

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 2; j++)
            answers[i][j] = 0;



//    ui->label_Question->setText("1 вопрос");
    ui->lcdNumber_Left->hide();
    ui->lcdNumber_Passed->hide();
    ui->label_Question->hide();
    ui->pushButton_Start->hide();
    on_radioButton_Q1_clicked();
    setWindowTitle("Тест");
}

MainWindow::~MainWindow() // деструктор
{
    delete ui;
}

void MainWindow::timer_tick() // обработчик таймера
{
    counter++;
    down_counter = time - counter;

//    QString str;
//    QString d_str;
    int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд
    int d_h, d_m, d_sec, d_s_sec;

    str.clear();
    d_str.clear();

    s_sec = counter % 100;
    sec = counter/100;
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


    d_s_sec = down_counter % 100;
    d_sec = down_counter/100;
    d_m = d_sec/60;
    d_sec = d_sec % 60;
    d_h = d_m/60;
    d_m = d_m % 60;

    if (d_h < 10)
        d_str.append("0");
    d_str.append(QString::number(d_h));
    d_str.append(":");

    if (d_m < 10)
        d_str.append("0");
    d_str.append(QString::number(d_m));
    d_str.append(":");

    if (d_sec < 10)
        d_str.append("0");
    d_str.append(QString::number(d_sec));
    d_str.append(".");

    if (d_s_sec < 10)
        d_str.append("0");
    d_str.append(QString::number(d_s_sec));

    ui->lcdNumber_Passed->display(str);
    ui->lcdNumber_Left->display(d_str);

    if (counter == time)
    {
        on_pushButton_End_clicked();
    }
}

void MainWindow::on_pushButton_Start_clicked() // нажата кнопка старт
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 2; j++)
            answers[i][j] = 0;
    ui->groupBox->setEnabled(true);
    ui->groupBox_2->setEnabled(true);

    ui->radioButton_A1->setAutoExclusive(false);
    ui->radioButton_A2->setAutoExclusive(false);
    ui->radioButton_A3->setAutoExclusive(false);
    ui->radioButton_A4->setAutoExclusive(false);

    ui->radioButton_A1->setChecked(false);
    ui->radioButton_A2->setChecked(false);
    ui->radioButton_A3->setChecked(false);
    ui->radioButton_A4->setChecked(false);

    ui->radioButton_A1->setAutoExclusive(true);
    ui->radioButton_A2->setAutoExclusive(true);
    ui->radioButton_A3->setAutoExclusive(true);
    ui->radioButton_A4->setAutoExclusive(true);
    counter = 0;
    timer->start(10);
    ui->pushButton_Start->hide();
    ui->pushButton_End->show();
    ui->lcdNumber_Left->show();
    ui->lcdNumber_Passed->show();
    ui->label_Question->show();
    ui->groupBox->show();
    ui->groupBox_2->show();
//    ui->radioButton_Q1->setChecked(true);
    on_radioButton_Q1_clicked();
    ui->pushButton_Answer->show();
}


void MainWindow::on_pushButton_End_clicked() // нажата кнопка закончить
{
//    ui->pushButton_Start->hide();
    timer->stop();
    ui->pushButton_End->hide();
    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
//    ui->groupBox->hide();
//    ui->groupBox_2->hide();
    ui->pushButton_Answer->hide();
    Dialog_Results dial_result;
    dial_result.setResults(answers, name, str, d_str, counter);
    dial_result.setWindowFlags (dial_result.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    dial_result.exec();
    ui->pushButton_Start->show();
}


void MainWindow::on_pushButton_Answer_clicked() // нажата кнопка ответить
{
    if (ui->radioButton_Q1->isChecked())
    {

        if (ui->radioButton_A1->isChecked())
        {
            answers[0][0] = 1;
            answers[0][1] = 1;
        }
        else if (ui->radioButton_A2->isChecked())
        {
            answers[0][0] = 2;
            answers[0][1] = -1;
        }
        else if (ui->radioButton_A3->isChecked())
        {
            answers[0][0] = 3;
            answers[0][1] = -1;
        }
        else if (ui->radioButton_A4->isChecked())
        {
            answers[0][0] = 4;
            answers[0][1] = -1;
        }
        on_radioButton_Q2_clicked();
    }
    else if (ui->radioButton_Q2->isChecked())
    {
        if (ui->radioButton_A1->isChecked())
        {
            answers[1][0] = 1;
            answers[1][1] = -1;
        }
        else if (ui->radioButton_A2->isChecked())
        {
            answers[1][0] = 2;
            answers[1][1] = 1;
        }
        else if (ui->radioButton_A3->isChecked())
        {
            answers[1][0] = 3;
            answers[1][1] = -1;
        }
        else if (ui->radioButton_A4->isChecked())
        {
            answers[1][0] = 4;
            answers[1][1] = -1;
        }
        on_radioButton_Q3_clicked();
    }
    else if (ui->radioButton_Q3->isChecked())
    {
        if (ui->radioButton_A1->isChecked())
        {
            answers[2][0] = 1;
            answers[2][1] = -1;
        }
        else if (ui->radioButton_A2->isChecked())
        {
            answers[2][0] = 2;
            answers[2][1] = -1;
        }
        else if (ui->radioButton_A3->isChecked())
        {
            answers[2][0] = 3;
            answers[2][1] = 1;
        }
        else if (ui->radioButton_A4->isChecked())
        {
            answers[2][0] = 4;
            answers[2][1] = -1;
        }
        on_radioButton_Q4_clicked();
    }
    else if (ui->radioButton_Q4->isChecked())
    {
        if (ui->radioButton_A1->isChecked())
        {
            answers[3][0] = 1;
            answers[3][1] = -1;
        }
        else if (ui->radioButton_A2->isChecked())
        {
            answers[3][0] = 2;
            answers[3][1] = -1;
        }
        else if (ui->radioButton_A3->isChecked())
        {
            answers[3][0] = 3;
            answers[3][1] = -1;
        }
        else if (ui->radioButton_A4->isChecked())
        {
            answers[3][0] = 4;
            answers[3][1] = 1;
        }
        on_radioButton_Q5_clicked();
    }
    else if (ui->radioButton_Q5->isChecked())
    {
        if (ui->radioButton_A1->isChecked())
        {
            answers[4][0] = 1;
            answers[4][1] = 1;
        }
        else if (ui->radioButton_A2->isChecked())
        {
            answers[4][0] = 2;
            answers[4][1] = -1;
        }
        else if (ui->radioButton_A3->isChecked())
        {
            answers[4][0] = 3;
            answers[4][1] = -1;
        }
        else if (ui->radioButton_A4->isChecked())
        {
            answers[4][0] = 4;
            answers[4][1] = -1;
        }
//        on_radioButton_Q1_clicked();
    }

}


void MainWindow::on_radioButton_Q1_clicked() // нажата радиокнопка 1 вопроса
{
    ui->label_Question->setText("Какое произношение Qt правильное?");
    ui->radioButton_A1->setText("Кьют");
    ui->radioButton_A2->setText("Ку-тэ");
    ui->radioButton_A3->setText("Кью-ти");
    ui->radioButton_A4->setText("Кью-тэ");
    ui->radioButton_Q1->setChecked(true);
    if (answers[0][0] == 0)
    {
        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);
    }
    else if (answers[0][0] == 1)
    {
        ui->radioButton_A1->setChecked(true);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);
    }
    else if (answers[0][0] == 2)
    {
        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(true);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);
    }
    else if (answers[0][0] == 3)
    {
        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(true);
        ui->radioButton_A4->setChecked(false);
    }
    else if (answers[0][0] == 4)
    {
        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(true);
    }
}


void MainWindow::on_radioButton_Q2_clicked() // нажата радиокнопка 2 вопроса
{
    ui->label_Question->setText("Выберите правильный список принципов ООП");
    ui->radioButton_A1->setText("Процедурность, полиморфизм, дискретность.");
    ui->radioButton_A2->setText("Наследование, полиморфизм, инкапсуляция.");
    ui->radioButton_A3->setText("Результативность, инкапсуляция, определенность.");
    ui->radioButton_A4->setText("Наследование, формальность, инкапсуляция.");
    ui->radioButton_Q2->setChecked(true);
    if (answers[1][0] == 0)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[1][0] == 1)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(true);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[1][0] == 2)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(true);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[1][0] == 3)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(true);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[1][0] == 4)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(true);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
}


void MainWindow::on_radioButton_Q3_clicked() // нажата радиокнопка 3 вопроса
{
    ui->label_Question->setText("Как зовут человека, «взломавшего» шифратор Enigma?");
    ui->radioButton_A1->setText("Григорий Перельман.");
    ui->radioButton_A2->setText("Билл Гейтс.");
    ui->radioButton_A3->setText("Алан Тьюринг.");
    ui->radioButton_A4->setText("Линус Торвальдс.");
    ui->radioButton_Q3->setChecked(true);
    if (answers[2][0] == 0)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[2][0] == 1)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(true);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[2][0] == 2)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(true);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[2][0] == 3)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(true);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[2][0] == 4)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(true);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
}


void MainWindow::on_radioButton_Q4_clicked() // нажата радиокнопка 4 вопроса
{
    ui->label_Question->setText("Каково происхождение слова «алгоритм»?");
    ui->radioButton_A1->setText("Из древнегреческого языка.");
    ui->radioButton_A2->setText("Было придумано советскими учёными.");
    ui->radioButton_A3->setText("Было придумано американскими учёными.");
    ui->radioButton_A4->setText("От имени персидского учёного.");

    ui->radioButton_Q4->setChecked(true);
    if (answers[3][0] == 0)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[3][0] == 1)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(true);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[3][0] == 2)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(true);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[3][0] == 3)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(true);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[3][0] == 4)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(true);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
}


void MainWindow::on_radioButton_Q5_clicked() // нажата радиокнопка 5 вопроса
{
    ui->label_Question->setText("Программа, выводящая «Hello, World!» на языке Brainfuck.");
    ui->radioButton_A1->setText("+[-->-[>>+>-----<<]<--<---]>-.>>>+.>>..+++[.>]<<<<.+++.------.<<-.>>>>+.");
    ui->radioButton_A2->setText("++<<[---->>+]>>>++.[<-->---+]+.<<+[-->-[>>+>-----<<]<]<<----.<<-.>>>>+.");
    ui->radioButton_A3->setText("+[-->-[>>+>----->+>-----<<+[.>]<>+]>>>++.[<-->---+]+--<<+[.>]<.");
    ui->radioButton_A4->setText("++[.>]<<<<.++>>++.[<-->--+.<<+[-->-[>>+>-----<<]<]<-+]+.<<+++[-->-+.");
    ui->radioButton_Q5->setChecked(true);
    if (answers[4][0] == 0)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[4][0] == 1)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(true);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[4][0] == 2)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(true);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[4][0] == 3)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(true);
        ui->radioButton_A4->setChecked(false);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
    else if (answers[4][0] == 4)
    {
        ui->radioButton_A1->setAutoExclusive(false);
        ui->radioButton_A2->setAutoExclusive(false);
        ui->radioButton_A3->setAutoExclusive(false);
        ui->radioButton_A4->setAutoExclusive(false);

        ui->radioButton_A1->setChecked(false);
        ui->radioButton_A2->setChecked(false);
        ui->radioButton_A3->setChecked(false);
        ui->radioButton_A4->setChecked(true);

        ui->radioButton_A1->setAutoExclusive(true);
        ui->radioButton_A2->setAutoExclusive(true);
        ui->radioButton_A3->setAutoExclusive(true);
        ui->radioButton_A4->setAutoExclusive(true);
    }
}


void MainWindow::on_pushButton_Name_clicked() // нажата кнопка ввести имя
{
    name = ui->lineEdit->text();
    if (!name.isEmpty() and name.size() > 2)
    {
        ui->label_Name->setText("Тестируемый: " + name);
        ui->label_SetName->hide();
        ui->lineEdit->hide();
        ui->pushButton_Name->hide();
        ui->pushButton_Start->show();
    }
    else if (name.size() < 3)
    {
        QMessageBox::information(this,"Ошибка", "Слишком короткое имя.",QMessageBox::Ok);

    }
    else if (name.isEmpty())
    {
        QMessageBox::information(this,"Ошибка", "Введите имя.",QMessageBox::Ok);
    }
}

void MainWindow::on_lineEdit_textChanged() // измененено поле для ввода имени
{
    int length = ui->lineEdit->text().length(); //ввод длины
    QPalette pal = ui->lineEdit->palette(); //ввод палитры
    pal.setColor(ui->label_SetName->foregroundRole(),Qt::black); //красим лейбл в черный изначально

    if ((length < 3) || (length > 20)) //длина имени от 3 до 20
    {
        pal.setColor(ui->label_SetName->foregroundRole(),Qt::red); //окраска в красный при неправильном значении
        pal.setColor(ui->lineEdit->foregroundRole(),Qt::red);//окраска в красный при неправильном значении
    }
    else
    {
        pal.setColor(ui->label_SetName->foregroundRole(),Qt::black); //окраска лейбла в зеленый при правильном
        pal.setColor(ui->lineEdit->foregroundRole(),Qt::black); //окраска эдита в зеленый при правильном
    }
    ui->lineEdit->setPalette(pal); //установка палитры
    ui->label_SetName->setPalette(pal); //установка палитры
}

