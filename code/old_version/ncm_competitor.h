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
    void set_name(QString name) {QS_Name = name;}
    void set_competitor_class(QString competitor_class) {QS_CompClass = competitor_class;}
    void set_starter_number(int number) {starter_number = number;}

    bool save();
    bool load();
    bool load(QString QS_path);

    int number() {return starter_number;}
    QString name() {return QS_Name;}
    QString competitor_class() {return QS_CompClass;}
    QDir competitor_dir() {return DIR_Competitors;}
signals:

protected:

    QDir DIR_Competitors;

private:

    int starter_number = 0;
    QString QS_Name = "";
    QString QS_CompClass = "";

};

#endif // NCM_COMPETITOR_H
