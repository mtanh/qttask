#ifndef GROUNDWATERMODEL_H
#define GROUNDWATERMODEL_H

#include <QString>

class GroundwaterModel
{
public:
    GroundwaterModel(bool isMSE);

    // Getters and setters
    bool includeWaterTable() const { return m_includeWaterTable; }
    void setIncludeWaterTable(bool value) { m_includeWaterTable = value; }

    bool isConstant() const { return m_isConstant; }
    void setIsConstant(bool value) { m_isConstant = value; }

    double waterElevation() const { return m_waterElevation; }
    void setWaterElevation(double value) { m_waterElevation = value; }

    double backslopeWaterElevation() const { return m_backslopeWaterElevation; }
    void setBackslopeWaterElevation(double value) { m_backslopeWaterElevation = value; }

    double frontFaceWaterElevation() const { return m_frontFaceWaterElevation; }
    void setFrontFaceWaterElevation(double value) { m_frontFaceWaterElevation = value; }

    bool infiltratesReinforcedZone() const { return m_infiltratesReinforcedZone; }
    void setInfiltratesReinforcedZone(bool value) { m_infiltratesReinforcedZone = value; }

    bool applyToAllSections() const { return m_applyToAllSections; }
    void setApplyToAllSections(bool value) { m_applyToAllSections = value; }

    bool isMSE() const { return m_isMSE; }

private:
    bool m_includeWaterTable = false; // Default OFF
    bool m_isConstant = true;         // Default to "Constant"
    double m_waterElevation = 0.0;
    double m_backslopeWaterElevation = 0.0;
    double m_frontFaceWaterElevation = 0.0;
    bool m_infiltratesReinforcedZone = false; // Default OFF
    bool m_applyToAllSections = false;
    bool m_isMSE; // Determines if this is MSE or Other Walls
};

#endif // GROUNDWATERMODEL_H
