#ifndef CHOOSEACTIONDIALOG_H
#define CHOOSEACTIONDIALOG_H

#include <QDialog>
#include <QLCDNumber>
#include "UAS.h"
#include "QsLog.h"


namespace Ui {
class ChooseActionDialog;
}

class ChooseActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseActionDialog(QWidget *parent = 0, UAS * uas=NULL);
    enum EmergencyReaction { NO_REACTION,INITATE_RTL,LAUNCH_PARACHUTE};
    EmergencyReaction reaction;
    UAS *m_uas;
    ~ChooseActionDialog();

private slots:
    void on_doNothingButton_clicked();

    void on_chuteButton_clicked();

    void on_rtlButton_clicked();

    void on_timer_update(void);

private:
    Ui::ChooseActionDialog *ui;
    QLCDNumber * lcdNumber;
    QTimer *timer;
    int remaining_seconds;
};

#endif // CHOOSEACTIONDIALOG_H
