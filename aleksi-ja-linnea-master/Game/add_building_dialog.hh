#ifndef ADD_BUILDING_DIALOG_HH
#define ADD_BUILDING_DIALOG_HH

#include <QDialog>
#include "core/resourcemaps.h"
#include <QString>
#include "student_resourcemaps.h"

namespace Ui {
class add_building_dialog;
}


/** @brief
 * Popup window that's used to buy new properties in the game.
 * Emits the wanted property type to gamescene.
 * */
class add_building_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_building_dialog(Course::ResourceMap resources, QWidget *parent = 0);

    /** Default destructor **/
    ~add_building_dialog();

signals:

    /** Sends the chosen property type forward
    * @param type - property type **/
    void sendValue_2(QString type);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:

    Ui::add_building_dialog *ui;
    Course::ResourceMap player_resources;
    bool check_if_player_has_funds(Course::ResourceMap resources);
};

#endif // ADD_BUILDING_DIALOG_HH
