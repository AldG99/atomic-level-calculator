#include "HealthEffectAnalyzer.h"
#include <cmath>
#include <sstream>
#include <iomanip>

HealthEffectAnalyzer::HealthEffectAnalyzer() {
    initializeEffectDatabase();
}

HealthEffects HealthEffectAnalyzer::analyzeEffects(double microSieverts, double exposureHours) {
    HealthEffects effects;
    RadiationCalculator calc;
    
    effects.dangerLevel = calc.getDangerLevel(microSieverts);
    effects.immediateEffects = getImmediateEffects(microSieverts);
    effects.longTermEffects = getLongTermEffects(microSieverts);
    effects.recommendations = getRecommendations(effects.dangerLevel);
    effects.medicalClassification = getMedicalClassification(microSieverts);
    effects.emergencyProtocol = getEmergencyProtocol(effects.dangerLevel);
    
    double totalDose = calculateAcuteDose(microSieverts, exposureHours);
    effects.survivalProbabilityWithoutTreatment = getSurvivalProbability(totalDose, false);
    effects.survivalProbabilityWithTreatment = getSurvivalProbability(totalDose, true);
    
    return effects;
}

std::vector<TimeEffect> HealthEffectAnalyzer::getImmediateEffects(double microSieverts) {
    std::vector<TimeEffect> effects;
    
    if (microSieverts < 2.0) {
        effects.push_back({"0-24 horas", "Sin síntomas observables", "NINGUNO"});
        return effects;
    } else if (microSieverts < 100.0) {
        effects.push_back({"0-6 horas", "Posible fatiga leve", "LEVE"});
        effects.push_back({"6-24 horas", "Ligera disminución del apetito", "LEVE"});
    } else if (microSieverts < 1000.0) {
        effects.push_back({"0-2 horas", "Náuseas y vómitos ocasionales", "MODERADO"});
        effects.push_back({"2-6 horas", "Fatiga y mareos", "MODERADO"});
        effects.push_back({"6-24 horas", "Pérdida del apetito", "MODERADO"});
    } else if (microSieverts < 10000.0) {
        effects.push_back({"0-2 horas", "Náuseas y vómitos severos", "SEVERO"});
        effects.push_back({"2-6 horas", "Fatiga extrema, mareos", "SEVERO"});
        effects.push_back({"6-24 horas", "Diarrea, fiebre", "SEVERO"});
        effects.push_back({"1-7 días", "Síndrome de radiación aguda", "SEVERO"});
    } else {
        effects.push_back({"0-1 hora", "Náuseas y vómitos inmediatos", "CRÍTICO"});
        effects.push_back({"1-4 horas", "Colapso cardiovascular", "CRÍTICO"});
        effects.push_back({"4-48 horas", "Síndrome neurológico agudo", "CRÍTICO"});
        effects.push_back({"2-14 días", "Muerte probable", "CRÍTICO"});
    }
    
    return effects;
}

std::vector<std::string> HealthEffectAnalyzer::getLongTermEffects(double microSieverts) {
    std::vector<std::string> effects;
    
    if (microSieverts < 0.5) {
        effects.push_back("• Sin efectos detectables a largo plazo");
        effects.push_back("• Riesgo de cáncer: No incrementado");
    } else if (microSieverts < 2.0) {
        effects.push_back("• Riesgo de cáncer: Ligeramente incrementado (<0.1%)");
        effects.push_back("• Efectos genéticos: Mínimos o inexistentes");
    } else if (microSieverts < 100.0) {
        effects.push_back("• Riesgo de cáncer: BAJO (0.1-5% probabilidad)");
        effects.push_back("• Posibles efectos en fertilidad temporal");
        effects.push_back("• Daño cromosómico menor detectable");
    } else if (microSieverts < 1000.0) {
        effects.push_back("• Riesgo de cáncer: MODERADO (5-20% probabilidad)");
        effects.push_back("• Fertilidad: Reducción temporal significativa");
        effects.push_back("• Daño cromosómico: MODERADO");
        effects.push_back("• Cataratas: Posible desarrollo");
    } else if (microSieverts < 10000.0) {
        effects.push_back("• Riesgo de cáncer: ALTO (20-50% probabilidad)");
        effects.push_back("• Fertilidad: SEVERAMENTE COMPROMETIDA");
        effects.push_back("• Daño cromosómico: SEVERO");
        effects.push_back("• Cataratas: Desarrollo probable");
        effects.push_back("• Envejecimiento prematuro");
    } else {
        effects.push_back("• Riesgo de cáncer: MUY ALTO (>70% probabilidad)");
        effects.push_back("• Fertilidad: PERMANENTEMENTE DAÑADA");
        effects.push_back("• Daño cromosómico: EXTREMO");
        effects.push_back("• Múltiples tipos de cáncer");
        effects.push_back("• Falla orgánica múltiple (si sobrevive)");
    }
    
    return effects;
}

