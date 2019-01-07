#ifndef SNIPERDIALOG_H
#define SNIPERDIALOG_H

#include <QDialog>

#include "sniperparams.h"
#include "F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/baseStrategyWrapper.h"
#include "F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/StrategyConstants.h"

namespace Ui {
class Sniperdialog;
}

class Sniperdialog : public APIWrapper
{
    Q_OBJECT

public:
    explicit Sniperdialog(QWidget *parent = 0);
    ~Sniperdialog();

    void setBasePointer(BaseStrategyWrapper *ptr)
    {
        setBaseWrapper(ptr);
    }

    void initDisplay();
    bool updateStrategyDefaultValues()
    {
        return true;
    }
    void updateEditableFieldColor(int row, QColor color);

private:
    Ui::Sniperdialog *ui;
    Sniperparams *_Sniperparams;
    QStandardItemModel *_baseTableModel;
    QTimer _timer;
    bool _isNewStrategyWriteMethod;
    int _updateCounter;
    API2::StrategyParamMap *_paramsMap;
    void initialize();
    void initializeSymbolPanel();
    void setDefaultIndex();

    //Flags
    bool isSpreadCalculationAllowed();
    bool isPortfolioNamePresent();

    bool buildCommandFromUi(API2::PORTFOLIO_STATE state);
    void updateRemainingFeilds(int row, QSqlRecord &adminTokenIdData);
    void populateUIPanels(int row, QSqlRecord &record, bool isNew);
    void setApiCommand(API2::UserParams * apiParams, QSqlRecord &record, int stgCount, short type);
    bool validateData(API2::PORTFOLIO_STATE state);
    bool isSidTotalQtyHandling();
    void getDllVersionString(QString &dllVersionString);
    void populateFilters();


public slots:
    //Overridden Slots
    void onNewPushButtonClicked();
    void onAddPushButtonClicked();
    void onRemovePushButtonClicked();
    void onEditPushButtonClicked();
    void onCommitPushButtonClicked();
    void onRunPushButtonClicked();
    void onAltMPressed();
    void onEscapePressed();
    void onRunActivated(){}
    void onCtrlSpacePressed();
    void onUpKeyPressed();
    void OnDownKeyPressed(){}
    void receiveStrategyResponse(API2::Strategy &strategyResponse);
    void updateDataOnTimer();
    bool isStrategyLegPresent();

private slots:
    void on_pushButtonClose_clicked();
    void setPrecisionDecimal(int);
};

#endif // SNIPERDIALOG_H
