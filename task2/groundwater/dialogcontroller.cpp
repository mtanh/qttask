#include <QVBoxLayout>
#include <QMessageBox>
#include "dialogcontroller.h"

DialogController::DialogController(bool isMSE, QWidget *parent) :
    QDialog(parent),
    buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this))
{
    if (isMSE)
    {
        widget = new MSEWidget(this);
    }
    else
    {
        widget = new OtherWallsWidget(this);
    }

    // Create the layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(widget);
    layout->addWidget(buttonBox);

    // Set the window title
    setWindowTitle("Define Groundwater");

    // Connect the button box signals
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

DialogController::~DialogController()
{
}

GroundwaterModel DialogController::getModel() const
{
    if (dynamic_cast<MSEWidget*>(widget))
    {
        return static_cast<MSEWidget*>(widget)->getModel();
    }
    else
    {
        return static_cast<OtherWallsWidget*>(widget)->getModel();
    }
}

void DialogController::setModel(const GroundwaterModel& model)
{
    if (dynamic_cast<MSEWidget*>(widget))
    {
        static_cast<MSEWidget*>(widget)->updateFromModel(model);
    }
    else
    {
        static_cast<OtherWallsWidget*>(widget)->updateFromModel(model);
    }
}

void DialogController::reject()
{
    // Show a warning message box when the user clicks Cancel
    QMessageBox::StandardButton reply = QMessageBox::warning(
        this,
        "Warning",
        "If you cancel, your changes will be lost.\n\n"
        "Are you sure you want to discard your changes?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No // Default button is "No"
    );

    if (reply == QMessageBox::Yes)
    {
        QDialog::reject();
    }
}
