#ifndef ROWDATA_H
#define ROWDATA_H

#include "QDate"

class RowData
{
public:
    explicit RowData(QString&& note, int water, int PDA);

private:
    //QDate m_date;
    QString m_note;

    //double m_inhale;
    int m_water;
    int m_PDA;
    //int m_wokout;

    //bool m_lesson;
};

#endif // ROWDATA_H
