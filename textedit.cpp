#include "textedit.h"
#include <QDebug>
#include <QApplication>
#include <QTime>

TextEdit::TextEdit(QWidget* parent):
    QTextEdit(parent)
{
    initFormats();
    setReadOnly(true);  // Prevent direct editing
    
    setFont(QFont("Courier", 14));
    QApplication::setCursorFlashTime(0);
}

void TextEdit::updateText(const QString &str)
{
    this->setFocus();
    this->setPlainText(str);
    m_text = str;
    m_index = 0;
    m_wrongChars = 0;
    m_finished = false;
    moveCursor(QTextCursor::Start);
    format(0, str.size()-1, DEF_FORMAT);
}

float TextEdit::calculateWPM(int validChars, int wrongChars, int msecs)
{
    return (validChars - wrongChars) / ((msecs / 1000.f) / 60) / 5.f;
}

void TextEdit::initFormats()
{
    DEF_FORMAT.setForeground(Qt::gray);
    TYPED_FORMAT.setForeground(Qt::white);
    WRONG_FORMAT.setForeground(Qt::red);
}

void TextEdit::format(int start, int end, const QTextCharFormat &_format)
{
    QTextCursor cursor = textCursor();
    cursor.setPosition(start);
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, end - start + 1);
    cursor.mergeCharFormat(_format);
}


void TextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace) {
        if (m_index > 0) {

            if (event->modifiers() & Qt::ControlModifier) // delete entire word
            {
                int first = textCursor().position();
                moveCursor(QTextCursor::StartOfWord);
                int second = textCursor().position();
                m_index -= (first - second);
                format(second, first, DEF_FORMAT);
            }
            else
            {
                m_index--;
                moveCursor(QTextCursor::Left);
                format(m_index, m_index, DEF_FORMAT);
            }
        }
        return;
    }
    else if (event->key() == Qt::Key_Tab)
    {
        // TODO
    }

    if (m_index >= m_text.size())
        return; // Prevent overflow

    QChar typedChar;
    {
        QString text = event->text();
        if (text.isEmpty())
            return;
        typedChar = text.at(0);
    }

    if (m_index == 0)
        m_beginTime = QTime::currentTime();

    QChar correctChar = m_text.at(m_index);

    if (typedChar == correctChar) {
        format(m_index, m_index, TYPED_FORMAT);
    } else {
        format(m_index, m_index, WRONG_FORMAT);
        m_wrongChars++;
    }

    m_index++;
    if (m_index == m_text.size())
    {

        if (!m_finished)
        {
            m_finished = true;
            int msecs = m_beginTime.msecsTo(QTime::currentTime());
            float wpm = calculateWPM(m_text.size() - m_wrongChars, m_wrongChars, msecs);
            emit testFinished(wpm);
        }
    }
    moveCursor(QTextCursor::Right);
}
