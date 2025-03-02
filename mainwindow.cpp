#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QTextEdit>
#include <QRadioButton>
#include <QCheckBox>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshParagraph()
{
    m_paragraph.generate();
    ui->paragraphText->setText(m_paragraph.Data());
}

void MainWindow::refreshParagraph(quint16 n_words)
{
    m_paragraph.generate(n_words);
    ui->paragraphText->setText(m_paragraph.Data());
}
