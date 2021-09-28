#ifndef NCM_COMPETITORLIST_H
#define NCM_COMPETITORLIST_H

#include <QDialog>

using namespace std;

namespace Ui {
class NCM_CompetitorList;
}

class NCM_CompetitorList : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_CompetitorList(QWidget *parent = nullptr);
    ~NCM_CompetitorList();

private:
    Ui::NCM_CompetitorList *ui;
};

#endif // NCM_COMPETITORLIST_H
