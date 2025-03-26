#ifndef OTHERWALLSWIDGET_H
#define OTHERWALLSWIDGET_H
#include <QWidget>
#include "groundwatermodel.h"

namespace Ui
{
    class OtherWallsWidget;
}

class OtherWallsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OtherWallsWidget(QWidget *parent = nullptr);
    ~OtherWallsWidget();
    void updateFromModel(const GroundwaterModel& model);
    GroundwaterModel getModel() const;

private slots:
    void on_includeWaterTable_toggled();
    void on_constantRadio_toggled();
    void on_differentialRadio_toggled();

private:
    Ui::OtherWallsWidget *ui;
    void updateControlsState();
};
#endif
