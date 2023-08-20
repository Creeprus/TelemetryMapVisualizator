#include "tmwindow.h"
#include "ui_tmwindow.h"

TMWindow::TMWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::TMWindow)
{
    ui->setupUi(this);
    ui->widgetGridLayout->setHorizontalSpacing(2);
    updateShieldegs();
}

TMWindow::~TMWindow()
{
    if (tm_getter)
        delete tm_getter;
    delete ui;

}

void TMWindow::on_pushButton_2_clicked()
{
  ui->widgetGridLayout->addWidget(new Shieldeg(nullptr, "Пусковое устройство", 23, QColor(255, 255, 255), QVariant()));
}

void TMWindow::on_getSignalsButton_clicked()
{
    updateShieldegs();
}

void TMWindow::updateShieldegs()
{
    tm_getter = new TmGetter(new DBReader);
    QVector<TmSignal> tm = tm_getter->getTm();
    QColor typeColor = QColor(255, 255, 255);
    QRegExp regex("[0-9][0-9]:[0-5][0-9]:[0-5][0-9]:[0-9][0-9][0-9]");
    int i = 0;
    int j = 0;
    QScriptEngine engine;

    for (const auto& sig : tm) {

        QVariant currentValue = sig.valueType;

        QVariant value = sig.value;

        auto jsonobj = currentValue.toJsonObject();
        QString signalName = jsonobj.value("имя").toVariant().toString();
        QString signalType = jsonobj.value("тип").toVariant().toString();
        if (signalType == "МЕТАДАННЫЕ") {
            // Метаданные нельзя визуализировать
            break;
        }

        QJsonValue trueValue = value.toJsonValue();
        bool convertable = true;
        value.toDouble(&convertable);
        if (convertable == true) {
            double past = value.toDouble();
            double future = std::floor(value.toDouble());
            if (past != future) {
                typeColor = QColor(200, 255, 200);
            } else {
                typeColor = QColor(135, 206, 250);
            }
        }

        if (convertable == false) {
            typeColor = QColor(200, 200, 255);
        }

        if (regex.exactMatch(trueValue.toString())) {
            typeColor = QColor(255, 200, 200);
        }

        if (sig.color != "") {
            engine.globalObject().setProperty("value", engine.toScriptValue(value));

            QString redCondition(sig.script.toString());
            auto evalRes = engine.evaluate(redCondition);
            if (evalRes.toBool() == true) {
                typeColor = QColor(sig.color.toString());
            }
        }
        if (signalName != "") {
            if (i < maxGridSize) {
                Shieldeg* shield = new Shieldeg(this, signalName, sig.id, typeColor, value, QVariant());
                connect(shield, &Shieldeg::requestUpdate, this, &TMWindow::updateShieldegs);
                ui->widgetGridLayout->addWidget(shield, i, j);

                i++;
            } else {
                i = 0;
                j++;
                Shieldeg* shield
                    = new Shieldeg(this, signalName, sig.id, typeColor, value, QVariant());
                connect(shield, &Shieldeg::requestUpdate, this, &TMWindow::updateShieldegs);
                ui->widgetGridLayout->addWidget(shield, i, j);
                i++;
            }
        } else {
            if (i < maxGridSize) {
                Shieldeg* shield = new Shieldeg(this,
                    "Устройство с id: " + QString::number(sig.id),
                    sig.id,
                    typeColor,
                    value,
                    QVariant());
                connect(shield, &Shieldeg::requestUpdate, this, &TMWindow::updateShieldegs);
                ui->widgetGridLayout->addWidget(shield, i, j);

                i++;
            } else {
                i = 0;
                j++;
                Shieldeg* shield = new Shieldeg(this,
                    "Устройство с id: " + QString::number(sig.id),
                    sig.id,
                    typeColor,
                    value,
                    QVariant());
                connect(shield, &Shieldeg::requestUpdate, this, &TMWindow::updateShieldegs);
                ui->widgetGridLayout->addWidget(shield, i, j);
                i++;
            }
        }
    }

}
