#include "FalloutStyleWidget.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QFontDatabase>

// Definición de colores Fallout
const QString FalloutStyleWidget::FALLOUT_GREEN = "#00FF41";
const QString FalloutStyleWidget::FALLOUT_BLACK = "#000000";
const QString FalloutStyleWidget::FALLOUT_YELLOW = "#FFFF00";
const QString FalloutStyleWidget::FALLOUT_ORANGE = "#FF8C00";
const QString FalloutStyleWidget::FALLOUT_RED = "#FF0000";

FalloutStyleWidget::FalloutStyleWidget(QWidget *parent)
    : QWidget(parent), animationFrame(0) {
    setupAnimation();
    applyFalloutStyle(this);
}

void FalloutStyleWidget::applyFalloutStyle(QWidget* widget) {
    if (!widget) return;
    
    widget->setStyleSheet(
        "QWidget {"
        "   background-color: " + FALLOUT_BLACK + ";"
        "   color: " + FALLOUT_GREEN + ";"
        "   border: 1px solid " + FALLOUT_GREEN + ";"
        "}"
        "QLineEdit {"
        "   background-color: " + FALLOUT_BLACK + ";"
        "   color: " + FALLOUT_GREEN + ";"
        "   border: 2px solid " + FALLOUT_GREEN + ";"
        "   padding: 5px;"
        "   font-family: 'Courier New', monospace;"
        "   font-size: 14px;"
        "}"
        "QPushButton {"
        "   background-color: " + FALLOUT_BLACK + ";"
        "   color: " + FALLOUT_GREEN + ";"
        "   border: 2px solid " + FALLOUT_GREEN + ";"
        "   padding: 8px 16px;"
        "   font-family: 'Courier New', monospace;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: " + FALLOUT_GREEN + ";"
        "   color: " + FALLOUT_BLACK + ";"
        "}"
        "QPushButton:pressed {"
        "   background-color: " + FALLOUT_GREEN + ";"
        "   color: " + FALLOUT_BLACK + ";"
        "}"
        "QComboBox {"
        "   background-color: " + FALLOUT_BLACK + ";"
        "   color: " + FALLOUT_GREEN + ";"
        "   border: 2px solid " + FALLOUT_GREEN + ";"
        "   padding: 5px;"
        "   font-family: 'Courier New', monospace;"
        "}"
        "QTextEdit {"
        "   background-color: " + FALLOUT_BLACK + ";"
        "   color: " + FALLOUT_GREEN + ";"
        "   border: 1px solid " + FALLOUT_GREEN + ";"
        "   font-family: 'Courier New', monospace;"
        "   font-size: 12px;"
        "}"
        "QProgressBar {"
        "   background-color: " + FALLOUT_BLACK + ";"
        "   border: 2px solid " + FALLOUT_GREEN + ";"
        "   text-align: center;"
        "   font-family: 'Courier New', monospace;"
        "   font-weight: bold;"
        "}"
        "QProgressBar::chunk {"
        "   background-color: " + FALLOUT_GREEN + ";"
        "}"
    );
    
    applyTerminalFont(widget);
}

void FalloutStyleWidget::applyTerminalFont(QWidget* widget) {
    widget->setFont(getTerminalFont());
}

QFont FalloutStyleWidget::getTerminalFont() {
    QFont font("Courier New", 12, QFont::Normal);
    font.setStyleHint(QFont::Monospace);
    return font;
}

void FalloutStyleWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Efecto de escanlines estilo CRT
    painter.setPen(QPen(QColor(FALLOUT_GREEN), 1, Qt::SolidLine));
    for (int y = 0; y < height(); y += 4) {
        painter.setOpacity(0.1);
        painter.drawLine(0, y, width(), y);
    }
    
    QWidget::paintEvent(event);
}

void FalloutStyleWidget::setupAnimation() {
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &FalloutStyleWidget::onAnimationTimer);
    animationTimer->start(500); // 500ms entre frames
}

void FalloutStyleWidget::onAnimationTimer() {
    animationFrame = (animationFrame + 1) % 4;
    update();
}

// FalloutLabel Implementation
FalloutLabel::FalloutLabel(const QString& text, QWidget* parent)
    : QLabel(text, parent), blinkVisible(true), glowEnabled(false) {
    FalloutStyleWidget::applyFalloutStyle(this);
    setupBlinking();
}

void FalloutLabel::setGlowEffect(bool enabled) {
    glowEnabled = enabled;
    if (enabled) {
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
        effect->setColor(QColor(FalloutStyleWidget::FALLOUT_GREEN));
        effect->setBlurRadius(15);
        effect->setOffset(0);
        setGraphicsEffect(effect);
    } else {
        setGraphicsEffect(nullptr);
    }
}

void FalloutLabel::setBlinking(bool enabled) {
    if (enabled) {
        blinkTimer->start(1000);
    } else {
        blinkTimer->stop();
        setVisible(true);
    }
}

void FalloutLabel::setupBlinking() {
    blinkTimer = new QTimer(this);
    connect(blinkTimer, &QTimer::timeout, this, &FalloutLabel::onBlinkTimer);
}

void FalloutLabel::onBlinkTimer() {
    blinkVisible = !blinkVisible;
    setVisible(blinkVisible);
}

// FalloutButton Implementation
FalloutButton::FalloutButton(const QString& text, QWidget* parent)
    : QPushButton(text, parent), isHovered(false) {
    FalloutStyleWidget::applyFalloutStyle(this);
}

