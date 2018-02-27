#include <QtWidgets>
#include <QTextEdit>
#include <QDir>
#include "mainwindow.h"

Window::Window()
{
    createCodeAnalysisGroupBox();
    createCodeViewerBox();
    createTempCalender();

    createGeneralOptionsGroupBox();
    createTextFormatsGroupBox();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(codeAnalysisBox, 0, 0);
    layout->addWidget(codeViewerBox, 0, 1);
    layout->addWidget(tempCalenderBox, 0, 2);
    layout->addWidget(generalOptionsGroupBox, 1, 0);
    layout->addWidget(textFormatsGroupBox, 1, 1);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    //previewLayout->setRowMinimumHeight(0, calendar->sizeHint().height());
    //previewLayout->setColumnMinimumWidth(0, calendar->sizeHint().width());

    setWindowTitle(tr("Code Analysis Widget"));
}



void Window::threadTypeChanged(int index)
{
    if(index == 0)
    {
        threadTypeLabel->setText("Thread Type: Multi-thread");
    }
    else if(index == 1)
    {
        threadTypeLabel->setText("Thread Type: Uni-thread");
    }
    else
    {
        threadTypeLabel->setText("Thread Type: Error");
    }
}

void Window::targetTypeChanged(int index)
{
    if(index == 0)
    {
        targetTypeLabel->setText("Target Type: Linux");
    }
    else if(index == 1)
    {
        targetTypeLabel->setText("Target Type: OSEC");
    }
    else if(index == 2)
    {
        targetTypeLabel->setText("Target Type: FreeRTOS");
    }
    else if(index == 3)
    {
        targetTypeLabel->setText("Target Type: MicroC/OS-II");
    }
    else
    {
        targetTypeLabel->setText("Target Type: Error");
    }


}

void Window::localeChanged(int index)
{
    const QLocale newLocale(localeCombo->itemData(index).toLocale());
    calendar->setLocale(newLocale);
    int newLocaleFirstDayIndex = firstDayCombo->findData(newLocale.firstDayOfWeek());
    firstDayCombo->setCurrentIndex(newLocaleFirstDayIndex);
}

void Window::firstDayChanged(int index)
{
    calendar->setFirstDayOfWeek(Qt::DayOfWeek(
                                firstDayCombo->itemData(index).toInt()));
}

void Window::selectionModeChanged(int index)
{
    calendar->setSelectionMode(QCalendarWidget::SelectionMode(
                               selectionModeCombo->itemData(index).toInt()));
}

void Window::horizontalHeaderChanged(int index)
{
    calendar->setHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat(
        horizontalHeaderCombo->itemData(index).toInt()));
}

void Window::verticalHeaderChanged(int index)
{
    calendar->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat(
        verticalHeaderCombo->itemData(index).toInt()));
}

void Window::selectedDateChanged()
{
    currentDateEdit->setDate(calendar->selectedDate());
}

void Window::minimumDateChanged(const QDate &date)
{
    calendar->setMinimumDate(date);
    maximumDateEdit->setDate(calendar->maximumDate());
}

void Window::maximumDateChanged(const QDate &date)
{
    calendar->setMaximumDate(date);
    minimumDateEdit->setDate(calendar->minimumDate());
}

void Window::weekdayFormatChanged()
{
    QTextCharFormat format;

    format.setForeground(qvariant_cast<QColor>(
        weekdayColorCombo->itemData(weekdayColorCombo->currentIndex())));
    calendar->setWeekdayTextFormat(Qt::Monday, format);
    calendar->setWeekdayTextFormat(Qt::Tuesday, format);
    calendar->setWeekdayTextFormat(Qt::Wednesday, format);
    calendar->setWeekdayTextFormat(Qt::Thursday, format);
    calendar->setWeekdayTextFormat(Qt::Friday, format);
}

void Window::weekendFormatChanged()
{
    QTextCharFormat format;

    format.setForeground(qvariant_cast<QColor>(
        weekendColorCombo->itemData(weekendColorCombo->currentIndex())));
    calendar->setWeekdayTextFormat(Qt::Saturday, format);
    calendar->setWeekdayTextFormat(Qt::Sunday, format);
}

