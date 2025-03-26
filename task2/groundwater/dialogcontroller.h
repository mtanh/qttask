#ifndef DIALOGCONTROLLER_H
#define DIALOGCONTROLLER_H
#include <QDialog>
#include <QDialogButtonBox>
#include "msewidget.h"
#include "otherwallswidget.h"

class DialogController : public QDialog
{
    Q_OBJECT
public:
    explicit DialogController(bool isMSE, QWidget *parent = nullptr);
    ~DialogController();
    GroundwaterModel getModel() const;
    void setModel(const GroundwaterModel& model);

protected:
    void reject() override; // Override to show a warning message box

private:
    QWidget* widget; // Either MSEWidget or OtherWallsWidget
    QDialogButtonBox* buttonBox; // For OK and Cancel buttons
};
#endif
