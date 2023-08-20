#include "scripteditor.h"
#include "ui_scripteditor.h"

ScriptEditor::ScriptEditor(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ScriptEditor)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

ScriptEditor::~ScriptEditor()
{
    delete ui;


}

void ScriptEditor::on_ScriptEditor_accepted()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/TelemetryData.sqlite");
    if (!db.open()) {
        qDebug() << "Не открылась бд";
        return;
    }
    QSqlQuery query(db);
    query.prepare("SELECT dataScriptColor "
                  " FROM "
                  " telemetryValues "
                  " WHERE "
                  "id = :id"
                  " AND "
                  " dataValue = :dataValue"
                  ";");
    query.bindValue(":id", currentId);
    query.bindValue(":dataValue", currentValue);
    query.exec();
    while (query.next()) {
        auto queryValue = query.value(0);

        if (queryValue != "") {
            QColor butColor(queryValue.toString());
            currentColor = butColor;
            int blackness = butColor.black();
            if (blackness >= 50) {
                ui->colorPickerButton->setStyleSheet("background-color: " + butColor.name() + ";"
                                                                                              "color: white");
            } else {
                ui->colorPickerButton->setStyleSheet("background-color: " + butColor.name() + ";"
                                                                                              "color: black");
            }
        }
    }
    query.prepare("SELECT dataScriptValue "
                  " FROM "
                  " telemetryValues "
                  " WHERE "
                  "id = :id"
                  " AND "
                  " dataValue = :dataValue"
                  ";");
    query.bindValue(":id", currentId);
    query.bindValue(":dataValue", currentValue);
    query.exec();
    while (query.next()) {
        auto queryValue = query.value(0);
        if (queryValue.isValid())
            ui->scriptField->document()->setPlainText(queryValue.toString());
    }
}

void ScriptEditor::on_colorPickerButton_clicked()
{
    currentColor = QColorDialog::getColor();
    int blackness = currentColor.black();
    if (blackness >= 50) {
        ui->colorPickerButton->setStyleSheet("background-color: " + currentColor.name() + ";"
                                                                                          "color: white");
    } else {
        ui->colorPickerButton->setStyleSheet("background-color: " + currentColor.name() + ";"
                                                                                          "color: black");
    }
}

void ScriptEditor::on_saveScriptButton_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/TelemetryData.sqlite");
    if (!db.open()) {
        qDebug() << "Не открылась бд";
        return;
    }
    QSqlQuery query(db);
    query.prepare("UPDATE telemetryValues SET "
                  "dataScriptValue = :dataScriptValue"
                  ","
                  " dataScriptColor = :dataScriptColor"
                  " WHERE "
                  "id = :id"
                  " AND "
                  " dataValue = :dataValue"

                  ";");
    QString text = ui->scriptField->document()->toPlainText();
    QString color = currentColor.name();
    query.bindValue(":dataScriptValue", text);
    query.bindValue(":dataScriptColor", QVariant(color));
    query.bindValue(":id", currentId);
    query.bindValue(":dataValue", currentValue);
    bool queryResult = query.exec();
    if (queryResult == true) {
        QMessageBox* box;
        box->about(this, "Успешное изменение скрипта", "Скрипт для визуализации был успешно обновлён");
    } else {
        QMessageBox* box;
        box->about(this, "Ошибка", "Произошла непредвиденная ошибка. Скрипт не изменился");
    }
    db.close();
    emit requestUpdate();
}

void ScriptEditor::on_deleteScriptButton_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/TelemetryData.sqlite");
    if (!db.open()) {
        qDebug() << "Не открылась бд";
        return;
    }
    QSqlQuery query(db);
    query.prepare("UPDATE telemetryValues SET "
                  "dataScriptValue = :dataScriptValue"
                  ","
                  " dataScriptColor = :dataScriptColor"
                  " WHERE "
                  "id = :id"
                  " AND "
                  " dataValue = :dataValue"

                  ";");

    query.bindValue(":dataScriptValue", QVariant());
    query.bindValue(":dataScriptColor", QVariant());
    query.bindValue(":id", currentId);
    query.bindValue(":dataValue", currentValue);
    bool queryResult = query.exec();
    if (queryResult == true) {
        QMessageBox *box;
        box->about(this, "Успешное изменение скрипта", "Скрипт для визуализации был удалён");
        ui->scriptField->document()->setPlainText("");
        ui->colorPickerButton->setStyleSheet("background-color: #6aa84f;color: white");

    } else {
        QMessageBox *box;
        box->about(this, "Ошибка", "Произошла непредвиденная ошибка. Скрипт не изменился");
    }
    db.close();
    emit requestUpdate();
}


void ScriptEditor::on_guideButton_clicked()
{
    scriptguidewindow *sgw = new scriptguidewindow();
    sgw->exec();
    delete sgw;
}

