
#include <QApplication>

#include "staffmember.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StaffMember staffmember;
    staffmember.show();

    return a.exec();
}
