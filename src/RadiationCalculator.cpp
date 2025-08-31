#include "RadiationCalculator.h"
#include <sstream>
#include <iomanip>
#include <cmath>

RadiationCalculator::RadiationCalculator() {
}

double RadiationCalculator::convertToMicroSieverts(double value, RadiationUnit unit) {
    switch (unit) {
        case RadiationUnit::MICROSIEVERTS_PER_HOUR:
            return value;
        case RadiationUnit::MILLISIEVERTS_PER_HOUR:
            return value * 1000.0;
        case RadiationUnit::SIEVERTS_PER_HOUR:
            return value * 1000000.0;
        default:
            return 0.0;
    }
}

std::string RadiationCalculator::formatWithUnit(double microSieverts, RadiationUnit targetUnit) {
    std::ostringstream oss;
    oss << std::fixed;
    
    switch (targetUnit) {
        case RadiationUnit::MICROSIEVERTS_PER_HOUR:
            oss << std::setprecision(1) << microSieverts << " μSv/h";
            break;
        case RadiationUnit::MILLISIEVERTS_PER_HOUR:
            oss << std::setprecision(3) << microSievertsToMilliSieverts(microSieverts) << " mSv/h";
            break;
        case RadiationUnit::SIEVERTS_PER_HOUR:
            oss << std::setprecision(6) << microSievertsToSieverts(microSieverts) << " Sv/h";
            break;
    }
    
    return oss.str();
}

DangerLevel RadiationCalculator::getDangerLevel(double microSieverts) {
    if (microSieverts < 0.5) {
        return DangerLevel::SAFE;
    } else if (microSieverts < 2.0) {
        return DangerLevel::CAUTION;
    } else if (microSieverts < 100.0) {
        return DangerLevel::DANGEROUS;
    } else if (microSieverts < 1000.0) {
        return DangerLevel::EXTREME;
    } else {
        return DangerLevel::LETHAL;
    }
}

std::string RadiationCalculator::getDangerDescription(DangerLevel level) {
    switch (level) {
        case DangerLevel::SAFE:
            return "SEGURO - Nivel normal de fondo";
        case DangerLevel::CAUTION:
            return "PRECAUCIÓN - Ligeramente elevado";
        case DangerLevel::DANGEROUS:
            return "PELIGROSO - Exposición limitada recomendada";
        case DangerLevel::EXTREME:
            return "⚠️ EXTREMO - Riesgo significativo para la salud";
        case DangerLevel::LETHAL:
            return "☠️ LETAL - EVACUACIÓN INMEDIATA";
        default:
            return "DESCONOCIDO";
    }
}

std::string RadiationCalculator::getDangerColor(DangerLevel level) {
    switch (level) {
        case DangerLevel::SAFE:
            return "#00FF41";  // Verde fosforescente
        case DangerLevel::CAUTION:
            return "#FFFF00";  // Amarillo
        case DangerLevel::DANGEROUS:
            return "#FF8C00";  // Naranja
        case DangerLevel::EXTREME:
            return "#FF0000";  // Rojo
        case DangerLevel::LETHAL:
            return "#FF0000";  // Rojo crítico
        default:
            return "#00FF41";
    }
}

int RadiationCalculator::getDangerPercentage(double microSieverts) {
    if (microSieverts <= 0.5) {
        return static_cast<int>((microSieverts / 0.5) * 20);
    } else if (microSieverts <= 2.0) {
        return 20 + static_cast<int>(((microSieverts - 0.5) / 1.5) * 20);
    } else if (microSieverts <= 100.0) {
        return 40 + static_cast<int>(((microSieverts - 2.0) / 98.0) * 30);
    } else if (microSieverts <= 1000.0) {
        return 70 + static_cast<int>(((microSieverts - 100.0) / 900.0) * 20);
    } else {
        return std::min(100, 90 + static_cast<int>(log10(microSieverts / 1000.0) * 5));
    }
}

double RadiationCalculator::getSafeExposureTime(double microSieverts) {
    const double ANNUAL_LIMIT = 1000000.0; // 1 mSv/año en μSv
    const double HOURS_PER_YEAR = 8760.0;
    
    if (microSieverts <= 0.0) {
        return HOURS_PER_YEAR;
    }
    
    double safeHoursPerYear = ANNUAL_LIMIT / microSieverts;
    
    if (safeHoursPerYear > HOURS_PER_YEAR) {
        return HOURS_PER_YEAR;
    }
    
    return safeHoursPerYear;
}

std::string RadiationCalculator::getAutoFormattedValue(double microSieverts) {
    if (microSieverts >= 1000000.0) {
        return formatWithUnit(microSieverts, RadiationUnit::SIEVERTS_PER_HOUR);
    } else if (microSieverts >= 1000.0) {
        return formatWithUnit(microSieverts, RadiationUnit::MILLISIEVERTS_PER_HOUR);
    } else {
        return formatWithUnit(microSieverts, RadiationUnit::MICROSIEVERTS_PER_HOUR);
    }
}

bool RadiationCalculator::isValidRadiationLevel(double value, RadiationUnit unit) {
    if (value < 0) return false;
    
    double microSieverts = convertToMicroSieverts(value, unit);
    return microSieverts <= 1000000000.0; // Límite máximo práctico
}

double RadiationCalculator::microSievertsToMilliSieverts(double microSieverts) {
    return microSieverts / 1000.0;
}

double RadiationCalculator::microSievertsToSieverts(double microSieverts) {
    return microSieverts / 1000000.0;
}

double RadiationCalculator::getDangerThreshold(DangerLevel level) {
    switch (level) {
        case DangerLevel::SAFE: return 0.5;
        case DangerLevel::CAUTION: return 2.0;
        case DangerLevel::DANGEROUS: return 100.0;
        case DangerLevel::EXTREME: return 1000.0;
        default: return 0.0;
    }
}