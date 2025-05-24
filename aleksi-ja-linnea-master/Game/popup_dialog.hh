#ifndef POPUP_DIALOG_HH
#define POPUP_DIALOG_HH

#include <QDialog>
#include "mapitem.hh"
#include "tilebase_s.h"
#include "workerbase_s.h"
#include "player.hh"
#include "student_resourcemaps.h"

namespace Ui {
class popup_dialog;
}


/** @brief
 * Popup dialog initialized by mouse click events on the gamescene.
 * Initializes only if the current player owns the clicked property.
 * Player can send workers to activities or buy workers from HQ.
 * */
class popup_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit popup_dialog(std::shared_ptr<Student::tilebase_s> tile, std::shared_ptr<Student::Player> player, bool is_berrybush, QWidget *parent = 0);

    /** Default destructor **/
    ~popup_dialog();

    /** Sets the basic interface texts **/
    void setPopupTexts();

signals:

    /** Sends the tile and the activity specified workertype to gamescene
     * @param tile - clicked tile
     * @param type - worker type that's required for the activity
     * */
    void sendValue(std::shared_ptr<Course::TileBase> tile, std::string type);

    /** Emits a signal that player has successfully bought a specific type of worker.
     * @param workertype - worker type player bought
     * */
    std::string player_bought();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_send_worker_btn_clicked();

    void on_pushButton_3_clicked();

private:

    Ui::popup_dialog *ui;
    std::shared_ptr<Student::tilebase_s> tile;
    std::shared_ptr<Student::Player> player_;

    bool is_tile_berrybush;

    /** Hide some of the texts if the clicked tile isn't players HQ **/
    void hideTexts();

    /** Checks if player has resources to commit a specific activity.
     * @param resources - Resourcemap of the chosen activity
     * @return true if player has the resources, false if not.
     * **/
    bool check_if_player_has_funds(Course::ResourceMap resources);
};

#endif // POPUP_DIALOG_HH
