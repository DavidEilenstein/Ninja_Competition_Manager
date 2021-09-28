#ifndef NCM_RANKINGSCHEME_H
#define NCM_RANKINGSCHEME_H

#include <QDialog>

using namespace std;

namespace Ui {
class NCM_RankingScheme;
}

class NCM_RankingScheme : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_RankingScheme(QWidget *parent = nullptr);
    ~NCM_RankingScheme();

private:
    Ui::NCM_RankingScheme *ui;
};

#endif // NCM_RANKINGSCHEME_H
