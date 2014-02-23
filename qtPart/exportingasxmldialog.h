#ifndef EXPORTINGASXMLDIALOG_H
#define EXPORTINGASXMLDIALOG_H

#include <QDialog>

namespace Ui {
class ExportingAsXmlDialog;
}

class ExportingAsXmlDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportingAsXmlDialog(QWidget *parent = 0);
    ~ExportingAsXmlDialog();
    
private:
    Ui::ExportingAsXmlDialog *ui;
};

#endif // EXPORTINGASXMLDIALOG_H
