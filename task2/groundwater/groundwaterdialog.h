#ifndef GROUNDWATERDIALOG_H
#define GROUNDWATERDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QCheckBox>
#include "groundwatermodel.h"

class GroundwaterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GroundwaterDialog(GroundwaterModel* model, QWidget *parent = nullptr);

private slots:
    void onIncludeWaterTableToggled(bool checked);
    void onConstantToggled(bool checked);
    void onDifferentialToggled(bool checked);
    void applyToAllSectionsPlaceholder();

private:
    void setupUi();
    void updateControls();
    void saveModelState();

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
};

#endif // GROUNDWATERDIALOG_H
