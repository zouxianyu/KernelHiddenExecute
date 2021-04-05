#pragma once

#include <QtWidgets/QWidget>
#include "ui_ControlPanel.h"

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    ControlPanel(QWidget *parent = Q_NULLPTR);

private:
    Ui::ControlPanelClass ui;
};
