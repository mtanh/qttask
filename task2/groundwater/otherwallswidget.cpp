#include "otherwallswidget.h"
#include "ui_otherwallswidget.h"

OtherWallsWidget::OtherWallsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtherWallsWidget)
{
    ui->setupUi(this);
    updateControlsState();
}

OtherWallsWidget::~OtherWallsWidget()
{
    delete ui;
}

void OtherWallsWidget::updateFromModel(const GroundwaterModel& model)
{
    ui->includeWaterTable->setChecked(model.includeWaterTable());
    ui->constantRadio->setChecked(model.isConstant());
    ui->differentialRadio->setChecked(!model.isConstant());
    ui->waterElevation->setValue(model.waterElevation());
    ui->backslopeElevation->setValue(model.backslopeElevation());
    ui->frontfaceElevation->setValue(model.frontfaceElevation());
    ui->applyToAllCheckBox->setChecked(model.applyToAllSections());
    updateControlsState();
}

GroundwaterModel OtherWallsWidget::getModel() const
{
    GroundwaterModel model;
    model.setIncludeWaterTable(ui->includeWaterTable->isChecked());
    model.setIsConstant(ui->constantRadio->isChecked());
    model.setWaterElevation(ui->waterElevation->value());
    model.setBackslopeElevation(ui->backslopeElevation->value());
    model.setFrontfaceElevation(ui->frontfaceElevation->value());
    model.setInfiltratesReinforcedZone(false); // Not applicable for Other Walls
    model.setApplyToAllSections(ui->applyToAllCheckBox->isChecked());
    return model;
}

void OtherWallsWidget::on_includeWaterTable_toggled()
{
    updateControlsState();
}

void OtherWallsWidget::on_constantRadio_toggled()
{
    updateControlsState();
}

void OtherWallsWidget::on_differentialRadio_toggled()
{
    updateControlsState();
}

void OtherWallsWidget::updateControlsState()
{
    bool waterTableEnabled = ui->includeWaterTable->isChecked();
    ui->constantRadio->setEnabled(waterTableEnabled);
    ui->differentialRadio->setEnabled(waterTableEnabled);
    ui->waterElevation->setEnabled(waterTableEnabled && ui->constantRadio->isChecked());
    ui->backslopeElevation->setEnabled(waterTableEnabled && ui->differentialRadio->isChecked());
    ui->frontfaceElevation->setEnabled(waterTableEnabled && ui->differentialRadio->isChecked());
    ui->applyToAllCheckBox->setEnabled(waterTableEnabled);
}
