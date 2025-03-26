#include "groundwaterwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

GroundwaterWidget::GroundwaterWidget(GroundwaterModel* model, QWidget *parent)
    : QWidget(parent), m_model(model)
{
    setupUi();
    setInitialState();
}

void GroundwaterWidget::setupUi()
{
    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Group box for water table
    m_waterTableGroup = new QGroupBox("Include water table");
    m_includeWaterTableCheck = new QCheckBox("Include");
    QVBoxLayout* groupLayout = new QVBoxLayout(m_waterTableGroup);
    groupLayout->addWidget(m_includeWaterTableCheck);

    // Radio buttons
    m_constantRadio = new QRadioButton("Constant");
    m_differentialRadio = new QRadioButton("Differential");
    groupLayout->addWidget(m_constantRadio);
    groupLayout->addWidget(m_differentialRadio);

    // Water elevation controls
    QHBoxLayout* waterLayout = new QHBoxLayout;
    m_waterElevationEdit = new QLineEdit;
    waterLayout->addWidget(new QLabel("Water elevation (m/ft):"));
    waterLayout->addWidget(m_waterElevationEdit);
    groupLayout->addLayout(waterLayout);

    QHBoxLayout* backslopeLayout = new QHBoxLayout;
    m_backslopeWaterElevationEdit = new QLineEdit;
    backslopeLayout->addWidget(new QLabel("Backslope water elevation (m/ft):"));
    backslopeLayout->addWidget(m_backslopeWaterElevationEdit);
    groupLayout->addLayout(backslopeLayout);

    QHBoxLayout* frontFaceLayout = new QHBoxLayout;
    m_frontFaceWaterElevationEdit = new QLineEdit;
    frontFaceLayout->addWidget(new QLabel("Front face water elevation (m/ft):"));
    frontFaceLayout->addWidget(m_frontFaceWaterElevationEdit);
    groupLayout->addLayout(frontFaceLayout);

    // Infiltrates checkbox (only for MSE)
    m_infiltratesCheck = new QCheckBox("Infiltrates reinforced zone");
    m_infiltratesCheck->setVisible(m_model->isMSE());
    groupLayout->addWidget(m_infiltratesCheck);

    // Apply to all sections
    m_applyToAllCheck = new QCheckBox("Apply to all sections");
    groupLayout->addWidget(m_applyToAllCheck);

    mainLayout->addWidget(m_waterTableGroup);
    mainLayout->addStretch();

    // Connections
    connect(m_includeWaterTableCheck, &QCheckBox::toggled, this, &GroundwaterWidget::includeWaterTableToggled);
    connect(m_constantRadio, &QRadioButton::toggled, this, &GroundwaterWidget::constantToggled);
    connect(m_differentialRadio, &QRadioButton::toggled, this, &GroundwaterWidget::differentialToggled);
    connect(m_applyToAllCheck, &QCheckBox::toggled, this, &GroundwaterWidget::applyToAllToggled);

    // Tab order
    setTabOrder(m_includeWaterTableCheck, m_constantRadio);
    setTabOrder(m_constantRadio, m_differentialRadio);
    setTabOrder(m_differentialRadio, m_waterElevationEdit);
    setTabOrder(m_waterElevationEdit, m_backslopeWaterElevationEdit);
    setTabOrder(m_backslopeWaterElevationEdit, m_frontFaceWaterElevationEdit);
    setTabOrder(m_frontFaceWaterElevationEdit, m_infiltratesCheck);
    setTabOrder(m_infiltratesCheck, m_applyToAllCheck);

    // Margins
    mainLayout->setContentsMargins(10, 10, 10, 10);
    groupLayout->setContentsMargins(5, 5, 5, 5);
}

void GroundwaterWidget::setInitialState()
{
    m_includeWaterTableCheck->setChecked(m_model->includeWaterTable());
    m_constantRadio->setChecked(m_model->isConstant());
    m_differentialRadio->setChecked(!m_model->isConstant());
    m_waterElevationEdit->setText(QString::number(m_model->waterElevation()));
    m_backslopeWaterElevationEdit->setText(QString::number(m_model->backslopeWaterElevation()));
    m_frontFaceWaterElevationEdit->setText(QString::number(m_model->frontFaceWaterElevation()));
    m_infiltratesCheck->setChecked(m_model->infiltratesReinforcedZone());
    m_applyToAllCheck->setChecked(m_model->applyToAllSections());
    updateControls();
}

void GroundwaterWidget::updateControls()
{
    bool enabled = m_includeWaterTableCheck->isChecked();
    m_constantRadio->setEnabled(enabled);
    m_differentialRadio->setEnabled(enabled);
    m_waterElevationEdit->setEnabled(enabled && m_constantRadio->isChecked());
    m_backslopeWaterElevationEdit->setEnabled(enabled && m_differentialRadio->isChecked());
    m_frontFaceWaterElevationEdit->setEnabled(enabled && m_differentialRadio->isChecked());
    m_infiltratesCheck->setEnabled(enabled && m_model->isMSE());
    m_applyToAllCheck->setEnabled(enabled);
}