void Window::reformatHeaders()
{
    QString text = headerTextFormatCombo->currentText();
    QTextCharFormat format;

    if (text == tr("Bold")) {
        format.setFontWeight(QFont::Bold);
    } else if (text == tr("Italic")) {
        format.setFontItalic(true);
    } else if (text == tr("Green")) {
        format.setForeground(Qt::green);
    }
    calendar->setHeaderTextFormat(format);
}

void Window::reformatCalendarPage()
{
    QTextCharFormat mayFirstFormat;
    const QDate mayFirst(calendar->yearShown(), 5, 1);

    QTextCharFormat firstFridayFormat;
    QDate firstFriday(calendar->yearShown(), calendar->monthShown(), 1);
    while (firstFriday.dayOfWeek() != Qt::Friday)
        firstFriday = firstFriday.addDays(1);

    if (firstFridayCheckBox->isChecked()) {
        firstFridayFormat.setForeground(Qt::blue);
    } else { // Revert to regular colour for this day of the week.
        Qt::DayOfWeek dayOfWeek(static_cast<Qt::DayOfWeek>(firstFriday.dayOfWeek()));
        firstFridayFormat.setForeground(calendar->weekdayTextFormat(dayOfWeek).foreground());
    }

    calendar->setDateTextFormat(firstFriday, firstFridayFormat);

    // When it is checked, "May First in Red" always takes precedence over "First Friday in Blue".
    if (mayFirstCheckBox->isChecked()) {
        mayFirstFormat.setForeground(Qt::red);
    } else if (!firstFridayCheckBox->isChecked() || firstFriday != mayFirst) {
        // We can now be certain we won't be resetting "May First in Red" when we restore
        // may 1st's regular colour for this day of the week.
        Qt::DayOfWeek dayOfWeek(static_cast<Qt::DayOfWeek>(mayFirst.dayOfWeek()));
        calendar->setDateTextFormat(mayFirst, calendar->weekdayTextFormat(dayOfWeek));
    }

    calendar->setDateTextFormat(mayFirst, mayFirstFormat);
}

void Window::createTempCalender()
{
    tempCalenderBox = new QGroupBox(tr("tempCalender"));
    tempCalenderLayout = new QGridLayout;


    calendar = new QCalendarWidget;
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(3000, 1, 1));
    calendar->setGridVisible(true);

    connect(calendar, SIGNAL(currentPageChanged(int,int)),
            this, SLOT(reformatCalendarPage()));

    tempCalenderLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);
    tempCalenderBox->setLayout(tempCalenderLayout);

}


void Window::handleAnalysis()
{
    threadOption = QString("--thread=Unithread");
    targetOption = QString("--target=Linux");
    QString file = QDir::currentPath() + "./code_analysis " + sourceFileName + " " + threadOption + " " + targetOption;
    qDebug() << "running: " << "./code_analysis" + sourceFileName+ threadOption + targetOption;
    main_process->start(file);
}


void Window::createCodeAnalysisGroupBox()
{
    codeAnalysisBox = new QGroupBox(tr("CodeAnalysis"));
    codeAnalysisLayout = new QGridLayout;

    main_process = new QProcess(this);

    QPushButton *code_analysis_button = new QPushButton();
    code_analysis_button = new QPushButton("Code Analysis");
    code_analysis_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(code_analysis_button, SIGNAL (released()), this, SLOT (handleAnalysis()));
    codeAnalysisLayout->addWidget(code_analysis_button, 0, 0, Qt::AlignLeft);
    codeAnalysisBox->setLayout(codeAnalysisLayout);


    threadTypeLabel = new QLabel(this);
    threadTypeLabel->setText("Thread Type: ");
    codeAnalysisLayout->addWidget(threadTypeLabel, 0, 1, Qt::AlignLeft);
    codeAnalysisBox->setLayout(codeAnalysisLayout);

    targetTypeLabel = new QLabel(this);
    targetTypeLabel->setText("Target Type: ");
    codeAnalysisLayout->addWidget(targetTypeLabel, 0, 2, Qt::AlignLeft);
    codeAnalysisBox->setLayout(codeAnalysisLayout);


    // Show the image //
    QLabel* analysisGraph = new QLabel("<img src='image.jpg' />");
    codeAnalysisLayout->addWidget(analysisGraph, 1, 0, Qt::AlignCenter);
    analysisGraph->show();
    codeAnalysisBox->setLayout(codeAnalysisLayout);



    /*
    calendar = new QCalendarWidget;
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(3000, 1, 1));
    calendar->setGridVisible(true);

    connect(calendar, SIGNAL(currentPageChanged(int,int)),
            this, SLOT(reformatCalendarPage()));

    codeAnalysisLayout->addWidget(calendar, 1, 1, Qt::AlignCenter);
    codeAnalysis->setLayout(codeAnalysisLayout);
    */

}


