#include "groundwaterdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

GroundwaterDialog::GroundwaterDialog(GroundwaterModel* model, QWidget *parent)
    : QDialog(parent), m_model(model)
{
    setWindowTitle(m_model->isMSE() ? "MSE Dialog" : "Other Walls Dialog");

    if (m_model->isMSE())
    {
        m_widget = new MSEGroundwaterWidget(m_model, this);
    }
    else
    {
        m_widget = new OtherWallsGroundwaterWidget(m_model, this);
    }

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_widget);
    mainLayout->addStretch();

    if (m_model->isMSE())
    {
        MSEGroundwaterWidget* mseWidget = qobject_cast<MSEGroundwaterWidget*>(m_widget);
        connect(mseWidget, &MSEGroundwaterWidget::includeWaterTableToggled, this, &GroundwaterDialog::onIncludeWaterTableToggled);
        connect(mseWidget, &MSEGroundwaterWidget::constantToggled, this, &GroundwaterDialog::onConstantToggled);
        connect(mseWidget, &MSEGroundwaterWidget::differentialToggled, this, &GroundwaterDialog::onDifferentialToggled);
        connect(mseWidget, &MSEGroundwaterWidget::applyToAllToggled, this, &GroundwaterDialog::applyToAllSectionsPlaceholder);
    }
    else
    {
        OtherWallsGroundwaterWidget* otherWidget = qobject_cast<OtherWallsGroundwaterWidget*>(m_widget);
        connect(otherWidget, &OtherWallsGroundwaterWidget::includeWaterTableToggled, this, &GroundwaterDialog::onIncludeWaterTableToggled);
        connect(otherWidget, &OtherWallsGroundwaterWidget::constantToggled, this, &GroundwaterDialog::onConstantToggled);
        connect(otherWidget, &OtherWallsGroundwaterWidget::differentialToggled, this, &GroundwaterDialog::onDifferentialToggled);
        connect(otherWidget, &OtherWallsGroundwaterWidget::applyToAllToggled, this, &GroundwaterDialog::applyToAllSectionsPlaceholder);
    }
}

void GroundwaterDialog::onIncludeWaterTableToggled(bool checked)
{
    m_model->setIncludeWaterTable(checked);
    if (m_model->isMSE())
    {
        qobject_cast<MSEGroundwaterWidget*>(m_widget)->updateControls();
    }
    else
    {
        qobject_cast<OtherWallsGroundwaterWidget*>(m_widget)->updateControls();
    }
}

void GroundwaterDialog::onConstantToggled(bool checked)
{
    if (checked)
    {
        m_model->setIsConstant(true);
        if (m_model->isMSE())
        {
            qobject_cast<MSEGroundwaterWidget*>(m_widget)->updateControls();
        }
        else
        {
            qobject_cast<OtherWallsGroundwaterWidget*>(m_widget)->updateControls();
        }
    }
}

void GroundwaterDialog::onDifferentialToggled(bool checked)
{
    if (checked)
    {
        m_model->setIsConstant(false);
        if (m_model->isMSE())
        {
            qobject_cast<MSEGroundwaterWidget*>(m_widget)->updateControls();
        }
        else
        {
            qobject_cast<OtherWallsGroundwaterWidget*>(m_widget)->updateControls();
        }
    }
}

void GroundwaterDialog::saveModelState()
{
    bool ok;
    double value;
    QLineEdit* waterElevationEdit = m_widget->findChild<QLineEdit*>("waterElevationEdit");
    QLineEdit* backslopeElevationEdit = m_widget->findChild<QLineEdit*>("backslopeWaterElevationEdit");
    QLineEdit* frontFaceElevationEdit = m_widget->findChild<QLineEdit*>("frontFaceWaterElevationEdit");
    QCheckBox* applyToAllCheck = m_widget->findChild<QCheckBox*>("applyToAllCheck");

    value = waterElevationEdit->text().toDouble(&ok);
    if (ok) m_model->setWaterElevation(value);
    value = backslopeElevationEdit->text().toDouble(&ok);
    if (ok) m_model->setBackslopeWaterElevation(value);
    value = frontFaceElevationEdit->text().toDouble(&ok);
    if (ok) m_model->setFrontFaceWaterElevation(value);

    if (m_model->isMSE())
    {
        QCheckBox* infiltratesCheck = m_widget->findChild<QCheckBox*>("infiltratesCheck");
        m_model->setInfiltratesReinforcedZone(infiltratesCheck->isChecked());
    }

    m_model->setApplyToAllSections(applyToAllCheck->isChecked());
}

void GroundwaterDialog::applyToAllSectionsPlaceholder(bool checked)
{
    qDebug() << "Apply to all sections toggled:" << checked;
}
