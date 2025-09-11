#ifndef FALLOUTSTYLEWIDGET_H
#define FALLOUTSTYLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QTimer>
#include <QFont>

class FalloutStyleWidget : public QWidget {
    Q_OBJECT

public:
    explicit FalloutStyleWidget(QWidget *parent = nullptr);
    
    // Estilo Fallout/Terminal
    static void applyFalloutStyle(QWidget* widget);
    static void applyTerminalFont(QWidget* widget);
    static QFont getTerminalFont();
    
    // Colores del tema
    static const QString FALLOUT_GREEN;
    static const QString FALLOUT_BLACK;
    static const QString FALLOUT_YELLOW;
    static const QString FALLOUT_ORANGE;
    static const QString FALLOUT_RED;
    
protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void onAnimationTimer();

private:
    QTimer* animationTimer;
    int animationFrame;
    
    void setupAnimation();
};

class FalloutLabel : public QLabel {
    Q_OBJECT

public:
    explicit FalloutLabel(const QString& text = "", QWidget* parent = nullptr);
    void setGlowEffect(bool enabled);
    void setBlinking(bool enabled);

private slots:
    void onBlinkTimer();

private:
    QTimer* blinkTimer;
    bool blinkVisible;
    bool glowEnabled;
    
    void setupBlinking();
};

class FalloutButton : public QPushButton {
    Q_OBJECT

public:
    explicit FalloutButton(const QString& text = "", QWidget* parent = nullptr);
    void setDangerLevel(const QString& level); // "SAFE", "CAUTION", "DANGEROUS", "EXTREME", "LETHAL"

protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QString dangerLevel;
    bool isHovered;
    
    QString getDangerColor(const QString& level);
};

class FalloutProgressBar : public QProgressBar {
    Q_OBJECT

public:
    explicit FalloutProgressBar(QWidget* parent = nullptr);
    void setDangerLevel(int percentage);
    void animateToValue(int targetValue);

private slots:
    void onAnimationStep();

private:
    QTimer* animationTimer;
    int currentAnimatedValue;
    int targetAnimatedValue;
    int animationStep;
};

class FalloutTextDisplay : public QTextEdit {
    Q_OBJECT

public:
    explicit FalloutTextDisplay(QWidget* parent = nullptr);
    void typewriterEffect(const QString& text, int delayMs = 50);
    void appendWithIcon(const QString& icon, const QString& text);
    void setTerminalStyle();

public slots:
    void clearWithEffect();

private slots:
    void onTypewriterTimer();

private:
    QTimer* typewriterTimer;
    QString pendingText;
    int currentCharIndex;
    int typewriterDelay;
    
    void setupTypewriter();
};

#endif // FALLOUTSTYLEWIDGET_H