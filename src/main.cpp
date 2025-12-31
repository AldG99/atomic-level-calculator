#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Radiation Monitor");
    app.setApplicationVersion("2.287");
    app.setApplicationDisplayName("Medidor de Radiación v2.287");
    app.setOrganizationName("Vault-Tec Industries");
    app.setOrganizationDomain("vault-tec.com");
    
    // Set dark style as base
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // Apply dark palette
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(0, 0, 0));
    darkPalette.setColor(QPalette::WindowText, QColor(0, 255, 65));
    darkPalette.setColor(QPalette::Base, QColor(0, 0, 0));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(0, 0, 0));
    darkPalette.setColor(QPalette::ToolTipText, QColor(0, 255, 65));
    darkPalette.setColor(QPalette::Text, QColor(0, 255, 65));
    darkPalette.setColor(QPalette::Button, QColor(0, 0, 0));
    darkPalette.setColor(QPalette::ButtonText, QColor(0, 255, 65));
    darkPalette.setColor(QPalette::BrightText, QColor(255, 0, 0));
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, QColor(0, 0, 0));
    app.setPalette(darkPalette);
    
    // Check if resources directory exists
    QDir resourcesDir("resources");
    if (!resourcesDir.exists()) {
        QMessageBox::warning(nullptr, "Recursos Faltantes", 
            "No se encontró el directorio 'resources'. "
            "Asegúrese de que el programa esté en el directorio correcto.");
    }
    
    try {
        MainWindow window;
        window.show();
        
        // Show welcome message
        QMessageBox::information(&window, 
            "Bienvenido", 
            "☢️ SISTEMA INICIADO ☢️\n\n"
            "Medidor de Radiación v2.287\n"
            "Estado: OPERATIVO\n\n"
            "Ingrese un nivel de radiación para comenzar el análisis.\n"
            "¡Manténgase seguro ahí fuera, habitante del Refugio!");
        
        return app.exec();
        
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Error Crítico", 
            QString("Error al inicializar la aplicación:\n%1").arg(e.what()));
        return -1;
    }
}

// Información del programa para depuración
/*
RADIATION MONITOR v2.287
==========================================

Este programa es una aplicación educativa que simula un medidor de radiación. 
Permite:

- Conversión entre unidades de radiación (μSv/h, mSv/h, Sv/h)
- Cálculo de equivalencia en plátanos (BED)
- Análisis de efectos en la salud
- Comparaciones con sitios históricos
- Interfaz estilo terminal retro

Desarrollado con Qt5 y C++17.

Características implementadas:
✓ Calculadora de radiación con conversiones
✓ Equivalencias de plátanos animadas
✓ Análisis médico de efectos
✓ Base de datos de sitios de referencia
✓ Interfaz gráfica estilo Fallout
✓ Animaciones y efectos visuales
✓ Modo de emergencia
✓ Sistema de pestañas informativas

Para compilar:
mkdir build && cd build
cmake ..
make

Para ejecutar:
./RadiationMonitor

AGG
*/