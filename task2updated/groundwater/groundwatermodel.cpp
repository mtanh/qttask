#include "groundwatermodel.h"

GroundwaterModel::GroundwaterModel()
    : m_includeWaterTable(false), m_isConstant(true),
      m_waterElevation(0.0), m_backslopeElevation(0.0),
      m_frontfaceElevation(0.0), m_infiltratesReinforcedZone(false),
      m_applyToAllSections(false)
{
}

void GroundwaterModel::setIncludeWaterTable(bool value) { m_includeWaterTable = value; }
void GroundwaterModel::setIsConstant(bool value) { m_isConstant = value; }
void GroundwaterModel::setWaterElevation(double value) { m_waterElevation = value; }
void GroundwaterModel::setBackslopeElevation(double value) { m_backslopeElevation = value; }
void GroundwaterModel::setFrontfaceElevation(double value) { m_frontfaceElevation = value; }
void GroundwaterModel::setInfiltratesReinforcedZone(bool value) { m_infiltratesReinforcedZone = value; }
void GroundwaterModel::setApplyToAllSections(bool value) { m_applyToAllSections = value; }

void GroundwaterModel::saveToSettings(QSettings& settings, const QString& prefix) const
{
    settings.setValue(prefix + "/include-water-table", m_includeWaterTable);
    settings.setValue(prefix + "/is-constant", m_isConstant);
    settings.setValue(prefix + "/water-elevation", m_waterElevation);
    settings.setValue(prefix + "/back-slope-elevation", m_backslopeElevation);
    settings.setValue(prefix + "/front-face-elevation", m_frontfaceElevation);
    settings.setValue(prefix + "/infiltrates-reinforced-zone", m_infiltratesReinforcedZone);
    settings.setValue(prefix + "/apply-to-all-sections", m_applyToAllSections);
}

void GroundwaterModel::loadFromSettings(QSettings& settings, const QString& prefix)
{
    m_includeWaterTable = settings.value(prefix + "/include-water-table", false).toBool();
    m_isConstant = settings.value(prefix + "/is-constant", true).toBool();
    m_waterElevation = settings.value(prefix + "/water-elevation", 0.0).toDouble();
    m_backslopeElevation = settings.value(prefix + "/back-slope-elevation", 0.0).toDouble();
    m_frontfaceElevation = settings.value(prefix + "/front-face-elevation", 0.0).toDouble();
    m_infiltratesReinforcedZone = settings.value(prefix + "/infiltrates-reinforced-zone", false).toBool();
    m_applyToAllSections = settings.value(prefix + "/apply-to-all-sections", false).toBool();
}
