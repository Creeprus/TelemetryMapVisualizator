#pragma once

#include <QDialog>

namespace Ui {
class scriptguidewindow;
}

class scriptguidewindow : public QDialog
{
    Q_OBJECT

public:
    explicit scriptguidewindow(QWidget *parent = nullptr);
    ~scriptguidewindow();

private:
    Ui::scriptguidewindow *ui;
};


