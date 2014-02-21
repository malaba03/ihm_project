#include "popup.h"
#include <QHBoxLayout>


PopUp::PopUp() :
    QDialog()
{


        textEdit = new QTextEdit;


        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                              | QDialogButtonBox::Cancel);

         connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
         connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

         createMainLayout();
}

void PopUp::createMainLayout(){

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

}


QTextEdit* PopUp::getTextEdit() const
{
    return textEdit;
}

void PopUp::setTextEdit(QTextEdit *value)
{
    textEdit = value;
}

void PopUp::accept(){

    emit sendNewClassroomName(textEdit->toPlainText());
    QDialog::accept();

}

