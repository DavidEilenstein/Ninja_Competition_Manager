#ifndef NCM_OBJ_COMPETITOR_LIST_H
#define NCM_OBJ_COMPETITOR_LIST_H

//Qt
#include <QObject>
#include <QDir>
#include <QStringList>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QIcon>
#include <QDateEdit>

//c++
#include <vector>
#include <fstream>

//own
#include <NCM_Enum.h>
#include <ncm_obj_competitor.h>

//namespaces
using namespace std;

class NCM_OBJ_Competitor_List
{

public:
    explicit                    NCM_OBJ_Competitor_List();
    explicit                    NCM_OBJ_Competitor_List(QDir dir_saved_in);

    bool                        contains_name(QString name);
    bool                        contains_number(int number);

    bool                        add_competitor(NCM_OBJ_Competitor competitor);
    NCM_OBJ_Competitor          get_competitor(size_t c)                            {return c < size() ? vCompetitors[c] : NCM_OBJ_Competitor();}

    bool                        change_starter_number(NCM_OBJ_Competitor competitor, int new_number);

    QStringList                 names();
    size_t                      size()                                              {return vCompetitors.size();}
    size_t                      count_in_class(bool female);
    void                        clear()                                             {vCompetitors.clear();}

    NCM_OBJ_Competitor_List     subtract(NCM_OBJ_Competitor_List list);

    void                        set_dir(QDir dir)                                   {DIR_SavedIn = dir;}
    bool                        load(QDir dir)                                      {set_dir(dir); return load();}
    bool                        load();
    bool                        save(QDir dir)                                      {set_dir(dir); return save();}
    bool                        save();

private:

    vector<NCM_OBJ_Competitor>  vCompetitors;
    QDir                        DIR_SavedIn;

};

#endif // NCM_OBJ_COMPETITOR_LIST_H
