#ifndef NCM_COMPETITORCLASS_H
#define NCM_COMPETITORCLASS_H

#include <QDialog>

using namespace std;

namespace Ui {
class NCM_CompetitorClass;
}

class NCM_CompetitorClass : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_CompetitorClass(QWidget *parent = nullptr);
    ~NCM_CompetitorClass();

private:
    Ui::NCM_CompetitorClass *ui;
};

#endif // NCM_COMPETITORCLASS_H
