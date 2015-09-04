#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <stdio.h>
#include "Guessnumber.h"
#include "QPainter"
#include "QMessageBox"



int userEnteredNumberArray[5];
int userEnteredNumber;
int randomGeneratedNumber;

int currentGuessIndex = 1;

int full_hit[5];
int half_hit[5];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    for(int i=1;i<10;i++)
    {
        ui->comboBox_1->addItem(QString::number(i));
    }
    for(int i=1;i<10;i++)
    {
        ui->comboBox_2->addItem(QString::number(i));
    }
    for(int i=1;i<10;i++)
    {
        ui->comboBox_3->addItem(QString::number(i));
    }
    for(int i=1;i<10;i++)
    {
        ui->comboBox_4->addItem(QString::number(i));
    }
    for(int i=1;i<10;i++)
    {
        ui->comboBox_5->addItem(QString::number(i));
    }
    generateRandomNumber();
    ui->label_random_generated_number->setVisible(false);
    initUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int pow_int(int a,int b)
{
    int result=a;
    if (b == 0)
        return 1;

    for(int i=0;i<b-1;i++)
    {
        result*=a;
    }
    return result;
}


void MainWindow::checkNumber()
{

    int random_number_array[5];

    int temp_random_generated_number;

    temp_random_generated_number = randomGeneratedNumber;


    //blablabla
    for(int i=4;i>=0;i--)
    {
        random_number_array[i] = (temp_random_generated_number / pow_int(10,i));
        temp_random_generated_number=temp_random_generated_number%(pow_int(10,(i)));
    }



    for(int i=0;i<5;i++)
       fprintf(stderr,"random_number_array[%d]:%d\n",i,random_number_array[i]);



    for(int i=0;i<5;i++)
        full_hit[i]=0;

    for(int i=0;i<5;i++)
        half_hit[i]=0;

    // full hit
    for(int i=4;i>-1;i--)
    {
        if (random_number_array[i] == userEnteredNumberArray[i])
        {
            qDebug() << i << ". full hit\n";
            full_hit[i] = 1;
        }
    }

    for(int i=0;i<5;i++)
       fprintf(stderr,"full_hit[%d]:%d\n",i,full_hit[i]);


    // half hit
    for(int i=4;i>-1;i--)
    {
        if (full_hit[i])
            continue;
        for(int j=4;j>-1;j--)
        {
            if (full_hit[j])
                continue;
            if (half_hit[j])
                continue;
            if (userEnteredNumberArray[i] == random_number_array[j])
            {
                half_hit[j] = 1;
                qDebug() << i << ". half hit";
                break;
            }

        }
    }


    drawCircles();

}


// Generate
void MainWindow::on_pushButton_clicked()
{
    generateRandomNumber();

}

// Guess

void MainWindow::on_pushButton_2_clicked()
{


    if (currentGuessIndex==13)
    {
        int ret;
        QMessageBox msgBox;
        QString numberString = QString::number(randomGeneratedNumber);
        msgBox.setText("No more moves! The number was " + numberString);
        ret = msgBox.exec();

        resetGame();
        return;

    }


    userEnteredNumberArray[4] = ui->comboBox_1->currentIndex() + 1;
    userEnteredNumberArray[3] = ui->comboBox_2->currentIndex() + 1;
    userEnteredNumberArray[2] = ui->comboBox_3->currentIndex() + 1;
    userEnteredNumberArray[1] = ui->comboBox_4->currentIndex() + 1;
    userEnteredNumberArray[0] = ui->comboBox_5->currentIndex() + 1;

    for(int i=4;i>-1;i--)
       fprintf(stderr,"userEnteredNumber[%d]:%d\n",i,userEnteredNumberArray[i]);

    userEnteredNumber = 0;
    for(int i=0;i<5;i++)
    {
        userEnteredNumber += userEnteredNumberArray[i]*pow_int(10,i);
    }

    checkNumber();
    currentGuessIndex++;
}

