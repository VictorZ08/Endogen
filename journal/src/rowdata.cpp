#include "rowdata.h"

RowData::RowData(QString&& note, int water, int PDA)
            : m_note{std::move(note)}
            , m_water{water}
            , m_PDA{PDA}
{

}
