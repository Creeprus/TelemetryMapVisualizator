#include "shieldeg.h"

Shieldeg::Shieldeg(QWidget* parent, QString signalName, int signalId, QColor color, QVariant signalValue, QVariant script)
    : QWidget(parent)
{
    this->setAutoFillBackground(true);
    int blackness = color.black();
    QString colorBlackness;
    if (blackness > 50) {
        colorBlackness = "white";
    } else {
        colorBlackness = "black";
    }
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("Shieldeg {"
                        "border: 5 solid #556052;"
                        "background-color: "
        + QString(color.toRgb().name()) + ";"
                                          "border-radius: 4px;"
                                          "}"
                                          "QLabel {"
                                          "border: 1 solid #556052;"

                                          "color :"
        + colorBlackness + ";"
                           ""
                           "}"
                           "QLavel: font {"
                           "size: 30;"
                           ""
                           ""
                           "}");
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setSizePolicy(policy);
    this->setAcceptDrops(true);
    labelName->setText("id: " + QString::number(signalId) + ": " + signalName);
    shSignalName = signalName;
    shSignalId = signalId;
    shSignalValue = signalValue;
    labelValue->setText("Значение: " + signalValue.toString());
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(labelName);
    this->layout()->addWidget(labelValue);
    contextMenu = new QMenu(this);
    QAction* scriptShower = contextMenu->addAction("Изменить скрипт");
    connect(scriptShower, &QAction::triggered, this, [this, this] { showScriptForm(this); });
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &Shieldeg::customContextMenuRequested, this,
        &Shieldeg::contextMenuExpand);
}
void Shieldeg::showScriptForm(QVariant sigValue)
{
    ScriptEditor* scrWindow = new ScriptEditor();
    scrWindow->currentValue.setValue(sigValue);
    scrWindow->exec();
}
void Shieldeg::showScriptForm(Shieldeg* shield)
{
    qDebug() << shield->shSignalId;
    qDebug() << shield->shSignalValue;
    ScriptEditor* scrWindow = new ScriptEditor();
    connect(scrWindow, &ScriptEditor::requestUpdate, this, &Shieldeg::requestUpdate);
    scrWindow->currentValue = shield->shSignalValue;
    scrWindow->currentId = shield->shSignalId;
    scrWindow->setWindowTitle(shield->labelName->text());
    qDebug() << scrWindow->currentValue;
    qDebug() << scrWindow->currentId;
    scrWindow->accept();
    scrWindow->exec();
    delete scrWindow;
}
void Shieldeg::contextMenuExpand(const QPoint& point)
{
    auto cur = QCursor::pos();
    contextMenu->move(cur);
    contextMenu->show();
}
