#ifndef GROUNDWATERWIDGET_H
#define GROUNDWATERWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QCheckBox>
#include "groundwatermodel.h"

class GroundwaterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GroundwaterWidget(GroundwaterModel* model, QWidget *parent = nullptr);
    void updateControls(); // To update UI from outside

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

#endif // GROUNDWATERWIDGET_H
