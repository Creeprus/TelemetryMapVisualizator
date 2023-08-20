#pragma once

#include "itmreader.h"
#include "shieldeg.h"
#include "tmgetter.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QRandomGenerator>
namespace Ui {
class TMWindow;
}

class TMWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit TMWindow(QWidget* parent = 0);
    ~TMWindow();
    // Все сигналы
    QVector<TmSignal> tm;
public slots:
    void on_pushButton_2_clicked();
    void on_getSignalsButton_clicked();
    void updateShieldegs();

private:
    Ui::TMWindow* ui;
    TmGetter* tm_getter{ nullptr };
    int maxGridSize = 3;
};
