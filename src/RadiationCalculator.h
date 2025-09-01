#ifndef RADIATIONCALCULATOR_H
#define RADIATIONCALCULATOR_H

#include <string>

enum class RadiationUnit {
    MICROSIEVERTS_PER_HOUR,
    MILLISIEVERTS_PER_HOUR,
    SIEVERTS_PER_HOUR
};

enum class DangerLevel {
    SAFE,        // < 0.5 μSv/h
    CAUTION,     // 0.5-2 μSv/h
    DANGEROUS,   // 2-100 μSv/h
    EXTREME,     // 100-1000 μSv/h
    LETHAL       // > 1000 μSv/h
};

class RadiationCalculator {
public:
    RadiationCalculator();
    
    // Conversiones de unidades
    double convertToMicroSieverts(double value, RadiationUnit unit);
    std::string formatWithUnit(double microSieverts, RadiationUnit targetUnit);
    
    // Clasificación de peligro
    DangerLevel getDangerLevel(double microSieverts);
    std::string getDangerDescription(DangerLevel level);
    std::string getDangerColor(DangerLevel level);
    int getDangerPercentage(double microSieverts);
    
    // Tiempo de exposición segura
    double getSafeExposureTime(double microSieverts);
    
    // Conversiones automáticas para display
    std::string getAutoFormattedValue(double microSieverts);
    
    // Validación de rangos
    bool isValidRadiationLevel(double value, RadiationUnit unit);
    
private:
    double microSievertsToMilliSieverts(double microSieverts);
    double microSievertsToSieverts(double microSieverts);
    double getDangerThreshold(DangerLevel level);
};

#endif // RADIATIONCALCULATOR_H