#ifndef T4PATTERN_DEFINING_DLG_H
#define T4PATTERN_DEFINING_DLG_H

#include <QDialog>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class T4pattern_defining_dlg;
}

class T4pattern_defining_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit T4pattern_defining_dlg(QWidget *parent = 0);
    ~T4pattern_defining_dlg();
    void set_parameters(std::string specname,
                   std::string pattern,
                   std::string *one,
                   std::string *two);
    void   get_parameters(vector<string> * vone, vector<string> * vtwo);

private slots:
    void on_lineEdit_one_textChanged(const QString &);
    void on_lineEdit_two_textChanged(const QString &);

private:
    Ui::T4pattern_defining_dlg *ui;
    void show_spectra_names();

    std::vector<std::string> spectra_names;
    std::vector<std::string> vec_one ;
    std::vector<std::string> vec_two ;

    string nieb_pocz ;
    string czerw_pocz ;
    string kolor_kon ;

};

#endif // T4PATTERN_DEFINING_DLG_H