void MainWindow::drawCircles()
{
    // Generate and fill circles according to result
    QString label_name = "label_";
    QString graphicsViewName = "graphicsView_";

    QBrush greenBrush(Qt::green);
    QPen greenOutline(Qt::green);
    QBrush yellowBrush(Qt::yellow);
    QPen yellowOutline(Qt::yellow);
    QBrush whiteBrush(Qt::white);
    QPen whiteOutline(Qt::white);

    greenOutline.setWidth(2);
    yellowOutline.setWidth(2);
    whiteOutline.setWidth(2);

    label_name = "label_";
    label_name.append(QString::number(currentGuessIndex));
    graphicsViewName = "graphicsView_";
    graphicsViewName.append(QString::number(currentGuessIndex));

    scene = new QGraphicsScene(this);
    ui->centralWidget->findChild<QGraphicsView*>(graphicsViewName)->setScene(scene);

    ui->centralWidget->findChild<QLabel*>(label_name)->setVisible(true);
    QString userEnteredNumberString = QString::number(userEnteredNumber);
    QChar space = QChar(QChar::Separator_Space);
    for(int i=1;i<5;i++)
        userEnteredNumberString.insert(i*2-1,space);
    ui->centralWidget->findChild<QLabel*>(label_name)->setText(userEnteredNumberString);


    // draw all white
    for(int i=4;i>-1;i--)
    {
        scene->addEllipse((4-i)*20, 0, 10, 10,whiteOutline, whiteBrush);
    }

    // draw full hits
    for(int i=4;i>-1;i--)
    {
        if (full_hit[i])
        {
            scene->addEllipse((4-i)*20, 0, 10, 10,greenOutline, greenBrush);
        }

    }
    // draw half hits
    // how many half hits?
    int halfHitCount = 0;

    for(int i=0;i<5;i++)
    {
        if (half_hit[i])
            halfHitCount++;
    }
    for(int i=4;i>-1;i--)
    {
        if (full_hit[i])
            continue;
        if (halfHitCount>0)
        {
            scene->addEllipse((4-i)*20, 0, 10, 10,yellowOutline, yellowBrush);
            halfHitCount--;
        }
    }

    ui->centralWidget->findChild<QGraphicsView*>(graphicsViewName)->setVisible(true);
}

// Reveal button
void MainWindow::on_pushButton_3_clicked()
{
    if (ui->label_random_generated_number->isVisible())
    {
        // ui->label_random_generated_number->setVisible(false);
        ui->label_random_generated_number->setVisible(false);
    }

    else
        ui->label_random_generated_number->setVisible(true);
}

void MainWindow::initUi()
{
#define ANSWER_COUNT 12
    QString label_name = "label_";
    QString graphicsViewName = "graphicsView_";

    for(int i = 1; i<ANSWER_COUNT+1;i++)
    {
        label_name = "label_";
        label_name.append(QString::number(i));
        ui->centralWidget->findChild<QLabel*>(label_name)->setVisible(false);
        graphicsViewName = "graphicsView_";
        graphicsViewName.append(QString::number(i));
        ui->centralWidget->findChild<QGraphicsView*>(graphicsViewName)->setStyleSheet("background-color: gray");
        ui->centralWidget->findChild<QGraphicsView*>(graphicsViewName)->setVisible(false);
    }
}

void MainWindow::resetGame()
{
#define ANSWER_COUNT 12
    QString label_name = "label_";
    QString graphicsViewName = "graphicsView_";

    currentGuessIndex = 1;
    userEnteredNumber = 0;
    generateRandomNumber();

    for(int i = 1; i<ANSWER_COUNT+1;i++)
    {
        label_name = "label_";
        label_name.append(QString::number(i));
        ui->centralWidget->findChild<QLabel*>(label_name)->setVisible(false);
        graphicsViewName = "graphicsView_";
        graphicsViewName.append(QString::number(i));
        ui->centralWidget->findChild<QGraphicsView*>(graphicsViewName)->setStyleSheet("background-color: gray");
        ui->centralWidget->findChild<QGraphicsView*>(graphicsViewName)->setVisible(false);
    }
    ui->label_random_generated_number->setVisible(false);
}

// Reset
void MainWindow::on_pushButton_4_clicked()
{
    resetGame();
}


void MainWindow::generateRandomNumber()
{
    GuessNumber g;
    randomGeneratedNumber = g.getRandomNumberToGuess();
    // qDebug() << "user entered number int format: " << userEnteredNumber << "\n" ;
    ui->label_random_generated_number->setText(QString::number(randomGeneratedNumber));
}
