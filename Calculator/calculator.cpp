#include <QtWidgets>
#include <cmath>
#include "button.h"
#include "calculator.h"

#define PI 3.14159265

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for (int i = 0; i< NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
    Button *changeSignButton = createButton(tr("\302\261"), SLOT(changeSignClicked()));

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    Button *clearButton = createButton(tr("Clear"), SLOT(clear()));
    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));

    Button *clearMemoryButton = createButton(tr("MC"), SLOT(clearMemory()));
    Button *readMemoryButton = createButton(tr("MR"), SLOT(readMemory()));
    Button *setMemoryButton = createButton(tr("MS"), SLOT(setMemory()));
    Button *addToMemoryButton = createButton(tr("M+"), SLOT(addToMemory()));

    Button *divisionButton = createButton(tr("\303\267"), SLOT(multiplicativeOperatorClicked()));
    Button *timesButton = createButton(tr("\303\227"), SLOT(multiplicativeOperatorClicked()));
    Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));

    Button *squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    Button *powerButton = createButton(tr("x\302\262"), SLOT(unaryOperatorClicked()));
    Button *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
    Button *equalButton = createButton(tr("="), SLOT(equalClicked()));

    Button *sineButton = createButton(tr("sin"), SLOT(trigonometricOperatorClicked()));
    Button *cosineButton = createButton(tr("cos"), SLOT(trigonometricOperatorClicked()));
    Button *tangentButton = createButton(tr("tan"), SLOT(trigonometricOperatorClicked()));
    Button *arcsineButton = createButton(tr("asin"), SLOT(trigonometricOperatorClicked()));
    Button *arccosineButton = createButton(tr("acos"), SLOT(trigonometricOperatorClicked()));
    Button *arctangentButton = createButton(tr("atan"), SLOT(trigonometricOperatorClicked()));

    Button *logarithmButton = createButton(tr("ln"), SLOT(logarithmicOperatorClicked()));
    Button *comlogarithmButton = createButton(tr("lg"), SLOT(logarithmicOperatorClicked()));
    Button *exponentButton = createButton(tr("e"), SLOT(logarithmicOperatorClicked()));


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 9);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 3);
    mainLayout->addWidget(clearButton, 1, 3, 1, 3);
    mainLayout->addWidget(clearAllButton, 1, 6, 1, 3);

    mainLayout->addWidget(clearMemoryButton, 2, 0);
    mainLayout->addWidget(readMemoryButton, 3, 0);
    mainLayout->addWidget(setMemoryButton, 4, 0);
    mainLayout->addWidget(addToMemoryButton, 5, 0);

    for (int i = 1; i<NumDigitButtons; ++i) {
        int row = ((9-i) / 3) + 2;
        int column = ((i-1) % 3) +1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5, 1, 4);

    mainLayout->addWidget(sineButton, 2, 6);
    mainLayout->addWidget(cosineButton, 3, 6);
    mainLayout->addWidget(tangentButton, 4, 6);
    mainLayout->addWidget(arcsineButton, 2, 7);
    mainLayout->addWidget(arccosineButton, 3, 7);
    mainLayout->addWidget(arctangentButton, 4, 7);

    mainLayout->addWidget(logarithmButton, 2, 8);
    mainLayout->addWidget(comlogarithmButton, 3, 8);
    mainLayout->addWidget(exponentButton, 4, 8);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}

void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() =="0" && digitValue == 0.0)
        return;
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}

void Calculator::trigonometricOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("sin")) {
        result = std::sin(operand*PI/180);
    } else if (clickedOperator == tr("cos")) {
        result = std::cos(operand*PI/180);
    } else if (clickedOperator == tr("tan")) {
        result = std::tan(operand*PI/180);
    } else if (clickedOperator == tr("asin")) {
        result = std::asin(operand)*180/PI;
    } else if (clickedOperator == tr("acos")) {
        result = std::acos(operand)*180/PI;
    } else if (clickedOperator == tr("atan")) {
        result = std::atan(operand)*180/PI;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}

void Calculator::logarithmicOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;
    if (clickedOperator == tr("ln")) {
        result = std::log(operand);
    } else if (clickedOperator == tr("lg")) {
        result = std::log10(operand);
    } else if (clickedOperator == tr("e")) {
        result = std::exp(operand);
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}

void Calculator::unaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}
void Calculator::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAddictiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAddictiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }
    pendingAddictiveOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }
    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAddictiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAddictiveOperator)) {
            abortOperation();
            return;
        }
        pendingAddictiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if(!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}

void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void Calculator::clear()
{
    if (waitingForOperand)
        return;
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAddictiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}

Button *Calculator::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void::Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0)
            return false;
        factorSoFar /= rightOperand;
    } else if (pendingOperator == tr("sin")) {
        factorSoFar = std::sin(rightOperand);
    } else if (pendingOperator == tr("cos")) {
        factorSoFar = std::cos(rightOperand);
    } else if (pendingOperator == tr("tan")) {
        factorSoFar = std::tan(rightOperand);
    } else if (pendingOperator == tr("asin")) {
        factorSoFar = std::asin(rightOperand);
    } else if (pendingOperator == tr("acos")) {
        factorSoFar = std::acos(rightOperand);
    } else if (pendingOperator == tr("atan")) {
        factorSoFar = std::atan(rightOperand);
    } else if (pendingOperator == tr("ln")) {
        factorSoFar = std::log(rightOperand);
    } else if (pendingOperator == tr("lg")) {
        factorSoFar = std::log10(rightOperand);
    } else if (pendingOperator == tr("e")) {
        factorSoFar = std::exp(rightOperand);
    }
    return true;
}