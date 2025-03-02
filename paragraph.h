#ifndef PARAGRAPH_H
#define PARAGRAPH_H
#include <QObject>
#include <QString>
#include <QStringList>


/*
Paragraph class (non-ui-related)
// Data
- WordList: static QStringList that stores Words read from .csv file.
- maxWordRank: qshort represents the number of words read from .csv file.
    - user can choose [Top 250 words - Top 500 words - ..so on]

- data: QString stores current paragraph generated from WordList.
- nWords: qshort stores number of words of current paragraph.

// Functions
- init(maxWordRank, nWords): initializes the Paragraph object
    - Fills WordList by reading #maxWordRank words from .csv file.
    - Generates random data of size nWords.
*/
class Paragraph
{
    // Q_OBJECT
public:
    Paragraph(quint16 numberOfWords = 50U, quint16 topNWords = 250);
    void init(quint16 numberOfWords = 50U, quint16 topNWords = 250U);

    void read(quint16 topNWords);
    void generate();
    void generate(quint16 numberOfWords);
    inline const QString& Data() const {return m_data;}

    inline void toggleNumbers() {
        m_numbers = !m_numbers;
    }
    inline bool numbersAllowed() const { return m_numbers; }

    inline void togglePunctuation() {
        m_punctuation = !m_punctuation;
    }
    inline bool punctuationAllowed() const { return m_punctuation; }
private:

    static QStringList wordList; // top N common english words.

    QString m_data; // current random words put together into one string
    quint16 m_nWords; // number of words in data string
    bool m_numbers = false;
    bool m_punctuation = false;
};

#endif // PARAGRAPH_H
