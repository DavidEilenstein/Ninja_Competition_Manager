#ifndef NCM_STAGE_H
#define NCM_STAGE_H

#include <QDialog>
#include <ncm_rankingscheme.h>

using namespace std;

namespace Ui {
class NCM_Stage;
}

class NCM_Stage : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_Stage(QWidget *parent = nullptr);
    ~NCM_Stage();

private slots:
    void on_plainTextEdit_StageCode_textChanged();

private:
    Ui::NCM_Stage *ui;

    bool saved = false;
};

#endif // NCM_STAGE_H
