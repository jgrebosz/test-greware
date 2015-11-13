#ifndef T4USER_SPECTRUM_WIZARD_H
#define T4USER_SPECTRUM_WIZARD_H

#include <QWizard>
#include <QStringList>
#include "user_spectrum_description.h"
//#include "enum_selfgate_types.h"
#include "tselfgate_type.h"
#include "Tself_gate_abstract_descr.h"

class QTableWidget;

namespace Ui {
class T4user_spectrum_wizard;
}

class T4user_spectrum_wizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit T4user_spectrum_wizard(QWidget *parent = 0);
    ~T4user_spectrum_wizard();
    void set_parameters( user_spectrum_description * s, bool editing );

    enum { page__name_of_spectrum = 10, page__binning_1D = 20, page__binning_2D = 30,
           page__x_incrementers = 40, page__y_incrementers = 50, page__combinations = 60,
           page__conditon = 70 } ;

    string name_without_extension(string);
    string selgate_name_with_extension(string sg, string incrementer);

private slots:

    void accept();
    int nextId () const;  // virtual f. from base class
    void on_lineEdit_spectrum_name_textChanged(const QString &arg1);
    bool validateCurrentPage();
    void on_pushButton_add_clicked();
    void on_pushButton_remove_x_clicked();
    void on_table_incr_x_cellDoubleClicked(int row, int column);

    void on_pushButton_add_y_clicked();
    void on_pushButton_remove_y_clicked();
    void on_table_incr_y_cellDoubleClicked(int row, int column);
    void on_push_clone_clicked();

    void on_push_crea_self_x_clicked();
    void on_push_edit_self_x_clicked();

    void on_push_crea_self_Y_clicked();
    void on_push_edit_self_y_clicked();

    void on_push_common_sg_clicked();

private:
    Ui::T4user_spectrum_wizard *ui;
    bool cloning;
    QStringList list_of_all_increm;
    user_spectrum_description *user ;

    void spectrum_name_changed();
    void load_combo_conditions();
    void illegal_value( double d );
    bool check_xy_time_diff_selfgate_correctness();
    string short_long_name( string name);
    void increm_dialog_called();

    void run_condition_wizard();
    void called_creator_self_gate(QTableWidget *table, bool create_or_edit);
    //void called_editor_self_gate(QTableWidget *);
    void selfgate_succesfully_created(string, QTableWidget *table);

    Tselfgate_type::Types selfgate_type_for_this_type_of_incrementer(string name_of_incrementer);

    // Now there is an extra file produced by the spy - list_of_variables_with_selfgates.txt
    // where we can find only these incrementerers which have selfgate code
    //  - different than 0 ("not available")

    void table_incr_DoubleClicked(QTableWidget * table, int row, int column);

    void add_clicked(QTableWidget *table);
    void remove_clicked(QTableWidget *table);
    void grey_cells(QTableWidget * table, int row);
    string select_sg_name_from_disk(Tselfgate_type t);

    bool has_any_ALL_incremeter() const;


    QColor szary;
    string NoSelfGate;


};

#endif // T4USER_SPECTRUM_WIZARD_H
