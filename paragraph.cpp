#include "paragraph.h"
#include <QDebug>
#include <QFile> // in read function to open top5000 words csv file
#include <QTextStream> // in read function to read from the file
#include <QRandomGenerator> // in generate function
#include <QCoreApplication>

QStringList Paragraph::wordList;

Paragraph::Paragraph(quint16 numberOfWords, quint16 topNWords)
{
    init(topNWords, numberOfWords);
}

void Paragraph::init(quint16 numberOfWords, quint16 topNWords)
{
    read(topNWords);
    generate(numberOfWords);
}

void Paragraph::read(quint16 topNWords)
{

    if (wordList.size() >= topNWords)
        return;
    wordList.clear();

    QFile file = QFile("words.csv");
    // qDebug() << QCoreApplication::applicationDirPath();
    // qDebug() << QCoreApplication::applicationFilePath();
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        return;
    }
    for (quint16 i = 0; i < topNWords; i++)
        wordList << file.readLine().removeLast().removeLast();
    file.close();
}

void Paragraph::generate()
{
    generate(m_nWords);
}

inline int random(int max)
{
    return QRandomGenerator::global()->bounded(max);
}

inline int random(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max);
}

void Paragraph::generate(quint16 numberOfWords)
{
    quint16 maxWordIndex = wordList.size();
    m_data.clear();
    if (m_nWords != numberOfWords)
        m_nWords = numberOfWords;

    const QList<QChar> special = {'-', ',', '.', '\'', '\"'};
    for (quint16 i = 0; i < m_nWords; ++i)
    {
        auto word = wordList.at( random(maxWordIndex) );

        if (punctuationAllowed())
        {
            if (i == 0 || (i > 0 && m_data.at(m_data.size() - 2) == '.'))
                word[0] = word[0].toUpper();

            // put a random punctuation
            if (random(5) == 0) // 20%
            {
                QChar currSpecial = special.at( random(special.size()) );
                if (currSpecial == '\'' || currSpecial == '\"')
                    word = currSpecial + word + currSpecial;
                else if (currSpecial == '-')
                    word = word + " " + currSpecial;
                else
                    word += currSpecial;
            }
        }

        if (numbersAllowed() && random(10) == 0) // 10%
        {
            quint16 n_digits = random(4) + 1;
            word.clear(); // current word will be digits only
            for (quint16 i = 0; i < n_digits; ++i)
                word += QString::number(random(10));
        }

        

        m_data.append(word + " ");
    }
    m_data.removeLast(); // clears the last " "
}