void Window::handleButton()
{
    // Pop FileDiaglog //
    sourceFileName = QFileDialog::getOpenFileName(
                this,
                "Open Source code",
                QDir::currentPath(),
                "All files (*.*) ;; cpp files (*.cpp);; c files (*.c);; header files (*.h)");

    if(!sourceFileName.isNull())
    {
        qDebug() << "selected file path: " << sourceFileName.toUtf8();
    }

    // Label source Code //
    sourceCodeNameViewLabel->setText("Source code: " + sourceFileName.toUtf8());


    // View source Code //
    sourceCodeViewer->clear();
    sourceFile.setFileName(sourceFileName);

    if(!sourceFile.exists())
    {
        qDebug() << "No exists file: " << sourceFileName;
    }
    else
    {
        qDebug() << sourceFileName << " open";
    }

    QString line;
    if(sourceFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&sourceFile);
        while(!stream.atEnd())
        {
            line = stream.readLine();
            sourceCodeViewer->setText(sourceCodeViewer->toPlainText()+line+"\n");
            qDebug() << "line: " << line;
        }
    }
}


void Window::createCodeViewerBox()
{

    codeViewerBox = new QGroupBox(tr("Source code"));

    // Button: Source code selector //
    codeViewerLayout = new QGridLayout;

    QPushButton *code_sel_button = new QPushButton();
    code_sel_button = new QPushButton("Code Selector");
    code_sel_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(code_sel_button, SIGNAL (released()), this, SLOT (handleButton()));
    codeViewerLayout->addWidget(code_sel_button, 0, 0, Qt::AlignLeft);
    codeViewerBox->setLayout(codeViewerLayout);


    // Label: SourceCodeName View //
    sourceCodeNameViewLabel = new QLabel(this);
    codeViewerLayout->addWidget(sourceCodeNameViewLabel, 1, 0, Qt::AlignLeft);
    codeViewerBox->setLayout(codeViewerLayout);


    // TextEdit: Source code viewer //
    sourceCodeViewer = new QTextEdit();
    sourceCodeViewer->resize(50, 170);
    sourceCodeViewer->clear();

    codeViewerLayout->addWidget(sourceCodeViewer, 2, 0, Qt::AlignCenter);
    codeViewerBox->setLayout(codeViewerLayout);


    //sourceFile.close();


}



