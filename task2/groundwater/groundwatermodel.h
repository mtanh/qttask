#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QSettings>

class GroundwaterModel
{
public:
    GroundwaterModel();

    bool includeWaterTable() const { return m_includeWaterTable; }
    bool isConstant() const { return m_isConstant; }
    double waterElevation() const { return m_waterElevation; }
    double backslopeElevation() const { return m_backslopeElevation; }
    double frontfaceElevation() const { return m_frontfaceElevation; }
    bool infiltratesReinforcedZone() const { return m_infiltratesReinforcedZone; }
    bool applyToAllSections() const { return m_applyToAllSections; }

    void setIncludeWaterTable(bool value);
    void setIsConstant(bool value);
    void setWaterElevation(double value);
    void setBackslopeElevation(double value);
    void setFrontfaceElevation(double value);
    void setInfiltratesReinforcedZone(bool value);
    void setApplyToAllSections(bool value);

    // Methods for serialization
    void saveToSettings(QSettings& settings, const QString& prefix) const;
    void loadFromSettings(QSettings& settings, const QString& prefix);

private:
    bool m_includeWaterTable;
    bool m_isConstant;
    double m_waterElevation;
    double m_backslopeElevation;
    double m_frontfaceElevation;
    bool m_infiltratesReinforcedZone;
    bool m_applyToAllSections;
};
#endif
