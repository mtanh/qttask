#ifndef OTHERWALLSGROUNDWATERWIDGET_H
#define OTHERWALLSGROUNDWATERWIDGET_H
#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QCheckBox>
#include "groundwatermodel.h"

class OtherWallsGroundwaterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OtherWallsGroundwaterWidget(GroundwaterModel* model, QWidget *parent = nullptr);
    void updateControls();
private:
    void setupUi();
    GroundwaterModel* m_model;
    QGroupBox* m_waterTableGroup;
    QCheckBox* m_includeWaterTableCheck;
    QRadioButton* m_constantRadio;
    QRadioButton* m_differentialRadio;
    QLineEdit* m_waterElevationEdit;
    QLineEdit* m_backslopeWaterElevationEdit;
    QLineEdit* m_frontFaceWaterElevationEdit;
    QCheckBox* m_applyToAllCheck;
signals:
    void includeWaterTableToggled(bool checked);
    void constantToggled(bool checked);
    void differentialToggled(bool checked);
    void applyToAllToggled(bool checked);
public slots:
    void setInitialState();
};

#endif // OTHERWALLSGROUNDWATERWIDGET_H