std::vector<std::string> HealthEffectAnalyzer::getRecommendations(DangerLevel level) {
    std::vector<std::string> recommendations;
    
    switch (level) {
        case DangerLevel::SAFE:
            recommendations.push_back("✅ Continuar actividades normales");
            recommendations.push_back("📊 Monitoreo rutinario si es ocupacional");
            break;
        case DangerLevel::CAUTION:
            recommendations.push_back("⚠️ Limitar tiempo de exposición");
            recommendations.push_back("📋 Documentar exposición");
            recommendations.push_back("👥 Consultar con supervisor de seguridad");
            break;
        case DangerLevel::DANGEROUS:
            recommendations.push_back("🚨 REDUCIR TIEMPO DE EXPOSICIÓN");
            recommendations.push_back("🦺 Usar equipo de protección personal");
            recommendations.push_back("🏥 Monitoreo médico recomendado");
            recommendations.push_back("📞 Reportar a autoridades competentes");
            break;
        case DangerLevel::EXTREME:
            recommendations.push_back("☢️ EVACUACIÓN RECOMENDADA");
            recommendations.push_back("🏥 ATENCIÓN MÉDICA PREVENTIVA");
            recommendations.push_back("💊 Considerar yoduro de potasio");
            recommendations.push_back("📞 CONTACTAR SERVICIOS DE EMERGENCIA");
            break;
        case DangerLevel::LETHAL:
            recommendations.push_back("🚨 EVACUACIÓN INMEDIATA OBLIGATORIA");
            recommendations.push_back("🏥 ATENCIÓN MÉDICA URGENTE");
            recommendations.push_back("💊 TRATAMIENTO CON YODURO DE POTASIO");
            recommendations.push_back("📞 ALERTAR A EMERGENCIAS NUCLEARES");
            recommendations.push_back("🛡️ REFUGIO EN LUGAR PROTEGIDO");
            break;
    }
    
    return recommendations;
}

double HealthEffectAnalyzer::getSurvivalProbability(double totalDose, bool withTreatment) {
    // Dosis en mSv para cálculos de supervivencia
    double doseMSv = totalDose / 1000.0;
    
    if (doseMSv < 1000) {
        return withTreatment ? 99.0 : 98.0;
    } else if (doseMSv < 2000) {
        return withTreatment ? 90.0 : 80.0;
    } else if (doseMSv < 4000) {
        return withTreatment ? 70.0 : 50.0;
    } else if (doseMSv < 6000) {
        return withTreatment ? 50.0 : 20.0;
    } else if (doseMSv < 10000) {
        return withTreatment ? 20.0 : 5.0;
    } else {
        return withTreatment ? 5.0 : 1.0;
    }
}

std::string HealthEffectAnalyzer::getMedicalClassification(double microSieverts) {
    if (microSieverts < 2.0) {
        return "Sin síndrome de radiación";
    } else if (microSieverts < 100.0) {
        return "Síndrome de radiación leve";
    } else if (microSieverts < 1000.0) {
        return "Síndrome de radiación moderado";
    } else if (microSieverts < 10000.0) {
        return "⚠️ SÍNDROME DE RADIACIÓN AGUDA";
    } else {
        return "☠️ SÍNDROME NEUROLÓGICO AGUDO";
    }
}

std::string HealthEffectAnalyzer::getEmergencyProtocol(DangerLevel level) {
    switch (level) {
        case DangerLevel::SAFE:
        case DangerLevel::CAUTION:
            return "Protocolo estándar de monitoreo";
        case DangerLevel::DANGEROUS:
            return "Protocolo de exposición ocupacional elevada";
        case DangerLevel::EXTREME:
            return "PROTOCOLO DE EMERGENCIA RADIOLÓGICA";
        case DangerLevel::LETHAL:
            return "🚨 PROTOCOLO DE CATÁSTROFE NUCLEAR";
        default:
            return "Protocolo no definido";
    }
}

std::string HealthEffectAnalyzer::formatHealthEffectsReport(const HealthEffects& effects) {
    std::ostringstream report;
    
    report << "ANÁLISIS MÉDICO\n";
    report << "══════════════════════════════════════\n\n";
    
    report << "CLASIFICACIÓN: " << effects.medicalClassification << "\n";
    report << "PROTOCOLO: " << effects.emergencyProtocol << "\n\n";
    
    report << "EFECTOS INMEDIATOS:\n";
    for (const auto& effect : effects.immediateEffects) {
        report << "• [" << effect.timeRange << "]: " << effect.effect << "\n";
    }
    
    report << "\nEFECTOS A LARGO PLAZO:\n";
    for (const auto& effect : effects.longTermEffects) {
        report << effect << "\n";
    }
    
    report << "\nRECOMENDACIONES:\n";
    for (const auto& rec : effects.recommendations) {
        report << rec << "\n";
    }
    
    report << "\nSUPERVIVENCIA:\n";
    report << std::fixed << std::setprecision(0);
    report << "Sin tratamiento: " << effects.survivalProbabilityWithoutTreatment << "%\n";
    report << "Con tratamiento: " << effects.survivalProbabilityWithTreatment << "%\n";
    
    return report.str();
}

void HealthEffectAnalyzer::initializeEffectDatabase() {
    // Base de datos inicializada en el constructor
}

double HealthEffectAnalyzer::calculateAcuteDose(double microSieverts, double hours) {
    return microSieverts * hours;
}

std::string HealthEffectAnalyzer::getSeverityColor(const std::string& severity) {
    if (severity == "NINGUNO") return "#00FF41";
    if (severity == "LEVE") return "#FFFF00";
    if (severity == "MODERADO") return "#FF8C00";
    if (severity == "SEVERO") return "#FF0000";
    if (severity == "CRÍTICO") return "#FF0000";
    return "#00FF41";
}