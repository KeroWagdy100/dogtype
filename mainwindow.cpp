#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "textedit.h"
#include <QPushButton>
#include <QTextEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_paragraph.init();

    refreshParagraph();
    connect(ui->refreshButton, &QPushButton::clicked, this, [this](){
        refreshParagraph();
    });
    connect(ui->restartButton, &QPushButton::clicked, this, [this](){
        refreshParagraph();
    });

    connect(ui->punctuation, &QCheckBox::toggled, this, [this](){
        m_paragraph.togglePunctuation();
        refreshParagraph();
        });
    connect(ui->numbers, &QCheckBox::toggled, this, [this](){
        m_paragraph.toggleNumbers();
        refreshParagraph();
    });

    connect(ui->n10, &QRadioButton::clicked, this, [this](){refreshParagraph(10);});
    connect(ui->n25, &QRadioButton::clicked, this, [this](){refreshParagraph(25);});
    connect(ui->n50, &QRadioButton::clicked, this, [this](){refreshParagraph(50);});
    connect(ui->n100, &QRadioButton::clicked, this, [this](){refreshParagraph(100);});
    connect(ui->n200, &QRadioButton::clicked, this, [this](){refreshParagraph(200);});
    connect(ui->n250, &QRadioButton::clicked, this, [this](){refreshParagraph(250);});

    connect(ui->paragraphText, &TextEdit::testFinished, this, &MainWindow::showResults);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshParagraph()
{
    m_paragraph.generate();
    ui->paragraphText->updateText(m_paragraph.Data());
    
    ui->wpmNumber->setVisible(false);
    ui->wpmLabel->setVisible(false);
}

void MainWindow::refreshParagraph(quint16 n_words)
{
    m_paragraph.generate(n_words);
    ui->paragraphText->updateText(m_paragraph.Data());

    ui->wpmNumber->setVisible(false);
    ui->wpmLabel->setVisible(false);
}

void MainWindow::showResults(float wpm)
{
    ui->wpmNumber->setVisible(true);
    ui->wpmLabel->setVisible(true);
    ui->wpmNumber->display(wpm);
}
