#include "t4results_of_integration.h"
#include "ui_t4results_of_integration.h"


#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "tplate_spectrum.h"

extern T4results_of_integration * integr_resul_ptr;

//*********************************************************************************
T4results_of_integration::T4results_of_integration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T4results_of_integration)
{
    ui->setupUi(this);
    integr_resul_ptr = this;
}
//*********************************************************************************
T4results_of_integration::~T4results_of_integration()
{
    delete ui;
}
//*********************************************************************************

void T4results_of_integration::on_button_clear_clicked()
{
    ui->textEdit1->setPlainText("");
}
//*********************************************************************************
void T4results_of_integration::on_pushButton_save_to_file_clicked()
{
    // storing on the disk the whole contents of the textEdit
    static QString last_file = "" ;


     Tplate_spectrum::flag_repainting_allowed = false;
 QString fileName;
        QString filter;

        fileName = QFileDialog::getSaveFileName(this,
                                                tr("Save current matrix as a file "),
                                                QString("./"),
                                                tr( "Any files (*);; Text files (*.txt)"),
                                                &filter
                                               );
 Tplate_spectrum::flag_repainting_allowed = true;
        
//     if ( fd->exec() == QDialog::Accepted )
//     {
//         fileName = fd->selectedFile();
//     }
    //cout << "Nazwa " << fileName << endl ;
    if(fileName.endsWith ( ".txt") == -1)
    {
        fileName.append(".txt");
    }

    if(fileName.size() )
    {
        // saving everything to the disk

        QFile file( fileName ); // Write the text to a file

        QIODevice::OpenMode   flags_to_open = QIODevice::WriteOnly ;
        if(file.exists() )
        {
            switch(QMessageBox::information ( this, "File exists",
                                                                                "File exists, Overwrite it or append ?",
                                                                                "Overwrite",
                                                                                "Append",
                                                                                "Cancel",
                                                                                2)
                  ) // int defaultButtonNumber = 0,
            {
                                        case 0:
                break ;
                                        case 1:
                flags_to_open = (QIODevice::WriteOnly | QIODevice::Append);
                break ;
                                        default:
                return ;

            }
        }

        if ( file.open( flags_to_open ) )
        {
            QTextStream stream( &file );   // bylo (&file)
            stream << ui->textEdit1->toPlainText();
            //ui->textEdit1->setModified( false );    // ?????????????????? w Qt3
            last_file = fileName ;
        }


    }
}
//*********************************************************************************
void T4results_of_integration::add_results(const char *ss )
{
     ui->  textEdit1->append(ss);
}
//*********************************************************************************
bool T4results_of_integration::multi_line_mode()
{
    return ! ui->checkBox_one_line->isChecked() ;
}
//*********************************************************************************
