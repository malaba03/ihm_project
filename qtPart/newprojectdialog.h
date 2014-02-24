#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT    
    
public:
    explicit NewProjectDialog(QWidget *parent = 0);
    ~NewProjectDialog();    

    Ui::NewProjectDialog *getUi() const;
    void setUi(Ui::NewProjectDialog *value);


    QLineEdit *getProjectNameLineEdit() const;
    void setProjectNameLineEdit(QLineEdit *value);

    QLineEdit *getLayerFileNameLineEdit() const;
    void setLayerFileNameLineEdit(QLineEdit *value);

    QLineEdit *getDefautfLocationOfProjectLineEdit() const;
    void setDefautfLocationOfProjectLineEdit(QLineEdit *value);

private:
    Ui::NewProjectDialog *ui;

    QLineEdit *projectNameLineEdit;
    QLineEdit *layerFileNameLineEdit;
    QLineEdit *defautfLocationOfProjectLineEdit;
    QString currentUserHomePath;
    QString mapeditorProjectDirName;
    QString projectName;


signals:
    void sendCurrentProjectDir(QDir,QString);
    void sendLayerFilePath(QString);

private slots:
    void on_browseButton_clicked();
    void on_newProjectButton_accepted();
};

#endif // NEWPROJECTDIALOG_H
