#include "aviso.h"
#include "ui_aviso.h"

aviso::aviso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aviso)
{
    ui->setupUi(this);
}

aviso::~aviso()
{
    delete ui;
}
