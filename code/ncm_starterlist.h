#ifndef NCM_STARTERLIST_H
#define NCM_STARTERLIST_H

#include <QDialog>

using namespace std;

namespace Ui {
class NCM_StarterList;
}

class NCM_StarterList : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_StarterList(QWidget *parent = nullptr);
    ~NCM_StarterList();

private:
    Ui::NCM_StarterList *ui;
};

#endif // NCM_STARTERLIST_H
