#include "exportingasxmldialog.h"
#include "ui_exportingasxmldialog.h"

ExportingAsXmlDialog::ExportingAsXmlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportingAsXmlDialog)
{
    ui->setupUi(this);
}

ExportingAsXmlDialog::~ExportingAsXmlDialog()
{
    delete ui;
}
