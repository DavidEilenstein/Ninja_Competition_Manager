#include "ncm_win_ranking_challenge.h"
#include "ui_ncm_win_ranking_challenge.h"

NCM_WIN_Ranking_Challenge::NCM_WIN_Ranking_Challenge(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Ranking_Challenge)
{
    ui->setupUi(this);
    Table.set_layout(ui->gridLayout_Ranking);

    Competition = comp;
    get_data();

    connect(&TimerAutoupdate, SIGNAL(timeout()), this, SLOT(update()));
    TimerAutoupdate.start(1000);

    setWindowTitle("Ranking Challenge - by David Eilenstein");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));

    int size_button = 80;
    QSize RefIconSize(size_button, size_button);
    ui->pushButton_DE->setIcon(QIcon(":/img/Logo_Final.jpg"));
    ui->pushButton_DE->setIconSize(RefIconSize);
}

NCM_WIN_Ranking_Challenge::~NCM_WIN_Ranking_Challenge()
{
    delete ui;
}

void NCM_WIN_Ranking_Challenge::get_data()
{
    if(data_loaded)
        return;

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   Stage this   XXXXXXXXXXXXXXXXXXXXXX

    //------------------------------- competitors

    QString QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                this,
                "This Stage - Select competitors directory",
                Competition.dir(COMP_DIR_COMPETITORS).path());

    if(QS_CompetitorsLoadPath.isEmpty())
        return;

    QDir DIR_Competitors_StageThis(QS_CompetitorsLoadPath);
    if(!DIR_Competitors_StageThis.exists())
        return;

    Ranking.set_stage_this_competitors(DIR_Competitors_StageThis);

    //------------------------------- stage

    QString QS_StageLoadPath = QFileDialog::getOpenFileName(
                this,
                "This Stage - Select stage file",
                Competition.dir(COMP_DIR_STAGES).path(),
                tr("*.txt *.TXT"));

    if(QS_StageLoadPath.isEmpty())
        return;

    QFileInfo FI_StageFile(QS_StageLoadPath);
    if(!FI_StageFile.exists())
        return;

    if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
        return;

    Ranking.set_stage_this(FI_StageFile);

    //------------------------------- runs

    QDir DIR_Runs(Competition.dir(COMP_DIR_RUNS).path() + "/" + Ranking.ranking_this().stage().name());

    if(!DIR_Runs.exists())
        QDir().mkdir(DIR_Runs.path());
    if(!DIR_Runs.exists())
        return;

    Ranking.set_stage_this_runs(DIR_Runs);

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   Stage previous   XXXXXXXXXXXXXXXXXXXXXX

    if(Ranking.ranking_this().stage().quali_count_previous_f() > 0 || Ranking.ranking_this().stage().quali_count_previous_m() > 0)
    {
        //------------------------------- competitors

        QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                    this,
                    "Previous Stage - Select competitors directory",
                    Competition.dir(COMP_DIR_COMPETITORS).path());

        if(QS_CompetitorsLoadPath.isEmpty())
            return;

        QDir DIR_Competitors_StagePrevious(QS_CompetitorsLoadPath);
        if(!DIR_Competitors_StagePrevious.exists())
            return;

        Ranking.set_stage_previous_competitors(DIR_Competitors_StagePrevious);

        //------------------------------- stage

        QS_StageLoadPath = QFileDialog::getOpenFileName(
                    this,
                    "Previous Stage - Select stage file",
                    Competition.dir(COMP_DIR_STAGES).path(),
                    tr("*.txt *.TXT"));

        if(QS_StageLoadPath.isEmpty())
            return;

        FI_StageFile.setFile(QS_StageLoadPath);
        if(!FI_StageFile.exists())
            return;

        if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
            return;

        Ranking.set_stage_previous(FI_StageFile);

        //------------------------------- runs

        DIR_Runs.setPath(Competition.dir(COMP_DIR_RUNS).path() + "/" + Ranking.ranking_previous().stage().name());

        if(!DIR_Runs.exists())
            QDir().mkdir(DIR_Runs.path());
        if(!DIR_Runs.exists())
            return;

        Ranking.set_stage_previous_runs(DIR_Runs);
    }

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   Challenges   XXXXXXXXXXXXXXXXXXXXXX

    //set path and names
    Ranking.set_challenges_challenges(Competition.dir(COMP_DIR_CHALLENGES));
    Ranking.set_challenges_competitors(DIR_Competitors_StageThis);
    Ranking.set_challenges_tries(Competition.dir(COMP_DIR_CHALLENGE_TRIES));
    Ranking.set_challenges_names();
    Ranking.load_challenges();

    //select challenge
    size_t n_ch = Ranking.rankings_challenges().size();
    if(n_ch > 0)
    {
        QString challenge_select_text = QString::number(n_ch) + " challenges have been found.<br>Please select the challenge to be shown in this ranking:<br>";
        for(size_t ch = 0; ch < n_ch; ch++)
        {
            challenge_select_text.append("<br>" + QString::number(ch) + ": " + Ranking.rankings_challenges().ranking(ch).challenge().name());
        }
        bool ok;
        challenge_index = QInputDialog::getInt(
                    this,
                    "Select Challenge",
                    challenge_select_text,
                    challenge_index,
                    0,
                    n_ch - 1,
                    1,
                    &ok);
        if(!ok)
            return;
    }
    else
    {
        QMessageBox::warning(
                    this,
                    "No Challenges",
                    "No valid challenges wrere found for the selected stage");
        return;
    }

    ui->label_Name->setText(Ranking.rankings_challenges().ranking(challenge_index).challenge().name());

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionget_data->setEnabled(false);
}