void Window::createGeneralOptionsGroupBox()
{
    generalOptionsGroupBox = new QGroupBox(tr("General Options"));

    // threadCombo box //
    threadCombo = new QComboBox;

    threadLabel = new QLabel(tr("&Thread Type"));
    threadLabel->setBuddy(threadCombo);

    threadCombo->addItem(tr("Multi-thread"), Qt::Sunday);
    threadCombo->addItem(tr("Uni-thread"), Qt::Monday);



    // targetCombo box //
    targetCombo = new QComboBox;

    targetLabel = new QLabel(tr("&OS Type"));
    targetLabel->setBuddy(targetCombo);

    targetCombo->addItem(tr("Linux"), Qt::Sunday);
    targetCombo->addItem(tr("OSEC"), Qt::Monday);
    targetCombo->addItem(tr("FreeRTOS"), Qt::Monday);
    targetCombo->addItem(tr("MicroC/OS-II"), Qt::Monday);






    localeCombo = new QComboBox;
    int curLocaleIndex = -1;
    int index = 0;
    for (int _lang = QLocale::C; _lang <= QLocale::LastLanguage; ++_lang) {
        QLocale::Language lang = static_cast<QLocale::Language>(_lang);
        QList<QLocale::Country> countries = QLocale::countriesForLanguage(lang);
        for (int i = 0; i < countries.count(); ++i) {
            QLocale::Country country = countries.at(i);
            QString label = QLocale::languageToString(lang);
            label += QLatin1Char('/');
            label += QLocale::countryToString(country);
            QLocale locale(lang, country);
            if (this->locale().language() == lang && this->locale().country() == country)
                curLocaleIndex = index;
            localeCombo->addItem(label, locale);
            ++index;
        }
    }
    if (curLocaleIndex != -1)
        localeCombo->setCurrentIndex(curLocaleIndex);
    localeLabel = new QLabel(tr("&Locale"));
    localeLabel->setBuddy(localeCombo);

    firstDayCombo = new QComboBox;
    firstDayCombo->addItem(tr("Sunday"), Qt::Sunday);
    firstDayCombo->addItem(tr("Monday"), Qt::Monday);
    firstDayCombo->addItem(tr("Tuesday"), Qt::Tuesday);
    firstDayCombo->addItem(tr("Wednesday"), Qt::Wednesday);
    firstDayCombo->addItem(tr("Thursday"), Qt::Thursday);
    firstDayCombo->addItem(tr("Friday"), Qt::Friday);
    firstDayCombo->addItem(tr("Saturday"), Qt::Saturday);

    firstDayLabel = new QLabel(tr("Wee&k starts on:"));
    firstDayLabel->setBuddy(firstDayCombo);

    selectionModeCombo = new QComboBox;
    selectionModeCombo->addItem(tr("Single selection"),
                                QCalendarWidget::SingleSelection);
    selectionModeCombo->addItem(tr("None"), QCalendarWidget::NoSelection);

    selectionModeLabel = new QLabel(tr("&Selection mode:"));
    selectionModeLabel->setBuddy(selectionModeCombo);

    gridCheckBox = new QCheckBox(tr("&Grid"));
    gridCheckBox->setChecked(calendar->isGridVisible());

    navigationCheckBox = new QCheckBox(tr("&Navigation bar"));
    navigationCheckBox->setChecked(true);

    horizontalHeaderCombo = new QComboBox;
    horizontalHeaderCombo->addItem(tr("Single letter day names"),
                                   QCalendarWidget::SingleLetterDayNames);
    horizontalHeaderCombo->addItem(tr("Short day names"),
                                   QCalendarWidget::ShortDayNames);
    horizontalHeaderCombo->addItem(tr("None"),
                                   QCalendarWidget::NoHorizontalHeader);
    horizontalHeaderCombo->setCurrentIndex(1);

    horizontalHeaderLabel = new QLabel(tr("&Horizontal header:"));
    horizontalHeaderLabel->setBuddy(horizontalHeaderCombo);

    verticalHeaderCombo = new QComboBox;
    verticalHeaderCombo->addItem(tr("ISO week numbers"),
                                 QCalendarWidget::ISOWeekNumbers);
    verticalHeaderCombo->addItem(tr("None"), QCalendarWidget::NoVerticalHeader);

    verticalHeaderLabel = new QLabel(tr("&Vertical header:"));
    verticalHeaderLabel->setBuddy(verticalHeaderCombo);

    connect(localeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(localeChanged(int)));
    connect(firstDayCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(firstDayChanged(int)));
    connect(selectionModeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(selectionModeChanged(int)));
    connect(gridCheckBox, SIGNAL(toggled(bool)),
            calendar, SLOT(setGridVisible(bool)));
    connect(navigationCheckBox, SIGNAL(toggled(bool)),
            calendar, SLOT(setNavigationBarVisible(bool)));
    connect(horizontalHeaderCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(horizontalHeaderChanged(int)));
    connect(verticalHeaderCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(verticalHeaderChanged(int)));


    connect(threadCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(threadTypeChanged(int)));
    connect(targetCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(targetTypeChanged(int)));





    QHBoxLayout *checkBoxLayout = new QHBoxLayout;
    checkBoxLayout->addWidget(gridCheckBox);
    checkBoxLayout->addStretch();
    checkBoxLayout->addWidget(navigationCheckBox);




    QGridLayout *outerLayout = new QGridLayout;
    outerLayout->addWidget(localeLabel, 0, 0);
    outerLayout->addWidget(localeCombo, 0, 1);
    outerLayout->addWidget(firstDayLabel, 1, 0);
    outerLayout->addWidget(firstDayCombo, 1, 1);
    outerLayout->addWidget(selectionModeLabel, 2, 0);
    outerLayout->addWidget(selectionModeCombo, 2, 1);
    outerLayout->addLayout(checkBoxLayout, 3, 0, 1, 2);
    outerLayout->addWidget(horizontalHeaderLabel, 4, 0);
    outerLayout->addWidget(horizontalHeaderCombo, 4, 1);
    outerLayout->addWidget(verticalHeaderLabel, 5, 0);
    outerLayout->addWidget(verticalHeaderCombo, 5, 1);

    outerLayout->addWidget(threadLabel, 6, 0);
    outerLayout->addWidget(threadCombo, 6, 1);
    outerLayout->addWidget(targetLabel, 7, 0);
    outerLayout->addWidget(targetCombo, 7, 1);



    generalOptionsGroupBox->setLayout(outerLayout);





    firstDayChanged(firstDayCombo->currentIndex());
    selectionModeChanged(selectionModeCombo->currentIndex());
    horizontalHeaderChanged(horizontalHeaderCombo->currentIndex());
    verticalHeaderChanged(verticalHeaderCombo->currentIndex());
}


