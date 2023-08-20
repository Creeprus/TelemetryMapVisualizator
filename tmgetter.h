#pragma once

#include "itmreader.h"
class TmGetter {
public:
    TmGetter(ITmReader* reader)
        : m_reader{ reader }
    {
    }
    ~TmGetter() { delete m_reader; }

    QVector<TmSignal> getTm(void) { return m_reader->getSignals(); }

private:
    ITmReader* m_reader;
};
