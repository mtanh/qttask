#include "msewidget.h"
#include "ui_msewidget.h"

MSEWidget::MSEWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSEWidget)
{
    ui->setupUi(this);
    updateControlsState();
}

MSEWidget::~MSEWidget()
{
    delete ui;
}

void MSEWidget::updateFromModel(const GroundwaterModel& model)
{
    ui->includeWaterTable->setChecked(model.includeWaterTable());
    ui->constantRadio->setChecked(model.isConstant());
    ui->differentialRadio->setChecked(!model.isConstant());
    ui->waterElevation->setValue(model.waterElevation());
    ui->backslopeElevation->setValue(model.backslopeElevation());
    ui->frontfaceElevation->setValue(model.frontfaceElevation());
    ui->infiltratesCheckBox->setChecked(model.infiltratesReinforcedZone());
    ui->applyToAllCheckBox->setChecked(model.applyToAllSections());
    updateControlsState();
}

GroundwaterModel MSEWidget::getModel() const
{
    GroundwaterModel model;
    model.setIncludeWaterTable(ui->includeWaterTable->isChecked());
    model.setIsConstant(ui->constantRadio->isChecked());
    model.setWaterElevation(ui->waterElevation->value());
    model.setBackslopeElevation(ui->backslopeElevation->value());
    model.setFrontfaceElevation(ui->frontfaceElevation->value());
    model.setInfiltratesReinforcedZone(ui->infiltratesCheckBox->isChecked());
    model.setApplyToAllSections(ui->applyToAllCheckBox->isChecked());
    return model;
}

void MSEWidget::on_includeWaterTable_toggled()
{
    updateControlsState();
}

void MSEWidget::on_constantRadio_toggled()
{
    updateControlsState();
}

void MSEWidget::on_differentialRadio_toggled()
{
    updateControlsState();
}

void MSEWidget::updateControlsState()
{
    bool waterTableEnabled = ui->includeWaterTable->isChecked();
    ui->constantRadio->setEnabled(waterTableEnabled);
    ui->differentialRadio->setEnabled(waterTableEnabled);
    ui->waterElevation->setEnabled(waterTableEnabled && ui->constantRadio->isChecked());
    ui->backslopeElevation->setEnabled(waterTableEnabled && ui->differentialRadio->isChecked());
    ui->frontfaceElevation->setEnabled(waterTableEnabled && ui->differentialRadio->isChecked());
    ui->infiltratesCheckBox->setEnabled(waterTableEnabled);
    ui->applyToAllCheckBox->setEnabled(waterTableEnabled);
}
