#ifndef NCM_COMPETITOR_H
#define NCM_COMPETITOR_H

#include <QObject>
#include <QDir>
#include <fstream>

using namespace std;

class NCM_Competitor : public QObject
{
    Q_OBJECT
public:
    explicit NCM_Competitor(QDir competitors_dir, QObject *parent = nullptr);
    NCM_Competitor(QDir competitors_dir, QString name, QString competitor_class, int number);

    void set_data(QDir competitors_dir, QString name, QString competitor_class, int number);

    bool save();
    bool load();
    bool load(QString QS_path);

    int number() {return starter_number;}
    QString name() {return QS_Name;}
    QString competitor_class() {return QS_CompClass;}
signals:

private:

    QDir DIR_Competitors;
    int starter_number = 0;
    QString QS_Name = "";
    QString QS_CompClass = "";

};

#endif // NCM_COMPETITOR_H
