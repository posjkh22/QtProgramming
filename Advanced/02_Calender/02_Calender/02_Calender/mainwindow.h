#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QFile>
#include <QTextEdit>
#include <QProcess>


class QCalendarWidget;
class QCheckBox;
class QComboBox;
class QDate;
class QDateEdit;
class QGridLayout;
class QGroupBox;
class QLabel;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private slots:
    void localeChanged(int index);
    void firstDayChanged(int index);
    void selectionModeChanged(int index);
    void horizontalHeaderChanged(int index);
    void verticalHeaderChanged(int index);
    void selectedDateChanged();
    void minimumDateChanged(const QDate &date);
    void maximumDateChanged(const QDate &date);
    void weekdayFormatChanged();
    void weekendFormatChanged();
    void reformatHeaders();
    void reformatCalendarPage();
    void handleButton();
    void handleAnalysis();

    void threadTypeChanged(int index);
    void targetTypeChanged(int index);


private:
    void createCodeAnalysisGroupBox();
    void createCodeViewerBox();
    void createTempCalender();

    void createGeneralOptionsGroupBox();
    void createTextFormatsGroupBox();
    QComboBox *createColorComboBox();

    QString sourceFileName;
    QFile sourceFile;
    QTextEdit *sourceCodeViewer;

    QGroupBox* codeAnalysisBox;
    QGridLayout *codeAnalysisLayout;

    QGroupBox *tempCalenderBox;
    QGridLayout *tempCalenderLayout;

    QGroupBox *codeViewerBox;
    QGridLayout *codeViewerLayout;

    QGroupBox *AnalysisResultBox;
    QGridLayout *AnalysisResultLayout;
    QTextEdit *AnalysisResultViewer;
    QString AnalysisResultFileName;
    QFile AnalysisResultFile;



    QLabel* sourceCodeNameViewLabel;

    QLabel* threadTypeLabel;
    QLabel* targetTypeLabel;



    QProcess *main_process;
    QString threadOption;
    QString targetOption;

    QGridLayout *previewLayout;




    QCalendarWidget *calendar;

    QGroupBox *generalOptionsGroupBox;
    QLabel *localeLabel;
    QLabel *firstDayLabel;
    QLabel *selectionModeLabel;
    QLabel *horizontalHeaderLabel;
    QLabel *verticalHeaderLabel;

    QLabel *threadLabel;
    QLabel *targetLabel;

    QComboBox *threadCombo;
    QComboBox *targetCombo;

    QComboBox *localeCombo;
    QComboBox *firstDayCombo;
    QComboBox *selectionModeCombo;
    QCheckBox *gridCheckBox;
    QCheckBox *navigationCheckBox;
    QComboBox *horizontalHeaderCombo;
    QComboBox *verticalHeaderCombo;

    QLabel *currentDateLabel;
    QLabel *minimumDateLabel;
    QLabel *maximumDateLabel;
    QDateEdit *currentDateEdit;
    QDateEdit *minimumDateEdit;
    QDateEdit *maximumDateEdit;

    QGroupBox *textFormatsGroupBox;
    QLabel *weekdayColorLabel;
    QLabel *weekendColorLabel;
    QLabel *headerTextFormatLabel;
    QComboBox *weekdayColorCombo;
    QComboBox *weekendColorCombo;
    QComboBox *headerTextFormatCombo;

    QCheckBox *firstFridayCheckBox;
    QCheckBox *mayFirstCheckBox;
};

#endif
