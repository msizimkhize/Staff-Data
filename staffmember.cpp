
#include "staffmember.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QString>
#include <QVariant>
#include <QFile>
#include <QTextStream>

#include <QLabel>
#include <QVBoxLayout>


//initialising pointers
StaffMember::StaffMember(QWidget *parent)
    : QWidget{parent},
    edtInput(new QLineEdit),
    edtBirthDate(new QLineEdit),
    staffType(new QComboBox),
    txtDisplay(new QTextEdit),
    btnProcess(new QPushButton("Add To List")),
    btnClose (new QPushButton("Print List")),
    btnSaveFile(new QPushButton("Save As Text"))
{

    //Setup GUI (no ui file)
    setupGUI();
    setWindowTitle("Staff Data ++");
    setMinimumSize(600,300);
    staffType->addItem("Permanent", permanent);
    staffType->addItem("Part-time", parttime);
    staffType->addItem("Contract", contract);
    numContract = 0;
    numPart = 0;
    numPermanent = 0;

    //table HTML open
    QTextStream(&fileStorage) << "<!DOCTYPE html>"
    << "<html>" << "\n" <<
    "<script src="<<'"'<<"https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js" << '"' <<"></script>"<< "\n"
    <<"\n"
    <<"                             <head><link rel="<<'"'<<"icon"<<'"'<<" href="<<'"'<<"icon"<<'"'<<".png"<<'"'<<'>'<<"\n"
    <<"                             <style>"<<"\n"
    <<"                             /* Header/Logo Title */"<<"\n"
    <<"                             .header {"<<"/n"
    <<"    padding-top: 4px;"<<"\n"
    <<"    padding-bottom: 16px;"<<"\n"
    <<"    text-align: center;"<<"\n"
    <<"background: #020231;"<<"\n"
    <<"color: white;"<<"\n"
    <<"padding-right: 10px"<<"\n"
    <<'}'<<"\n"
    <<"\n"
    <<".spacer {"<<"\n"
    <<"    padding-top: 20px;"<<"\n"
    <<"    padding-bottom 20px"<<"\n"
    <<'}'<<"\n"
    <<"\n"
    <<"canvas {"<<"\n"
    <<"    padding-left: 0;"<<"\n"
    <<"    padding-right: 0;"<<"\n"
    <<"    margin-left: auto;"<<"\n"
    <<"    margin-right: auto;"<<"\n"
    <<"display: block;"<<"\n"
    <<"width: 100%;"<<"\n"
    <<"    max-width:600px"<<"\n"
    <<'}'<<"\n"
    <<"\n"
    <<"table {    border-collapse: collapse;    width: 100%;}"<<"\n"
    <<"th, td {    text-align: left;    padding: 8px;}"<<"\n"
    <<"tr:nth-child(even){background-color: #f2f2f2}"<<"\n"
    <<"    th {    background-color: #08084e;    color: white;}"<<"\n"
    <<".mainfont {	font-family: Arial, Helvetica, sans-serif;} .bodytext (	font-family: Arial, Helvetica, sans-serif)</style></head><body>"<<"\n"
    <<"    <div class="<<'"'<<"header"<<'"'<<'>'<<"<br>"<<"\n"
    <<"    <h2 class="<<'"'<<"mainfont"<<'"'<<"><img style="<<'"'<<"display:  inline; margin: 0 10px;"<<'"'<<"src="<<'"'<<"icon.png"<<'"'<<" alt="<<'"'<<'"'<<" width="<<'"'<<"20"<<'"'<<" height="<<'"'<<"20"<<'"'<<"/>Data on Staff Members</h2>"<<"\n"
    <<"    </div>"<<"\n"
    <<"\n"
    <<"    <div  class="<<'"'<<"spacer"<<'"'<<"></div>"<<"\n"
    <<"\n"
    <<"    <canvas id="<<'"'<<"myChart"<<'"'<<"></canvas><br><br>"<<'"'<<"\n"
                              <<"    <table class="<<'"'<<"mainfont"<<'"'<<'>'<<"\n"
                              <<"    <tr><th>Name</th><th>Date of Birth</th><th>Employment Type</th></tr>"<<"\n";

}

void StaffMember::processInput(){

    QString chcStaffType;
    if (this->StaffMember::getStaffAppoinmtentType() == permanent){
        chcStaffType = StaffMember::getStaffAppoinmtentTypeName();
        numPermanent++;
    }
    else if (this->StaffMember::getStaffAppoinmtentType() == parttime){
        chcStaffType = StaffMember::getStaffAppoinmtentTypeName();
        numPart++;
    }
    else if (this->StaffMember::getStaffAppoinmtentType() == contract){
        chcStaffType = StaffMember::getStaffAppoinmtentTypeName();
        numContract++;
    }

    txtDisplay->append(getName() + "; " + getBirthDate() + "; " + chcStaffType);
    QTextStream(&tempStorage) << edtInput->text() + "; " + edtBirthDate->text() + "; " + chcStaffType << "\n";
    QTextStream(&fileStorage) << "<td>" << edtInput->text() << "</td><td>" << edtBirthDate->text() << "</td><td>" << chcStaffType << "</td></tr>";

    edtInput->clear();
    edtInput->setFocus();

    edtBirthDate->clear();
}

