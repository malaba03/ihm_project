#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QDialogButtonBox>





class PopUp : public QDialog
{
    Q_OBJECT
public:
    explicit PopUp();
    
    QTextEdit *getTextEdit() const;
    void setTextEdit(QTextEdit *value);

signals:
    void sendNewClassroomName(QString newClassroomName);

    
public slots:
    void accept();



private:

    QTextEdit *textEdit;

    QDialogButtonBox *buttonBox;

    void createMainLayout();
    
};

#endif // POPUP_H