void NCM_WIN_Ranking_Challenge::table_dims_dialog()
{
    //wait for update to finish
    ui->actionAutoupdate->setChecked(false);
    while (update_running)
    {
        //just chill
    }

    bool ok;

    int n_tables = QInputDialog::getInt(
                this,
                "Table count",
                "How many ranking tables do you want to have side by side in layout?",
                Table.count_tables(),
                1,
                10,
                1,
                &ok);
    if(!ok)
        return;

    int n_rows = QInputDialog::getInt(
                this,
                "Row count",
                "How many rows shall a table (exept the last one) have at maximum?",
                Table.count_rowsPerTable(),
                1,
                1000,
                1,
                &ok);
    if(!ok)
        return;

    Table.set_table_count(n_tables);
    Table.set_table_rows(n_rows);
}

void NCM_WIN_Ranking_Challenge::update()
{
    if(!data_loaded)
        return;

    if(update_running)
        return;

    update_running = true;

    //update
    Ranking.update();

    //challenge ranking
    NCM_OBJ_Ranking_Challenge ranking_challenge = Ranking.rankings_challenges().ranking(challenge_index);
    QString unit =  " " + ranking_challenge.challenge().unit();

    //--------------------------------------------------------------------------------------- table

    //clear scores
    ui->label_Qualiscore_F->setText("");
    ui->label_Qualiscore_M->setText("");
    ui->label_Highscore_F->setText("");
    ui->label_Highscore_M->setText("");

    //data
    size_t n_cols = COL_NUMBER_OF;
    size_t n_rows = ranking_challenge.challengetrys().size();
    vector<vector<QString>> vvQS_TableContent_c_r(n_cols, vector<QString>(n_rows, "..."));

    //row names
    QStringList QSL_NamesRows;

    //loop tries
    for(size_t r = 0; r < n_rows; r++)
    {
        //try/competitor
        NCM_OBJ_Try challengetry = ranking_challenge.challengetry(r);
        NCM_OBJ_Competitor competitor = challengetry.competitor();

        //row name
        QSL_NamesRows.append(QString::number(ranking_challenge.pos_current_overall(competitor)));

        //competitor info
        vvQS_TableContent_c_r[COL_NAME][r]      = competitor.name();

        //try data
        vvQS_TableContent_c_r[COL_SCORE][r]     = QString::number(challengetry.score()) + unit;

        //position
        size_t pos_current      = ranking_challenge.pos_current_class(competitor);
        QString class_symbol    = competitor.competitor_class_symbol();
        vvQS_TableContent_c_r[COL_POS][r] = class_symbol + " " + QString::number(pos_current) + ".";

        //quali
        size_t quali_state = Ranking.quali_state(competitor);
        vvQS_TableContent_c_r[COL_QUALI][r] = QSL_QualiState[quali_state];

        //run or not
        vvQS_TableContent_c_r[COL_RUN][r] = Ranking.ranking_this().runs().competitors_list().contains_name(competitor.name()) ? QS_SymbolYes : QS_SymbolNo;

        //Highscore/Qualiscore
        if(competitor.female())
        {
            if(pos_current == 1)
            {
                ui->label_Highscore_F->setText(QString::number(challengetry.score()) + unit);
            }

            if(quali_state == QUALI_STATE_QUALI_CHALLENGE)
            {
                if(Ranking.quali_from_challenge_index(competitor) == challenge_index)
                {
                    ui->label_Qualiscore_F->setText(QString::number(challengetry.score()) + unit);
                    vvQS_TableContent_c_r[COL_QUALI][r] = QS_QualiChallengeThis;
                }
            }
        }
        else
        {
            if(pos_current == 1)
            {
                ui->label_Highscore_M->setText(QString::number(challengetry.score()) + unit);
            }

            if(quali_state == QUALI_STATE_QUALI_CHALLENGE)
            {
                if(Ranking.quali_from_challenge_index(competitor) == challenge_index)
                {
                    ui->label_Qualiscore_M->setText(QString::number(challengetry.score()) + unit);
                    vvQS_TableContent_c_r[COL_QUALI][r] = QS_QualiChallengeThis;
                }
            }
        }
    }

    //set table data
    Table.set_data(vvQS_TableContent_c_r, QSL_NamesColumns, QSL_NamesRows, false, true);

    //take screenshot once per minute
    if(ui->actionTake_Screenshot_once_per_minute->isChecked())
        if(QDateTime::currentDateTime().time().second() <= 1)
            this->grab().save(Competition.dir(COMP_DIR_SCREENSHOTS).path() + "/Ranking - " + ranking_challenge.challenge().name() + ".png");

    update_running = false;
}

void NCM_WIN_Ranking_Challenge::update_auto(bool activate)
{
    if(activate)
    {
        bool ok;
        double time_s = QInputDialog::getDouble(
                    this,
                    "Autoupdate interval",
                    "Please select the interval for autoupdateing ranking in seconds.",
                    1,
                    0.1,
                    300,
                    2,
                    &ok);
        if(!ok)
        {
            ui->actionAutoupdate->setChecked(false);
            return;
        }

        TimerAutoupdate.start(int(time_s * 1000));
    }
    else
    {
        TimerAutoupdate.stop();
    }

    ui->actionUpdate->setEnabled(!activate);
}

void NCM_WIN_Ranking_Challenge::on_actionget_data_triggered()
{
    get_data();
}

void NCM_WIN_Ranking_Challenge::on_actionChange_table_settings_triggered()
{
    table_dims_dialog();
}

void NCM_WIN_Ranking_Challenge::on_actionUpdate_triggered()
{
    ui->actionAutoupdate->setChecked(false);
    while (update_running)
    {
        //just chill
    }

    update();
}

void NCM_WIN_Ranking_Challenge::on_actionAutoupdate_triggered(bool checked)
{
    update_auto(checked);
}