void FalloutButton::setDangerLevel(const QString& level) {
    dangerLevel = level;
    QString color = getDangerColor(level);
    
    setStyleSheet(
        "QPushButton {"
        "   background-color: " + FalloutStyleWidget::FALLOUT_BLACK + ";"
        "   color: " + color + ";"
        "   border: 2px solid " + color + ";"
        "   padding: 8px 16px;"
        "   font-family: 'Courier New', monospace;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: " + color + ";"
        "   color: " + FalloutStyleWidget::FALLOUT_BLACK + ";"
        "}"
    );
}

QString FalloutButton::getDangerColor(const QString& level) {
    if (level == "SAFE") return FalloutStyleWidget::FALLOUT_GREEN;
    if (level == "CAUTION") return FalloutStyleWidget::FALLOUT_YELLOW;
    if (level == "DANGEROUS") return FalloutStyleWidget::FALLOUT_ORANGE;
    if (level == "EXTREME" || level == "LETHAL") return FalloutStyleWidget::FALLOUT_RED;
    return FalloutStyleWidget::FALLOUT_GREEN;
}

void FalloutButton::enterEvent(QEvent* event) {
    isHovered = true;
    QPushButton::enterEvent(event);
}

void FalloutButton::leaveEvent(QEvent* event) {
    isHovered = false;
    QPushButton::leaveEvent(event);
}

void FalloutButton::paintEvent(QPaintEvent* event) {
    QPushButton::paintEvent(event);
    
    if (isHovered) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(QColor(getDangerColor(dangerLevel)), 2));
        painter.drawRect(rect().adjusted(1, 1, -1, -1));
    }
}

// FalloutProgressBar Implementation
FalloutProgressBar::FalloutProgressBar(QWidget* parent)
    : QProgressBar(parent), currentAnimatedValue(0), targetAnimatedValue(0) {
    FalloutStyleWidget::applyFalloutStyle(this);
    
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &FalloutProgressBar::onAnimationStep);
    animationStep = 2;
}

void FalloutProgressBar::setDangerLevel(int percentage) {
    QString color = FalloutStyleWidget::FALLOUT_GREEN;
    
    if (percentage > 90) color = FalloutStyleWidget::FALLOUT_RED;
    else if (percentage > 70) color = FalloutStyleWidget::FALLOUT_ORANGE;
    else if (percentage > 40) color = FalloutStyleWidget::FALLOUT_YELLOW;
    
    setStyleSheet(
        "QProgressBar {"
        "   background-color: " + FalloutStyleWidget::FALLOUT_BLACK + ";"
        "   border: 2px solid " + FalloutStyleWidget::FALLOUT_GREEN + ";"
        "   text-align: center;"
        "   font-family: 'Courier New', monospace;"
        "   font-weight: bold;"
        "   color: " + FalloutStyleWidget::FALLOUT_GREEN + ";"
        "}"
        "QProgressBar::chunk {"
        "   background-color: " + color + ";"
        "}"
    );
}

void FalloutProgressBar::animateToValue(int targetValue) {
    targetAnimatedValue = targetValue;
    currentAnimatedValue = value();
    animationTimer->start(50);
}

void FalloutProgressBar::onAnimationStep() {
    if (currentAnimatedValue < targetAnimatedValue) {
        currentAnimatedValue = std::min(currentAnimatedValue + animationStep, targetAnimatedValue);
        setValue(currentAnimatedValue);
    } else if (currentAnimatedValue > targetAnimatedValue) {
        currentAnimatedValue = std::max(currentAnimatedValue - animationStep, targetAnimatedValue);
        setValue(currentAnimatedValue);
    } else {
        animationTimer->stop();
    }
}

// FalloutTextDisplay Implementation
FalloutTextDisplay::FalloutTextDisplay(QWidget* parent)
    : QTextEdit(parent), currentCharIndex(0), typewriterDelay(50) {
    setTerminalStyle();
    setupTypewriter();
}

void FalloutTextDisplay::setTerminalStyle() {
    FalloutStyleWidget::applyFalloutStyle(this);
    setReadOnly(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void FalloutTextDisplay::typewriterEffect(const QString& text, int delayMs) {
    typewriterDelay = delayMs;
    pendingText = text;
    currentCharIndex = 0;
    clear();
    typewriterTimer->start(typewriterDelay);
}

void FalloutTextDisplay::appendWithIcon(const QString& icon, const QString& text) {
    append(icon + " " + text);
}

void FalloutTextDisplay::clearWithEffect() {
    // Efecto de "borrado" con animación
    QString currentText = toPlainText();
    clear();
    for (int i = 0; i < currentText.length(); i += 10) {
        QTimer::singleShot(i * 2, [this, i, currentText]() {
            if (i < currentText.length()) {
                setPlainText(currentText.left(currentText.length() - i));
            }
        });
    }
}

void FalloutTextDisplay::setupTypewriter() {
    typewriterTimer = new QTimer(this);
    connect(typewriterTimer, &QTimer::timeout, this, &FalloutTextDisplay::onTypewriterTimer);
}

void FalloutTextDisplay::onTypewriterTimer() {
    if (currentCharIndex < pendingText.length()) {
        setPlainText(pendingText.left(currentCharIndex + 1));
        currentCharIndex++;
    } else {
        typewriterTimer->stop();
    }
}

