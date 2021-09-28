#ifndef NCM_RUN_H
#define NCM_RUN_H

#include <QDialog>

using namespace std;

namespace Ui {
class NCM_Run;
}

class NCM_Run : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_Run(QWidget *parent = nullptr);
    ~NCM_Run();

private:
    Ui::NCM_Run *ui;
};

#endif // NCM_RUN_H
