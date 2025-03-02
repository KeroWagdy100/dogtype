#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit();
};

#endif // TEXTEDIT_H
