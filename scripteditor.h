#pragma once

#include "itmreader.h"
#include <QColorDialog>
#include <QDebug>
#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QScriptEngine>
#include <QVariant>
#include "scriptguidewindow.h"
class TMWindow;
namespace Ui {
class ScriptEditor;
}

class ScriptEditor : public QDialog {
    Q_OBJECT

public:
    explicit ScriptEditor(QWidget* parent = 0);
    ~ScriptEditor();
    QVariant currentValue = "";
    QSqlDatabase db;
    int currentId;
    QColor currentColor;
    TMWindow* tmWindow;
public slots:
    void on_ScriptEditor_accepted();
    void on_colorPickerButton_clicked();
    void on_saveScriptButton_clicked();
signals:
    void requestUpdate();

private slots:
    void on_deleteScriptButton_clicked();

    void on_guideButton_clicked();

private:
    Ui::ScriptEditor* ui;
};