void StaffMember::setupGUI(){

    //initialising *layout through the constructor is efficient
    QVBoxLayout *layout(new QVBoxLayout(this));
    QLabel *lblInput(new QLabel("Staff Member Name"));
    QLabel *lblDateOfBirth(new QLabel("Staff Member Date of Birth"));
    QLabel *lblStaffType(new QLabel("Staff Type"));
    QLabel *lblDisplay(new QLabel("Staff Member List"));


    //adds widgets
    layout->addWidget(lblInput);
    layout->addWidget(edtInput);
    layout->addWidget(lblDateOfBirth);
    layout->addWidget(edtBirthDate);
    layout->addWidget(lblStaffType);
    layout->addWidget(staffType);
    layout->addWidget(lblDisplay);
    layout->addWidget(txtDisplay);

    layout->addWidget(btnProcess);
    layout->addWidget(btnClose);
    layout->addWidget(btnSaveFile);

    //connect signals abd slots
    connect(btnProcess, &QPushButton::clicked, this, &StaffMember::processInput);
    connect(btnClose, &QPushButton::clicked, this, &StaffMember::close);
    connect(btnSaveFile, &QPushButton::clicked, this, &StaffMember::fileSave);

    //initialise widgets
    edtInput->setPlaceholderText("First name");//for good look (user convenience)
    edtInput->setToolTip("e.g. Robert");
    edtInput->setMaxLength(30);

    //for good look (user convenience)
    edtBirthDate->setPlaceholderText("DD-MM-YYYY");
    edtBirthDate->setToolTip("Must not be more than 10 characters");
    edtBirthDate->setMaxLength(10);

    //makes layout a child of the widget, and all that is within it
    setLayout(layout);
}

QVariant StaffMember::getStaffAppoinmtentType(){
    QString appointment;
    appointment = QVariant::fromValue(staffType->currentData()).toString();
    return appointment;
}

QString StaffMember::getStaffAppoinmtentTypeName(){
    QString appointment;
    appointment = QVariant::fromValue(staffType->currentText()).toString();
    return appointment;
}

//write text to file
void StaffMember::fileSave(){
    QFile file1("./save.txt");

    file1.open(QIODevice::WriteOnly | QIODevice::Text);

    std::string str = tempStorage.toStdString();
    const char* c = str.c_str();

    file1.write(c);
    file1.close();

}

QString StaffMember::getName() const{
    return edtInput->text();
}

QString StaffMember::getBirthDate() const{
    return edtBirthDate->text();
}

//prints text to html and opens it
void StaffMember::close(){

    QTextStream(&fileStorage)<<"<script>"<<"\n"
    <<"        var xValues = ["<<'"'<<"Permanent"<<'"'<<", "<<'"'<<"Contract"<<'"'<<", "<<'"'<<"Part-time"<<'"'<<"];"<<"\n"
    <<"var yValues = ["<< numPermanent<< ", "<<numContract<<", "<<numPart<<"];"<<"\n"
    <<"var barColors = ["<<"\n"
    <<"    "<<'"'<<"#7575f0"<<'"'<<','<<"\n"
    <<"    "<<'"'<<"#4747eb"<<'"'<<','<<"\n"
    <<"    "<<'"'<<"#0c0c73"<<'"'<<"\n"
    <<"];"<<"\n"
    <<"\n"
    <<"new Chart("<<'"'<<"myChart"<<'"'<<", {"<<"\n"
    <<"    type: "<<'"'<<"doughnut"<<'"'<<','<<"\n"
    <<"    data: {"<<"\n"
    <<"        labels: xValues,"<<"\n"
    <<"        datasets: [{"<<"\n"
    <<"            backgroundColor: barColors,"<<"\n"
    <<"            data: yValues"<<"\n"
    <<"        }]"<<"\n"
    <<"    },"<<"\n"
    <<"    options: {"<<"\n"
    <<"\n"
    <<"    }"<<"\n"
    <<"});"<<"\n"
    <<"</script>"<<"\n"
    <<"    </body></html></table>"<<"\n"
    <<"    <canvas id="<<'"'<<"myChart"<<'"'<<"style="<<'"'<<"width:100%;max-width:600px"<<'"'<<"></canvas>"<<"\n"
    <<"    <script>"
    <<"        var xValues = ["<<'"'<<"Permanent"<<'"'<<", "<<'"'<<"Contract"<<'"'<<", "<<'"'<<"Temporary"<<'"'<<"];"<<"\n"
    <<"var yValues = ["<< numPermanent<< ", "<<numContract<<", "<<numPart<<"];"<<"\n"
    <<"var barColors = ["<<"\n"
    <<"    "<<'"'<<"#7575f0"<<'"'<<','<<"\n"
    <<"    "<<'"'<<"#4747eb"<<'"'<<','<<"\n"
    <<"    "<<'"'<<"#0c0c73"<<'"'<<"\n"
    <<"];"<<"\n"
    <<"\n"
    <<"new Chart("<<'"'<<"myChart"<<'"'<<", {"<<"\n"
    <<"    type: "<<'"'<<"doughnut"<<'"'<<','<<"\n"
    <<"    data: {"<<"\n"
    <<"        labels: xValues,"<<"\n"
    <<"        datasets: [{"<<"\n"
    <<"            backgroundColor: barColors,"<<"\n"
    <<"            data: yValues"<<"\n"
    <<"        }]"<<"\n"
    <<"    },"<<"\n"
              <<"    options: {"<<"\n"
    <<"\n"
    <<"    }"<<"\n"
    <<"});"<<"\n";
    QTextStream(&fileStorage) << "</body>";
    QTextStream(&fileStorage) << "</html>";
    QFile file1("./save.html");

    file1.open(QIODevice::WriteOnly | QIODevice::Text);

    std::string str = fileStorage.toStdString();
    const char* c = str.c_str();

    file1.write(c);
    file1.close();
}
