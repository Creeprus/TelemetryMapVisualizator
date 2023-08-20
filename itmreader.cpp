#include "itmreader.h"

QVector<TmSignal> DBReader::getSignals()
{
    QVector<TmSignal> res;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/TelemetryData.sqlite");
    if (!db.open()) {
        qDebug() << "Не открылась бд";
        return res;
    }
    QSqlQuery query(db);
    query.exec("SELECT * FROM telemetryValues;");
    while (query.next()) {
        auto queryValue = query.value(0);
        qDebug() << QJsonDocument::fromBinaryData(queryValue.toByteArray());
        res.append({ query.value(0).toInt(),
            QVariant(QJsonDocument::fromBinaryData(query.value(1).toByteArray())),
            query.value(2), query.value(3), query.value(4) });
    }
    db.close();
    return res;
}
QVector<TmSignal> TMMapReader::getSignals()
{
    QJsonDocument doc = readJSON();
    QJsonArray array = doc.array();
    QJsonObject obj;
    QVector<TmSignal> res;
    QVariant objValue;
    QRandomGenerator random;
    for (int i = 0; i < array.size(); i++) {

        obj = array[i].toObject();
        for (int j = 0; j < obj.size(); j++) {
            auto key = obj.keys().at(j);
            auto value = obj.value(key);
            auto valuetype = obj.value("тип");
            if (valuetype == "ЦЕЛОЕ") {
                qint32 a = random.bounded(50);
                objValue = a;
            }
            if (valuetype == "ВЕЩЕСТВЕННОЕ") {
                double a = random.generateDouble();
                objValue = a;
            }
            if (valuetype == "ФОК") {

                objValue = "Флаг";
            }
            if (valuetype == "ВРЕМЯ") {
                qint32 a = random.bounded(0, 999);
                qint32 b = random.bounded(0, 59);
                qint32 c = random.bounded(0, 59);
                qint32 d = random.bounded(0, 23);
                QTime time = QTime(d, c, b, a);
                objValue = time;
            }
            if (key == "id" || key == "id времени") {
                res.append({ value.toVariant().toInt(),
                    QVariant(obj),
                    objValue });
                break;
            }
        }
    }
    return res;
}

QJsonDocument TMMapReader::readJSON()
{
    QString val;
    QFile file;
    QFileDialog dialog;
    dialog.open();
    dialog.hide();
    dialog.close();
    file.setFileName(dialog.getOpenFileName());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    return doc;
}
