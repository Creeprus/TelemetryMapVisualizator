#pragma once

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QRegExp>
#include <QScriptEngine>
#include <QSqlQuery>
#include <QTime>
#include <QVariant>
#include <QVector>
#include <QtSql/QSqlDatabase>
struct TmSignal {
    int id;
    QVariant valueType;
    QVariant value;
    QVariant script;
    QVariant color;
};

class ITmReader {
public:

    virtual QVector<TmSignal> getSignals(void) = 0;
    virtual ~ITmReader() {}
};
class DBReader : public ITmReader {
public:
    virtual QVector<TmSignal> getSignals(void) override;
    QSqlDatabase db;
    virtual ~DBReader() {}
};
class TMMapReader : public ITmReader {
public:
    virtual QVector<TmSignal> getSignals(void) override;
    virtual ~TMMapReader() {}
    QJsonDocument readJSON();
};
