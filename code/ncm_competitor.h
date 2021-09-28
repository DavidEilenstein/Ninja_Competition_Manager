#ifndef NCM_COMPETITOR_H
#define NCM_COMPETITOR_H

#include <QDialog>

using namespace std;

namespace Ui {
class NCM_Competitor;
}

class NCM_Competitor : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_Competitor(QWidget *parent = nullptr);
    ~NCM_Competitor();

private:
    Ui::NCM_Competitor *ui;
};

#endif // NCM_COMPETITOR_H
