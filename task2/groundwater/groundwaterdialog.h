#ifndef GROUNDWATERDIALOG_H
#define GROUNDWATERDIALOG_H
#include <QDialog>
#include "groundwatermodel.h"
#include "msegroundwaterwidget.h"
#include "otherwallsgroundwaterwidget.h"

class GroundwaterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GroundwaterDialog(GroundwaterModel* model, QWidget *parent = nullptr);
private slots:
    void onIncludeWaterTableToggled(bool checked);
    void onConstantToggled(bool checked);
    void onDifferentialToggled(bool checked);
    void applyToAllSectionsPlaceholder(bool checked);
private:
    void saveModelState();
    GroundwaterModel* m_model;
    QWidget* m_widget;
};

#endif // GROUNDWATERDIALOG_H
