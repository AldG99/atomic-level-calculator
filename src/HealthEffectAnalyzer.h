#ifndef HEALTHEFFECTANALYZER_H
#define HEALTHEFFECTANALYZER_H

#include "RadiationCalculator.h"
#include <string>
#include <vector>

struct TimeEffect {
    std::string timeRange;
    std::string effect;
    std::string severity;
};

struct HealthEffects {
    DangerLevel dangerLevel;
    std::vector<TimeEffect> immediateEffects;
    std::vector<std::string> longTermEffects;
    std::vector<std::string> recommendations;
    double survivalProbabilityWithoutTreatment;
    double survivalProbabilityWithTreatment;
    std::string medicalClassification;
    std::string emergencyProtocol;
};

class HealthEffectAnalyzer {
public:
    HealthEffectAnalyzer();
    
    // Análisis principal
    HealthEffects analyzeEffects(double microSieverts, double exposureHours = 1.0);
    
    // Efectos específicos
    std::vector<TimeEffect> getImmediateEffects(double microSieverts);
    std::vector<std::string> getLongTermEffects(double microSieverts);
    std::vector<std::string> getRecommendations(DangerLevel level);
    
    // Análisis de supervivencia
    double getSurvivalProbability(double totalDose, bool withTreatment = false);
    
    // Clasificación médica
    std::string getMedicalClassification(double microSieverts);
    std::string getEmergencyProtocol(DangerLevel level);
    
    // Información educativa
    std::string getRadiationSyndromeInfo(double microSieverts);
    std::string getProtectionMeasures();
    std::string getCancerRiskInfo(double microSieverts);
    
    // Formateo para UI
    std::string formatHealthEffectsReport(const HealthEffects& effects);
    
private:
    void initializeEffectDatabase();
    double calculateAcuteDose(double microSieverts, double hours);
    std::string getSeverityColor(const std::string& severity);
};

#endif // HEALTHEFFECTANALYZER_H