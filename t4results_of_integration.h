#ifndef T4results_OF_INTEGRATION_H
#define T4results_OF_INTEGRATION_H

#include <QDialog>

namespace Ui {
   class T4results_of_integration;
}

///////////////////////////////////////////////////////////////
class T4results_of_integration : public QDialog
{
    Q_OBJECT
    
public:
    explicit T4results_of_integration(QWidget *parent = 0);
    ~T4results_of_integration();

    T4results_of_integration(const T4results_of_integration&) = delete;
    T4results_of_integration& operator=(const T4results_of_integration&) = delete;

    void add_results(const char *ss);
    bool multi_line_mode();

private slots:


    void on_button_clear_clicked();

    void on_pushButton_save_to_file_clicked();

private:
    Ui::T4results_of_integration *ui;
};
////////////////////////////////////////////////////////////////
#endif // T4results_OF_INTEGRATION_H
