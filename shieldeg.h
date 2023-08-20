#pragma once

#include "scripteditor.h"
#include <QDebug>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QJsonArray>
#include <QJsonValue>
#include <QLabel>
#include <QMenu>
#include <QMimeData>
#include <QModelIndex>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>

class Shieldeg : public QWidget {
    Q_OBJECT
public:
    explicit Shieldeg(QWidget* parent, QString labelName, int id, QColor color, QVariant signalValue, QVariant script = QVariant());
    QMenu* contextMenu = new QMenu(this);
    void contextMenuExpand(const QPoint& point);

public:
    QLabel* labelName = new QLabel();
    QString shSignalName;
    QLabel* labelValue = new QLabel();
    QVariant shSignalValue;
    QLabel* labelId = new QLabel();
    int shSignalId;
    QVariant shScriptValue;
    void showScriptForm(QVariant sigValue);
    void showScriptForm(Shieldeg* shield);
signals:
    void requestUpdate();
};


