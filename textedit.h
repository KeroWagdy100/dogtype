#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <QKeyEvent>
#include <QTextCharFormat>
#include <QTime>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit(QWidget* parent = nullptr);
    void updateText(const QString& str);

    static float calculateWPM(int validChars, int wrongChars, int msecs);

signals:
    void testFinished(float wpm);

private:
    int m_index = 0;
    int m_wrongChars = 0;
    QString m_text;
    QTime m_beginTime;
    bool m_finished = false;

    /* FORMATS */
    QTextCharFormat DEF_FORMAT;
    QTextCharFormat TYPED_FORMAT;
    QTextCharFormat WRONG_FORMAT;
    void initFormats();
    void format(int start, int end, const QTextCharFormat& _format);
    /* ------ */

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // TEXTEDIT_H
