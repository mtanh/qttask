#ifndef MSEGROUNDWATERWIDGET_H
#define MSEGROUNDWATERWIDGET_H
#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QCheckBox>
#include "groundwatermodel.h"

class MSEGroundwaterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MSEGroundwaterWidget(GroundwaterModel* model, QWidget *parent = nullptr);
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
    QCheckBox* m_infiltratesCheck;
    QCheckBox* m_applyToAllCheck;
signals:
    void includeWaterTableToggled(bool checked);
    void constantToggled(bool checked);
    void differentialToggled(bool checked);
    void applyToAllToggled(bool checked);
public slots:
    void setInitialState();
};

#endif // MSEGROUNDWATERWIDGET_H
