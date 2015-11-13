#ifndef TCALIBRATION_FACTORS_DLG_H
#define TCALIBRATION_FACTORS_DLG_H

#include <QDialog>
#include <vector>

namespace Ui {
class Tcalibration_factors_dlg;
}

class Tcalibration_factors_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit Tcalibration_factors_dlg(QWidget *parent = 0);
    ~Tcalibration_factors_dlg();
    void setup(std::vector<double> fact);
std::vector<double> fact_local;

private slots:

    void on_spinBox_degree_valueChanged(int degree);

    void on_tableWidget_cellChanged(int row, int column);

    void on_buttonBox_accepted();

private:
    Ui::Tcalibration_factors_dlg *ui;



};

#endif // TCALIBRATION_FACTORS_DLG_H