void Window::createTextFormatsGroupBox()
{
    textFormatsGroupBox = new QGroupBox(tr("Text Formats"));

    weekdayColorCombo = createColorComboBox();
    weekdayColorCombo->setCurrentIndex(
            weekdayColorCombo->findText(tr("Black")));

    weekdayColorLabel = new QLabel(tr("&Weekday color:"));
    weekdayColorLabel->setBuddy(weekdayColorCombo);

    weekendColorCombo = createColorComboBox();
    weekendColorCombo->setCurrentIndex(
            weekendColorCombo->findText(tr("Red")));

    weekendColorLabel = new QLabel(tr("Week&end color:"));
    weekendColorLabel->setBuddy(weekendColorCombo);

    headerTextFormatCombo = new QComboBox;
    headerTextFormatCombo->addItem(tr("Bold"));
    headerTextFormatCombo->addItem(tr("Italic"));
    headerTextFormatCombo->addItem(tr("Plain"));

    headerTextFormatLabel = new QLabel(tr("&Header text:"));
    headerTextFormatLabel->setBuddy(headerTextFormatCombo);

    firstFridayCheckBox = new QCheckBox(tr("&First Friday in blue"));

    mayFirstCheckBox = new QCheckBox(tr("May &1 in red"));

    connect(weekdayColorCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(weekdayFormatChanged()));
    connect(weekdayColorCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(reformatCalendarPage()));
    connect(weekendColorCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(weekendFormatChanged()));
    connect(weekendColorCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(reformatCalendarPage()));
    connect(headerTextFormatCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(reformatHeaders()));
    connect(firstFridayCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(reformatCalendarPage()));
    connect(mayFirstCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(reformatCalendarPage()));

    QHBoxLayout *checkBoxLayout = new QHBoxLayout;
    checkBoxLayout->addWidget(firstFridayCheckBox);
    checkBoxLayout->addStretch();
    checkBoxLayout->addWidget(mayFirstCheckBox);

    QGridLayout *outerLayout = new QGridLayout;
    outerLayout->addWidget(weekdayColorLabel, 0, 0);
    outerLayout->addWidget(weekdayColorCombo, 0, 1);
    outerLayout->addWidget(weekendColorLabel, 1, 0);
    outerLayout->addWidget(weekendColorCombo, 1, 1);
    outerLayout->addWidget(headerTextFormatLabel, 2, 0);
    outerLayout->addWidget(headerTextFormatCombo, 2, 1);
    outerLayout->addLayout(checkBoxLayout, 3, 0, 1, 2);
    textFormatsGroupBox->setLayout(outerLayout);

    weekdayFormatChanged();
    weekendFormatChanged();
    reformatHeaders();
    reformatCalendarPage();
}

QComboBox *Window::createColorComboBox()
{
    QComboBox *comboBox = new QComboBox;
    comboBox->addItem(tr("Red"), QColor(Qt::red));
    comboBox->addItem(tr("Blue"), QColor(Qt::blue));
    comboBox->addItem(tr("Black"), QColor(Qt::black));
    comboBox->addItem(tr("Magenta"), QColor(Qt::magenta));
    return comboBox;
}
