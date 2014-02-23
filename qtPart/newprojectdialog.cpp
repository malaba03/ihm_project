#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"


#include <QFileDialog>
#include <QMessageBox>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);

    mapeditorProjectDirName = QString("mapeditorProjects");
    currentUserHomePath = QDir::homePath();

    projectNameLineEdit = (ui->projectNameLineEdit);

    layerFileNameLineEdit = (ui->layerFileLineEdit);

    defautfLocationOfProjectLineEdit = (ui->locationLineEdit);
    defautfLocationOfProjectLineEdit->setText(currentUserHomePath+"/"+mapeditorProjectDirName);

}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

Ui::NewProjectDialog* NewProjectDialog::getUi() const
{
    return ui;
}

void NewProjectDialog::setUi(Ui::NewProjectDialog *value)
{
    ui = value;
}


QLineEdit* NewProjectDialog::getProjectNameLineEdit() const
{
    return projectNameLineEdit;
}

void NewProjectDialog::setProjectNameLineEdit(QLineEdit *value)
{
    projectNameLineEdit = value;
}

QLineEdit* NewProjectDialog::getLayerFileNameLineEdit() const
{
    return layerFileNameLineEdit;
}

void NewProjectDialog::setLayerFileNameLineEdit(QLineEdit *value)
{
    layerFileNameLineEdit = value;
}

QLineEdit* NewProjectDialog::getDefautfLocationOfProjectLineEdit() const
{
    return defautfLocationOfProjectLineEdit;
}

void NewProjectDialog::setDefautfLocationOfProjectLineEdit(QLineEdit *value)
{
    defautfLocationOfProjectLineEdit = value;
}

//Generate with Qt Designer
//Pas de gestion des erreurs pour le moment
void NewProjectDialog::on_browseButton_clicked()
{
    layerFileNameLineEdit->setText(QFileDialog::getOpenFileName(this, tr("Opening a image used as layer)"), currentUserHomePath , tr("Image Files (*.png *.jpg)")));

}


void NewProjectDialog::on_newProjectButton_accepted()
{
    /*if(projectNameLineEdit->text().compare(QString(""))){
    }*/
    QDir home = QDir::home();
    QDir projectDir;
    int result = home.absolutePath().compare(home.path());
    QString layerFilePath = layerFileNameLineEdit->text();
    QString projectName = projectNameLineEdit->text();

    if(result==0){

        home.mkdir("mapeditorProjects");

            //A vérifier maybe
            projectDir = QDir(currentUserHomePath+"/"+mapeditorProjectDirName);

            if(projectDir.mkdir(projectName)){

                QMessageBox msgBox;
                msgBox.setWindowTitle("Creating project result");
                msgBox.setText("The creating of project has succeeded!");
                //msgBox.setInformativeText("We advice you to choose another one and try again.");
                msgBox.setStandardButtons(QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Cancel);
                msgBox.exec();
                ///transfert project name
                ///path of layer file
                projectDir.cd(projectName);
                emit sendCurrentProjectDir(projectDir);
                emit sendLayerFilePath(layerFilePath);


            }else {

                QMessageBox::warning(this, tr("Creating project result"),
                                                tr("The project can't be created, the given project name already exist.\n"
                                                   "Choose another one!"),
                                                QMessageBox::Cancel ,
                                                QMessageBox::Cancel);
            }

    }else {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Creating project result");
        msgBox.setText("There is a problem with your home directory.");
        //msgBox.setInformativeText("We advice you to choose another one and try again.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();

    }



}
