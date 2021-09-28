#ifndef NCM_LIVERANKING_H
#define NCM_LIVERANKING_H

#include <QDialog>

using namespace std;

namespace Ui {
class NCM_LiveRanking;
}

class NCM_LiveRanking : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_LiveRanking(QWidget *parent = nullptr);
    ~NCM_LiveRanking();

private:
    Ui::NCM_LiveRanking *ui;
};

#endif // NCM_LIVERANKING_H
