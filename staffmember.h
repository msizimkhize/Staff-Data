
#ifndef STAFFMEMBER_H
#define STAFFMEMBER_H

#include <QWidget>

class QLineEdit;
class QTextEdit;
class QComboBox;
class QPushButton;
class QString;
class QVariant;
class QFile;


class StaffMember : public QWidget
{
    Q_OBJECT
public:
    explicit StaffMember(QWidget *parent = nullptr);
    enum  staffAppointmentType{
        permanent,
        parttime,
        contract
    };



private slots:
    void processInput();
    void fileSave();
    void close();


private:
    //we make our getters private
    QVariant getStaffAppoinmtentType();
    QString getStaffAppoinmtentTypeName();

    //more getters
    QString getName() const;
    QString getBirthDate() const;

    void setupGUI();
    QLineEdit *edtInput;//input part
    QLineEdit *edtBirthDate;
    QComboBox *staffType;

    QTextEdit *txtDisplay;//displayed part
    QPushButton *btnProcess;
    QPushButton *btnClose;
    QPushButton *btnSaveFile;

    QString tempStorage;
    QString fileStorage;

    int numPart;
    int numContract;
    int numPermanent;

};


#endif // STAFFMEMBER_H
