#ifndef MSEWIDGET_H
#define MSEWIDGET_H
#include <QWidget>
#include "groundwatermodel.h"

namespace Ui
{
    class MSEWidget;
}

class MSEWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MSEWidget(QWidget *parent = nullptr);
    ~MSEWidget();
    void updateFromModel(const GroundwaterModel& model);
    GroundwaterModel getModel() const;

private slots:
    void on_includeWaterTable_toggled();
    void on_constantRadio_toggled();
    void on_differentialRadio_toggled();

private:
    Ui::MSEWidget *ui;
    void updateControlsState();
};
#endif
