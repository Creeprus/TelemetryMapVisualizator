#include "scriptguidewindow.h"
#include "ui_scriptguidewindow.h"

scriptguidewindow::scriptguidewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scriptguidewindow)
{
    ui->setupUi(this);
     setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

scriptguidewindow::~scriptguidewindow()
{
    delete ui;
}
