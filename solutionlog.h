#ifndef SOLUTIONLOG_H
#define SOLUTIONLOG_H

#include <QDialog>
#include "Matrix.h"
namespace Ui {
class SolutionLog;
}

class SolutionLog : public QDialog
{
    Q_OBJECT

public:
    void setTableLog(Matrix Log);
    explicit SolutionLog(QWidget *parent = nullptr);
    ~SolutionLog();

private:
    Ui::SolutionLog *ui;
};

#endif // SOLUTIONLOG_H
