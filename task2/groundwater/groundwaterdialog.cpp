#include "groundwaterdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

GroundwaterDialog::GroundwaterDialog(GroundwaterModel* model, QWidget *parent)
    : QDialog(parent), m_model(model)
{
    setWindowTitle(m_model->isMSE() ? "MSE Dialog" : "Other Walls Dialog");

    // Tạo widget tùy chỉnh
    m_widget = new GroundwaterWidget(m_model, this);

    // Thêm widget vào layout của dialog
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_widget);
    mainLayout->addStretch();

    // Kết nối tín hiệu từ widget đến các slot của dialog
    connect(m_widget, &GroundwaterWidget::includeWaterTableToggled, this, &GroundwaterDialog::onIncludeWaterTableToggled);
    connect(m_widget, &GroundwaterWidget::constantToggled, this, &GroundwaterDialog::onConstantToggled);
    connect(m_widget, &GroundwaterWidget::differentialToggled, this, &GroundwaterDialog::onDifferentialToggled);
    connect(m_widget, &GroundwaterWidget::applyToAllToggled, this, &GroundwaterDialog::applyToAllSectionsPlaceholder);
}

void GroundwaterDialog::onIncludeWaterTableToggled(bool checked)
{
    m_model->setIncludeWaterTable(checked);
    m_widget->updateControls();
}

void GroundwaterDialog::onConstantToggled(bool checked)
{
    if (checked) {
        m_model->setIsConstant(true);
        m_widget->updateControls();
    }
}

void GroundwaterDialog::onDifferentialToggled(bool checked)
{
    if (checked) {
        m_model->setIsConstant(false);
        m_widget->updateControls();
    }
}

void GroundwaterDialog::saveModelState()
{
    bool ok;
    double value;

    // Lấy giá trị từ các QLineEdit trong widget
    value = m_widget->findChild<QLineEdit*>("waterElevationEdit")->text().toDouble(&ok);
    if (ok) m_model->setWaterElevation(value);
    value = m_widget->findChild<QLineEdit*>("backslopeWaterElevationEdit")->text().toDouble(&ok);
    if (ok) m_model->setBackslopeWaterElevation(value);
    value = m_widget->findChild<QLineEdit*>("frontFaceWaterElevationEdit")->text().toDouble(&ok);
    if (ok) m_model->setFrontFaceWaterElevation(value);

    // Lấy trạng thái từ các QCheckBox trong widget
    m_model->setInfiltratesReinforcedZone(m_widget->findChild<QCheckBox*>("infiltratesCheck")->isChecked());
    m_model->setApplyToAllSections(m_widget->findChild<QCheckBox*>("applyToAllCheck")->isChecked());
}

void GroundwaterDialog::applyToAllSectionsPlaceholder(bool checked)
{
    qDebug() << "Apply to all sections toggled:" << checked;
}
