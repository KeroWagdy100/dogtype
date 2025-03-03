#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "paragraph.h"

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

    void refreshParagraph();
    void refreshParagraph(quint16 n_words);

    void showResults(float wpm);

private:
    Ui::MainWindow *ui;
    Paragraph m_paragraph;
};
#endif // MAINWINDOW_H
